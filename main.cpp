#include "main.hpp"

LogQueue* lgQu = new LogQueue();
bool canConnect = true;

enum InputModes
{
	M_PRESS = 0x00,
	M_CLICK = 0x01,
	M_KEYREPEAT = 0x02
};

enum PressMode
{
	P_CLICK = 0x00,
	P_PRESS = 0x01,
	P_RELEASE = 0x02
};

void setBarPercent(int percent)
{
	GUI::Widget::getWidgetByID<GUI::LoadingBar>("updateBar")->fill(percent, 0.05);
	GUI::Widget::getWidgetByID<GUI::Label>("updateBarLbl")->setText(std::to_string(percent) + "%", sf::Color::White);
}

void addLog(std::string content)
{
	std::cout << content << std::endl;
	lgQu->push_back(content);
	GUI::Widget::getWidgetByID<GUI::Label>("logsContLbl")->setComplexText(lgQu->returnComplexText());
}

void setLog(std::string content)
{
	lgQu->set(content);
	GUI::Widget::getWidgetByID<GUI::Label>("logsContLbl")->setComplexText(lgQu->returnComplexText());
}

void handleEvents(std::string ip, int port, std::vector<std::string>* allKeys, std::map<std::string, std::string>* keyAssoc, std::map<std::string, int>* pressMode, mse::Input::KeyBinder* keybinder)
{
	canConnect = false;
	GUI::Widget::getWidgetByID<GUI::Button>("connectBtn")->setText("Connecting...", "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3);
	addLog("<color:255,255,255>Connexion to Vita [ ... ]");
	//Network
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(ip, port);
	socket.setBlocking(true);
	if (status != sf::Socket::Done)
		setLog("<color:255,255,255>Connexion to Vita [ <color:255,0,0>Fail<color:255,255,255> ]");
	else
		setLog("<color:255,255,255>Connexion to Vita [ <color:0,255,0>Done<color:255,255,255> ]");
	GUI::Widget::getWidgetByID<GUI::Button>("connectBtn")->setText("Connected", "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3);
	sf::Packet initPacket;
	initPacket << 0;
	socket.send(initPacket);
	char sockData[256];
	std::size_t received;
	PsVitaKeys psvKeys;
	std::vector<std::string> pastActivation;

	while (true)
	{
		socket.send(initPacket);
		status = socket.receive(sockData, 256, received);
		if (status == sf::Socket::Done)
		{
			std::vector<std::string> getKeys = psvKeys.getPressedKeys(sockData);
			std::vector<std::string> pastActivationBuffer;
			for (int i = 0; i < getKeys.size(); i++)
			{
				if (pressMode->at(getKeys[i]) == M_KEYREPEAT || (pressMode->at(getKeys[i]) == M_CLICK && !mse::Functions::Vector::isInList(getKeys[i], pastActivation)))
					keybinder->simulateKey(keyAssoc->at(getKeys[i]), P_CLICK);
				else if (pressMode->at(getKeys[i]) == M_PRESS && !mse::Functions::Vector::isInList(getKeys[i], pastActivation))
					keybinder->simulateKey(keyAssoc->at(getKeys[i]), P_PRESS);
				pastActivationBuffer.push_back(getKeys[i]);
			}
			for (int i = 0; i < pastActivation.size(); i++)
			{
				if (pressMode->at(pastActivation[i]) == M_PRESS && !mse::Functions::Vector::isInList(pastActivation[i], getKeys))
					keybinder->simulateKey(keyAssoc->at(pastActivation[i]), P_RELEASE);
			}
			pastActivation.clear();
			pastActivation = pastActivationBuffer;
		}
		else if (status == sf::Socket::Disconnected)
		{
			break;
		}
	}
	GUI::Widget::getWidgetByID<GUI::Button>("connectBtn")->setText("Connect", "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3);
	addLog("<color:255,0,0>Vita disconnected<color:255,255,255>");
	canConnect = true;
}

int main()
{
	mse::System::Path::basePaths.push_back("");
	std::ofstream out("log.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	mse::Functions::Coord::width = 800; mse::Functions::Coord::height = 600;
	mse::Functions::Coord::baseWidth = 800; mse::Functions::Coord::baseHeight = 600;
	sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::None);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::RectangleShape windowBorder(sf::Vector2f(798, 598));
	windowBorder.setPosition(1, 1); windowBorder.setFillColor(sf::Color(40, 40, 40)); windowBorder.setOutlineColor(sf::Color::White); windowBorder.setOutlineThickness(1);
	sf::Vertex linetop[] = { sf::Vertex(sf::Vector2f(0, 60)), sf::Vertex(sf::Vector2f(800, 60)) };
	sf::Vertex linemiddle[] = { sf::Vertex(sf::Vector2f(0, 450)), sf::Vertex(sf::Vector2f(800, 450)) };
	sf::Vertex linebottom[] = { sf::Vertex(sf::Vector2f(0, 550)), sf::Vertex(sf::Vector2f(800, 550)) };

	sf::Event sfevent;
	GUI::Container* gui = new GUI::Container(&sfevent, &window, 800, 600);
	GUI::WidgetContainer* mainContainer = gui->createWidgetContainer("main", 1, 0, 0, 800, 600, GUI::ContainerMovement::Fixed, 0, 0);
	GUI::WidgetContainer* mappContainer = gui->createWidgetContainer("mapp", 1, 0, 60, 800, 390, GUI::ContainerMovement::Fixed, 0, 0);
	GUI::WidgetContainer* stgsContainer = gui->createWidgetContainer("stgs", 1, 0, 60, 800, 390, GUI::ContainerMovement::Fixed, 0, 0);
	GUI::WidgetContainer* logsContainer = gui->createWidgetContainer("logs", 1, 0, 450, 800, 100, GUI::ContainerMovement::Fixed, 0, 0);
	GUI::WidgetContainer* bublContainer = gui->createWidgetContainer("bubl", 1, 0, 60, 800, 390, GUI::ContainerMovement::Fixed, 0, 0);
	bool mapDisplayed = true;

	mse::Cursor::Cursor curs(&window);
	mse::Input::KeyBinder keybinder;

	sf::Font font;
	font.loadFromFile("Data/Fonts/weblysleekuil.ttf");

	//Main UI
	gui->createLabel("main", "titleLbl", 10, 10, "VitaPad GUI", "weblysleekuil.ttf", 32, sf::Color::White);
	gui->createLabel("main", "vitapadAuthor", 400, 10, "VitaPad by Rinnegatamante", "weblysleekuil.ttf", 12, sf::Color::White);
	gui->createLabel("main", "clientAuthor", 400, 30, "Client by Sygmei", "weblysleekuil.ttf", 12, sf::Color::White);
	gui->createCheckbox("main", "settingsBtn", 700, 15, "SETTINGS", false);
	gui->createButton("main", "quitBtn", 750, 15, true, true, "QUIT");
	gui->createButton("main", "updateBtn", 600, 560, true, true, "GREY");
	gui->createButton("main", "connectBtn", 400, 560, true, true, "GREY");
	GUI::ButtonEvent* updBtn = GUI::Widget::getWidgetByID<GUI::Button>("updateBtn")->getHook();
	GUI::ButtonEvent* conBtn = GUI::Widget::getWidgetByID<GUI::Button>("connectBtn")->getHook();
	std::thread* tupd = nullptr;

	//Infos UI
	gui->createLabel("mapp", "settingsTitleLbl", 10, 10, "Mapping : ", "weblysleekuil.ttf", 24, sf::Color::Cyan);
	sf::Texture psvitaTex;
	psvitaTex.loadFromFile("Sprites/Images/psvita.png");
	sf::Sprite psvitaSpr;
	psvitaSpr.setTexture(psvitaTex);
	psvitaSpr.setPosition(40, 120);

	//Settings UI
	gui->createLabel("stgs", "settingsTitleLbl", 10, 10, "Settings : ", "weblysleekuil.ttf", 24, sf::Color::Cyan);
	gui->createLabel("stgs", "vitaIpLbl", 30, 50, "Vita's IP : ", "weblysleekuil.ttf", 16, sf::Color::White);
	gui->createTextInput("stgs", "vitaIpInput", 110, 52, "", "weblysleekuil.ttf", 14, sf::Color::White, false, "GREY");
	gui->createLabel("stgs", "vitaPortLbl", 30, 80, "Vita's Port : ", "weblysleekuil.ttf", 16, sf::Color::White);
	gui->createTextInput("stgs", "vitaPortInput", 110, 82, "", "weblysleekuil.ttf", 14, sf::Color::White, false, "GREY");

	//Logs UI
	gui->createLabel("logs", "logsTitleLbl", 10, 10, "Logs : ", "weblysleekuil.ttf", 24, sf::Color::Cyan);
	gui->createLabel("logs", "logsContLbl", 30, 45, "", "weblysleekuil.ttf", 16, sf::Color::White);
	addLog("<color:255,255,255>VitaPad Client started [ <color:0,255,0>Done<color:255,255,255> ]");

	//Bubbles UI
	GUI::Button* currentButton = nullptr;
	bool* waitForInput = new bool;
	*waitForInput = false;
	GUI::Button* waitForInputButton = nullptr;
	sf::Texture selectedBubble; selectedBubble.loadFromFile("Sprites/GUI/Button/BUBBLE/register.png");
	sf::Texture idleBubble; idleBubble.loadFromFile("Sprites/GUI/Button/BUBBLE/idle.png");
	sf::Texture hoverBubble; hoverBubble.loadFromFile("Sprites/GUI/Button/BUBBLE/hover.png");
	sf::Texture pushedBubble; pushedBubble.loadFromFile("Sprites/GUI/Button/BUBBLE/pushed.png");
	std::vector<GUI::Button*> allButtons;
	gui->createButton("bubl", "Up", 75, 74, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Left", 44, 107, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Right", 107, 106, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Down", 75, 123, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "LTrigger", 130, 8, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "RTrigger", 600, 8, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Triangle", 656, 73, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Square", 630, 100, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Cross", 656, 126, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Circle", 683, 100, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Select", 627, 244, true, true, "BUBBLE")->setDisplayed(false);
	gui->createButton("bubl", "Start", 664, 244, true, true, "BUBBLE")->setDisplayed(false);
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Up"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Left"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Right"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Down"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("LTrigger"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("RTrigger"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Triangle"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Square"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Cross"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Circle"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Select"));
	allButtons.push_back(GUI::Widget::getWidgetByID<GUI::Button>("Start"));
	for (int i = 0; i < allButtons.size(); i++)
		allButtons[i]->bindFunction([waitForInput]() { *waitForInput = true; });
	std::vector<BubbleDetector*> allDetectors;
	allDetectors.push_back(new BubbleDetector("Up", 91, 126, 28, 30));
	allDetectors.push_back(new BubbleDetector("Left", 68, 150, 30, 29));
	allDetectors.push_back(new BubbleDetector("Right", 111, 150, 30, 29));
	allDetectors.push_back(new BubbleDetector("Down", 90, 172, 29, 30));
	allDetectors.push_back(new BubbleDetector("LTrigger", 94, 64, 65, 27));
	allDetectors.push_back(new BubbleDetector("RTrigger", 626, 64, 70, 28));
	allDetectors.push_back(new BubbleDetector("Triangle", 672, 124, 27, 27));
	allDetectors.push_back(new BubbleDetector("Square", 645, 150, 27, 27));
	allDetectors.push_back(new BubbleDetector("Cross", 673, 178, 27, 27));
	allDetectors.push_back(new BubbleDetector("Circle", 700, 150, 27, 27));
	allDetectors.push_back(new BubbleDetector("Select", 642, 296, 30, 20));
	allDetectors.push_back(new BubbleDetector("Start", 679, 296, 30, 20));

	mse::Data::DataParser mappingFile;
	mappingFile.parseFile("config.cfg.msd");
	std::vector<std::string> allKeys = mappingFile.getAllAttributes("Buttons", "Keys");
	std::vector<std::string> allActivationType = mappingFile.getAllAttributes("Buttons", "Keys");
	std::map<std::string, std::string> keyAssoc;
	std::map<std::string, int> uniqueActivation;
	for (int i = 0; i < allKeys.size(); i++)
	{
		GUI::Button* assignButtonText = GUI::Widget::getWidgetByID<GUI::Button>(allKeys[i]);
		std::string buttonText;
		mappingFile.getAttribute("Buttons", "Keys", allKeys[i])->getData(&buttonText);
		std::cout << allKeys[i] << " is " << buttonText << std::endl;
		keyAssoc[allKeys[i]] = buttonText;
		if (assignButtonText != nullptr) assignButtonText->setText(buttonText, "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3, sf::Text::Bold);
		uniqueActivation[allKeys[i]] = false;
	}
	for (int i = 0; i < allActivationType.size(); i++)
	{
		std::string actType;
		mappingFile.getAttribute("Buttons", "InputType", allKeys[i])->getData(&actType);
		if (actType == "Click")
			uniqueActivation[allKeys[i]] = M_CLICK;
		else if (actType == "KeyRepeat")
			uniqueActivation[allKeys[i]] = M_KEYREPEAT;
		else if (actType == "Press")
			uniqueActivation[allKeys[i]] = M_PRESS;
	}

	GUI::ButtonEvent* appQuitBool = GUI::Widget::getWidgetByID<GUI::Button>("quitBtn")->getHook();
	bool* appSettingsBool = GUI::Widget::getWidgetByID<GUI::Checkbox>("settingsBtn")->getHook();
	GUI::Widget::getWidgetByID<GUI::Button>("updateBtn")->setText("Save", "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3);
	GUI::Widget::getWidgetByID<GUI::Button>("connectBtn")->setText("Connect", "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3);
	sf::Vector2i grabbedOffset;
	
	std::string vitaIP;
	int vitaPort;
	bool autoconnect;
	mappingFile.getAttribute("Config", "", "ip")->getData(&vitaIP);
	mappingFile.getAttribute("Config", "", "port")->getData(&vitaPort);
	mappingFile.getAttribute("Config", "", "autoconnect")->getData(&autoconnect);

	GUI::Widget::getWidgetByID<GUI::TextInput>("vitaIpInput")->setText(vitaIP);
	GUI::Widget::getWidgetByID<GUI::TextInput>("vitaPortInput")->setText(std::to_string(vitaPort));

	std::thread vitaThread;
	if (autoconnect)
		vitaThread = std::thread(handleEvents, vitaIP, vitaPort, &allKeys, &keyAssoc, &uniqueActivation, &keybinder);

	bool grabbedWindow = false;
	while (window.isOpen())
	{
		if (*waitForInput)
		{
			if (waitForInputButton == nullptr)
			{
				currentButton->setTextureAll(selectedBubble);
				waitForInputButton = currentButton;
			}
			else if (waitForInputButton == currentButton)
			{
				std::string pressedKey = keybinder.getFirstKeyPressed();
				if (pressedKey != "")
				{
					currentButton->setText(pressedKey, "weblysleekuil.ttf", sf::Color::White, 18, true, 0, -3, sf::Text::Bold);
					keyAssoc[currentButton->getID()] = pressedKey;
					*waitForInput = false;
					waitForInputButton = nullptr;
					currentButton->setTextureIdle(idleBubble);
					currentButton->setTextureHover(hoverBubble);
					currentButton->setTexturePushed(pushedBubble);
				}
			}
			else
			{
				*waitForInput = false;
				waitForInputButton->setTextureIdle(idleBubble);
				waitForInputButton->setTextureHover(hoverBubble);
				waitForInputButton->setTexturePushed(pushedBubble);
				waitForInputButton = nullptr;
			}
		}
		while (window.pollEvent(sfevent))
		{
			if (sfevent.type == sf::Event::Closed)
				window.close();
			else if (sfevent.type == sf::Event::KeyPressed)
			{
				if (sfevent.key.code == sf::Keyboard::Escape)
					window.close();
			}
			else if (sfevent.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::getPosition().y - window.getPosition().y < 60 && sf::Mouse::getPosition().x - window.getPosition().x < 680)
				{
					if (sfevent.mouseButton.button == sf::Mouse::Left)
					{
						grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
						grabbedWindow = true;
					}
				}
			}
			else if (sfevent.type == sf::Event::MouseButtonReleased)
			{
				if (sfevent.mouseButton.button == sf::Mouse::Left)
					grabbedWindow = false;
			}
			else if (sfevent.type == sf::Event::MouseMoved)
			{
				if (grabbedWindow)
					window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
			}
		}
		
		
		if (currentButton == nullptr || !currentButton->isHovering(sfevent))
		{
			GUI::Button* selBtn;
			for (int i = 0; i < allDetectors.size(); i++)
			{
				selBtn = allDetectors[i]->update(bublContainer, curs.getX(), curs.getY());
				if (selBtn != nullptr)
				{
					currentButton = selBtn;
					break;
				}
			}
				
		}

		gui->updateAllContainer();
		curs.update();
		if (*conBtn == GUI::ButtonEvent::Clicked)
		{
			vitaIP = GUI::Widget::getWidgetByID<GUI::TextInput>("vitaIpInput")->getText();
			vitaPort = std::stoi(GUI::Widget::getWidgetByID<GUI::TextInput>("vitaPortInput")->getText());

			if (canConnect)
			{
				if (vitaThread.joinable())
					vitaThread.join();
				vitaThread = std::thread(handleEvents, vitaIP, vitaPort, &allKeys, &keyAssoc, &uniqueActivation, &keybinder);
			}
		}
			
		if (*updBtn == GUI::ButtonEvent::Clicked)
		{
			vitaIP = GUI::Widget::getWidgetByID<GUI::TextInput>("vitaIpInput")->getText();
			vitaPort = std::stoi(GUI::Widget::getWidgetByID<GUI::TextInput>("vitaPortInput")->getText());

			mse::Data::DataParser saveFile;
			saveFile.createDataObject("Config");
			saveFile.createBaseAttribute("Config", "", "ip", vitaIP);
			saveFile.createBaseAttribute("Config", "", "port", vitaPort);
			saveFile.createBaseAttribute("Config", "", "autoconnect", autoconnect);
			saveFile.createDataObject("Buttons");
			saveFile.createComplexAttribute("Buttons", "", "InputType");
			for (auto it = uniqueActivation.begin(); it != uniqueActivation.end(); it++)
			{
				if (it->second == M_CLICK)
					saveFile.createBaseAttribute("Buttons", "InputType", it->first, std::string("Click"));
				else if (it->second == M_KEYREPEAT)
					saveFile.createBaseAttribute("Buttons", "InputType", it->first, std::string("KeyRepeat"));
				else if (it->second == M_PRESS)
					saveFile.createBaseAttribute("Buttons", "InputType", it->first, std::string("Press"));
			}
			saveFile.createComplexAttribute("Buttons", "", "Keys");
			for (auto it = keyAssoc.begin(); it != keyAssoc.end(); it++)
				saveFile.createBaseAttribute("Buttons", "Keys", it->first, it->second);
			saveFile.writeFile("config.cfg.msd");
			addLog("<color:255,255,255>Configuration file saved<color:255,255,255>");
		}
		if (*appQuitBool == GUI::ButtonEvent::Pressed) {window.close();}
		if (*appSettingsBool) { mapDisplayed = false; }
		else { mapDisplayed = true; }

		window.clear(sf::Color(40, 40, 40));
		window.draw(windowBorder);
		//gui->drawAllContainer(&window);
		gui->drawContainer("main", &window);
		if (mapDisplayed)
			gui->drawContainer("mapp", &window);
		gui->drawContainer("logs", &window);
		if (!mapDisplayed)
			gui->drawContainer("stgs", &window);
		window.draw(linetop, 2, sf::Lines); window.draw(linemiddle, 2, sf::Lines); window.draw(linebottom, 2, sf::Lines);
		if (mapDisplayed)
		{
			window.draw(psvitaSpr);
			gui->drawContainer("bubl", &window);
		}
		window.draw(*curs.getSprite());
		window.display();
	}
}

void LogQueue::push_back(std::string content)
{
	logContent.push_back(content);
	if (logContent.size() > 2)
		logContent.erase(logContent.begin());
}

void LogQueue::set(std::string content)
{
	logContent[logContent.size() - 1] = content;
}

std::string LogQueue::returnComplexText()
{
	std::string complexText;
	for (int i = 0; i < logContent.size(); i++)
	{
		complexText += logContent[i] + "\n";
	}
	return complexText;
}

BubbleDetector::BubbleDetector(std::string bubbleId, int x, int y, int w, int h)
{
	this->bubbleId = bubbleId;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

GUI::Button* BubbleDetector::update(GUI::WidgetContainer* cont, int x, int y)
{
	if (x >= this->x && x <= this->x + this->w)
	{
		if (y - 60 >= this->y && y - 60 <= this->y + this->h)
		{
			for (int i = 0; i < cont->getNbWidget(); i++)
			{
				cont->getWidgetByInt(i)->setDisplayed(false);
			}
			GUI::Widget::getWidgetByID<GUI::Button>(bubbleId)->setDisplayed(true);
			return GUI::Widget::getWidgetByID<GUI::Button>(bubbleId);
		}
	}
	return nullptr;
}
