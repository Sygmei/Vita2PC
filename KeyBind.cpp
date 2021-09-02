//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "KeyBind.hpp"

namespace mse
{
	namespace Input
	{
		KeyClass::KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type)
		{
			this->key = key;
			this->name = name;
			this->returnChar = returnChar;
			this->type = type;
		}
		sf::Keyboard::Key KeyClass::getKey()
		{
			return this->key;
		}
		std::string KeyClass::getType()
		{
			return this->type;
		}
		std::string KeyClass::getName()
		{
			return this->name;
		}

		KeySim::KeySim(std::string name, int keycode)
		{
			this->name = name;
			this->keycode = keycode;
		}
		std::string KeySim::getName()
		{
			return name;
		}
		int KeySim::getKey()
		{
			return keycode;
		}

		std::string KeyBinder::getActionKey(std::string action)
		{
			if (actionMap.find(action) != actionMap.end())
				return actionMap[action];
			else
				std::cout << "<Error:KeyBind:KeyBinder>[getActionKey] : Can't find key for action : " << action << std::endl;
		}

		KeyClass* KeyBinder::getKey(std::string key)
		{
			if (keyMap.find(key) != keyMap.end())
				return keyMap[key];
			else
				std::cout << "<Error:KeyBind:KeyBinder>[getKey] : Can't find KeyClass for key : " << key << std::endl;
		}

		KeyBinder::KeyBinder()
		{
			//Keys
			//Alpha
			keyMap["A"] = new KeyClass(sf::Keyboard::A, "A", "A", "Alpha");
			keyMap["Z"] = new KeyClass(sf::Keyboard::Z, "Z", "Z", "Alpha");
			keyMap["E"] = new KeyClass(sf::Keyboard::E, "E", "E", "Alpha");
			keyMap["R"] = new KeyClass(sf::Keyboard::R, "R", "E", "Alpha");
			keyMap["T"] = new KeyClass(sf::Keyboard::T, "T", "T", "Alpha");
			keyMap["Y"] = new KeyClass(sf::Keyboard::Y, "Y", "Y", "Alpha");
			keyMap["U"] = new KeyClass(sf::Keyboard::U, "U", "U", "Alpha");
			keyMap["I"] = new KeyClass(sf::Keyboard::I, "I", "I", "Alpha");
			keyMap["O"] = new KeyClass(sf::Keyboard::O, "O", "O", "Alpha");
			keyMap["P"] = new KeyClass(sf::Keyboard::P, "P", "P", "Alpha");
			keyMap["Q"] = new KeyClass(sf::Keyboard::Q, "Q", "Q", "Alpha");
			keyMap["S"] = new KeyClass(sf::Keyboard::S, "S", "S", "Alpha");
			keyMap["D"] = new KeyClass(sf::Keyboard::D, "D", "D", "Alpha");
			keyMap["F"] = new KeyClass(sf::Keyboard::F, "F", "F", "Alpha");
			keyMap["G"] = new KeyClass(sf::Keyboard::G, "G", "G", "Alpha");
			keyMap["H"] = new KeyClass(sf::Keyboard::H, "H", "H", "Alpha");
			keyMap["J"] = new KeyClass(sf::Keyboard::J, "J", "J", "Alpha");
			keyMap["K"] = new KeyClass(sf::Keyboard::K, "K", "K", "Alpha");
			keyMap["L"] = new KeyClass(sf::Keyboard::L, "L", "L", "Alpha");
			keyMap["M"] = new KeyClass(sf::Keyboard::M, "M", "M", "Alpha");
			keyMap["W"] = new KeyClass(sf::Keyboard::W, "W", "W", "Alpha");
			keyMap["X"] = new KeyClass(sf::Keyboard::X, "X", "W", "Alpha");
			keyMap["C"] = new KeyClass(sf::Keyboard::C, "C", "C", "Alpha");
			keyMap["V"] = new KeyClass(sf::Keyboard::V, "V", "V", "Alpha");
			keyMap["B"] = new KeyClass(sf::Keyboard::B, "B", "B", "Alpha");
			keyMap["N"] = new KeyClass(sf::Keyboard::N, "N", "N", "Alpha");
			//Numeric
			keyMap["0"] = new KeyClass(sf::Keyboard::Num0, "0", "0", "Numeric");
			keyMap["1"] = new KeyClass(sf::Keyboard::Num1, "1", "1", "Numeric");
			keyMap["2"] = new KeyClass(sf::Keyboard::Num2, "2", "2", "Numeric");
			keyMap["3"] = new KeyClass(sf::Keyboard::Num3, "3", "3", "Numeric");
			keyMap["4"] = new KeyClass(sf::Keyboard::Num4, "4", "4", "Numeric");
			keyMap["5"] = new KeyClass(sf::Keyboard::Num5, "5", "5", "Numeric");
			keyMap["6"] = new KeyClass(sf::Keyboard::Num6, "6", "6", "Numeric");
			keyMap["7"] = new KeyClass(sf::Keyboard::Num7, "7", "7", "Numeric");
			keyMap["8"] = new KeyClass(sf::Keyboard::Num8, "8", "8", "Numeric");
			keyMap["9"] = new KeyClass(sf::Keyboard::Num9, "9", "9", "Numeric");
			//Numpad
			keyMap["NumPad0"] = new KeyClass(sf::Keyboard::Numpad0, "NumPad0", "0", "NumericNP");
			keyMap["NumPad1"] = new KeyClass(sf::Keyboard::Numpad1, "NumPad1", "1", "NumericNP");
			keyMap["NumPad2"] = new KeyClass(sf::Keyboard::Numpad2, "NumPad2", "2", "NumericNP");
			keyMap["NumPad3"] = new KeyClass(sf::Keyboard::Numpad3, "NumPad3", "3", "NumericNP");
			keyMap["NumPad4"] = new KeyClass(sf::Keyboard::Numpad4, "NumPad4", "4", "NumericNP");
			keyMap["NumPad5"] = new KeyClass(sf::Keyboard::Numpad5, "NumPad5", "5", "NumericNP");
			keyMap["NumPad6"] = new KeyClass(sf::Keyboard::Numpad6, "NumPad6", "6", "NumericNP");
			keyMap["NumPad7"] = new KeyClass(sf::Keyboard::Numpad7, "NumPad7", "7", "NumericNP");
			keyMap["NumPad8"] = new KeyClass(sf::Keyboard::Numpad8, "NumPad8", "8", "NumericNP");
			keyMap["NumPad9"] = new KeyClass(sf::Keyboard::Numpad9, "NumPad9", "9", "NumericNP");
			//Arrows
			keyMap["Left"] = new KeyClass(sf::Keyboard::Left, "Left", "", "Arrows");
			keyMap["Right"] = new KeyClass(sf::Keyboard::Right, "Right", "", "Arrows");
			keyMap["Up"] = new KeyClass(sf::Keyboard::Up, "Up", "", "Arrows");
			keyMap["Down"] = new KeyClass(sf::Keyboard::Down, "Down", "", "Arrows");
			//Functions
			keyMap["F1"] = new KeyClass(sf::Keyboard::F1, "F1", "", "Functions");
			keyMap["F2"] = new KeyClass(sf::Keyboard::F2, "F2", "", "Functions");
			keyMap["F3"] = new KeyClass(sf::Keyboard::F3, "F3", "", "Functions");
			keyMap["F4"] = new KeyClass(sf::Keyboard::F4, "F4", "", "Functions");
			keyMap["F5"] = new KeyClass(sf::Keyboard::F5, "F5", "", "Functions");
			keyMap["F6"] = new KeyClass(sf::Keyboard::F6, "F6", "", "Functions");
			keyMap["F7"] = new KeyClass(sf::Keyboard::F7, "F7", "", "Functions");
			keyMap["F8"] = new KeyClass(sf::Keyboard::F8, "F8", "", "Functions");
			keyMap["F9"] = new KeyClass(sf::Keyboard::F9, "F9", "", "Functions");
			keyMap["F10"] = new KeyClass(sf::Keyboard::F10, "F10", "", "Functions");
			keyMap["F11"] = new KeyClass(sf::Keyboard::F11, "F11", "", "Functions");
			keyMap["F12"] = new KeyClass(sf::Keyboard::F12, "F12", "", "Functions");
			//Others
			keyMap["Add"] = new KeyClass(sf::Keyboard::Add, "Add", "+", "Others");
			keyMap["BackSlash"] = new KeyClass(sf::Keyboard::BackSlash, "BackSlash", "\\", "Others");
			keyMap["BackSpace"] = new KeyClass(sf::Keyboard::BackSpace, "BackSpace", "", "Others");
			keyMap["Comma"] = new KeyClass(sf::Keyboard::Comma, "Comma", ",", "Others");
			keyMap["Dash"] = new KeyClass(sf::Keyboard::Dash, "Dash", "-", "Others");
			keyMap["Delete"] = new KeyClass(sf::Keyboard::Delete, "Delete", "", "Others");
			keyMap["Divide"] = new KeyClass(sf::Keyboard::Divide, "Divide", "/", "Others");
			keyMap["End"] = new KeyClass(sf::Keyboard::End, "End", "", "Others");
			keyMap["Equal"] = new KeyClass(sf::Keyboard::Equal, "Equal", "=", "Others");
			keyMap["Escape"] = new KeyClass(sf::Keyboard::Escape, "Escape", "", "Others");
			keyMap["Home"] = new KeyClass(sf::Keyboard::Home, "Home", "", "Others");
			keyMap["Insert"] = new KeyClass(sf::Keyboard::Insert, "Insert", "", "Others");
			keyMap["LAlt"] = new KeyClass(sf::Keyboard::LAlt, "LAlt", "", "Others");
			keyMap["LBracket"] = new KeyClass(sf::Keyboard::LBracket, "LBracket", "[", "Others");
			keyMap["LControl"] = new KeyClass(sf::Keyboard::LControl, "LControl", "", "Others");
			keyMap["LShift"] = new KeyClass(sf::Keyboard::LShift, "LShift", "", "Others");
			keyMap["Menu"] = new KeyClass(sf::Keyboard::Menu, "Menu", "", "Others");
			keyMap["Multiply"] = new KeyClass(sf::Keyboard::Multiply, "Multiply", "*", "Others");
			keyMap["PageDown"] = new KeyClass(sf::Keyboard::PageDown, "PageDown", "", "Others");
			keyMap["PageUp"] = new KeyClass(sf::Keyboard::PageUp, "PageUp", "", "Others");
			keyMap["Pause"] = new KeyClass(sf::Keyboard::Pause, "Pause", "", "Others");
			keyMap["Period"] = new KeyClass(sf::Keyboard::Period, "Period", ".", "Others");
			keyMap["Quote"] = new KeyClass(sf::Keyboard::Quote, "Quote", "\"", "Others");
			keyMap["RAlt"] = new KeyClass(sf::Keyboard::RAlt, "RAlt", "", "Others");
			keyMap["RBracket"] = new KeyClass(sf::Keyboard::RBracket, "RBracket", "]", "Others");
			keyMap["RControl"] = new KeyClass(sf::Keyboard::RControl, "RControl", "", "Others");
			keyMap["Return"] = new KeyClass(sf::Keyboard::Return, "Return", "\n", "Others");
			keyMap["RShift"] = new KeyClass(sf::Keyboard::RShift, "RShift", "", "Others");
			keyMap["RSystem"] = new KeyClass(sf::Keyboard::RSystem, "RSystem", "", "Others");
			keyMap["SemiColon"] = new KeyClass(sf::Keyboard::SemiColon, "SemiColon", ";", "Others");
			keyMap["Slash"] = new KeyClass(sf::Keyboard::Slash, "Slash", "/", "Others");
			keyMap["Space"] = new KeyClass(sf::Keyboard::Space, "Space", " ", "Others");
			keyMap["Substract"] = new KeyClass(sf::Keyboard::Subtract, "Substract", "-", "Others");
			keyMap["Tab"] = new KeyClass(sf::Keyboard::Tab, "Tab", "    ", "Others");
			keyMap["Tilde"] = new KeyClass(sf::Keyboard::Tilde, "Tilde", "~", "Others");

			//Keys Sim
			//Alpha
			keySimMap["A"] = new KeySim("A", 0x41);
			keySimMap["Z"] = new KeySim("Z", 0x5A);
			keySimMap["E"] = new KeySim("E", 0x45);
			keySimMap["R"] = new KeySim("R", 0x52);
			keySimMap["T"] = new KeySim("T", 0x54);
			keySimMap["Y"] = new KeySim("Y", 0x59);
			keySimMap["U"] = new KeySim("U", 0x55);
			keySimMap["I"] = new KeySim("I", 0x49);
			keySimMap["O"] = new KeySim("O", 0x4F);
			keySimMap["P"] = new KeySim("P", 0x50);
			keySimMap["Q"] = new KeySim("Q", 0x51);
			keySimMap["S"] = new KeySim("S", 0x53);
			keySimMap["D"] = new KeySim("D", 0x44);
			keySimMap["F"] = new KeySim("F", 0x46);
			keySimMap["G"] = new KeySim("G", 0x47);
			keySimMap["H"] = new KeySim("H", 0x48);
			keySimMap["J"] = new KeySim("J", 0x4A);
			keySimMap["K"] = new KeySim("K", 0x4B);
			keySimMap["L"] = new KeySim("L", 0x4C);
			keySimMap["M"] = new KeySim("M", 0x4D);
			keySimMap["W"] = new KeySim("W", 0x57);
			keySimMap["X"] = new KeySim("X", 0x58);
			keySimMap["C"] = new KeySim("C", 0x43);
			keySimMap["V"] = new KeySim("V", 0x56);
			keySimMap["B"] = new KeySim("B", 0x42);
			keySimMap["N"] = new KeySim("N", 0x4E);
			//Numeric
			keySimMap["0"] = new KeySim("0", 0x30);
			keySimMap["1"] = new KeySim("1", 0x31);
			keySimMap["2"] = new KeySim("2", 0x32);
			keySimMap["3"] = new KeySim("3", 0x33);
			keySimMap["4"] = new KeySim("4", 0x34);
			keySimMap["5"] = new KeySim("5", 0x35);
			keySimMap["6"] = new KeySim("6", 0x36);
			keySimMap["7"] = new KeySim("7", 0x37);
			keySimMap["8"] = new KeySim("8", 0x38);
			keySimMap["9"] = new KeySim("9", 0x39);
			//Numpad
			keySimMap["Numpad0"] = new KeySim("Numpad0", 0x60);
			keySimMap["Numpad1"] = new KeySim("Numpad1", 0x61);
			keySimMap["Numpad2"] = new KeySim("Numpad2", 0x62);
			keySimMap["Numpad3"] = new KeySim("Numpad3", 0x63);
			keySimMap["Numpad4"] = new KeySim("Numpad4", 0x64);
			keySimMap["Numpad5"] = new KeySim("Numpad5", 0x65);
			keySimMap["Numpad6"] = new KeySim("Numpad6", 0x66);
			keySimMap["Numpad7"] = new KeySim("Numpad7", 0x67);
			keySimMap["Numpad8"] = new KeySim("Numpad8", 0x68);
			keySimMap["Numpad9"] = new KeySim("Numpad9", 0x69);
			//Arrows
			keySimMap["Left"] = new KeySim("Left", 0x25);
			keySimMap["Right"] = new KeySim("Right", 0x27);
			keySimMap["Up"] = new KeySim("Up", 0x26);
			keySimMap["Down"] = new KeySim("Down", 0x28);
			//Functions
			keySimMap["F1"] = new KeySim("F1", 0x70);
			keySimMap["F2"] = new KeySim("F2", 0x71);
			keySimMap["F3"] = new KeySim("F3", 0x72);
			keySimMap["F4"] = new KeySim("F4", 0x73);
			keySimMap["F5"] = new KeySim("F5", 0x74);
			keySimMap["F6"] = new KeySim("F6", 0x75);
			keySimMap["F7"] = new KeySim("F7", 0x76);
			keySimMap["F8"] = new KeySim("F8", 0x77);
			keySimMap["F9"] = new KeySim("F9", 0x78);
			keySimMap["F10"] = new KeySim("F10", 0x79);
			keySimMap["F11"] = new KeySim("F11", 0x7A);
			keySimMap["F12"] = new KeySim("F12", 0x7B);
			//Others
			keySimMap["Add"] = new KeySim("Add", 0x6B);
			keySimMap["BackSlash"] = new KeySim("BackSlash", 0xDC);
			keySimMap["BackSpace"] = new KeySim("BackSpace", 0x08);
			keySimMap["Comma"] = new KeySim("Comma", 0xBC);
			keySimMap["Dash"] = new KeySim("Dash", 0xBD);
			keySimMap["Delete"] = new KeySim("Delete", 0x2E);
			keySimMap["Divide"] = new KeySim("Divide", 0x6F);
			keySimMap["End"] = new KeySim("End", 0x23);
			keySimMap["Equal"] = new KeySim("Equal", 0xBB);
			keySimMap["Escape"] = new KeySim("Escape", 0x1B);
			keySimMap["Home"] = new KeySim("Home", 0x24);
			keySimMap["Insert"] = new KeySim("Insert", 0x2D);
			keySimMap["LAlt"] = new KeySim("LAlt", 0xA4);
			keySimMap["LBracket"] = new KeySim("LBracket", 0xDB);
			keySimMap["LControl"] = new KeySim("LControl", 0xA2);
			keySimMap["LShift"] = new KeySim("LShift", 0xA0);
			keySimMap["Menu"] = new KeySim("Menu", 0xA4);
			keySimMap["Multiply"] = new KeySim("Multiply", 0x6A);
			keySimMap["PageDown"] = new KeySim("PageDown", 0x22);
			keySimMap["PageUp"] = new KeySim("PageUp", 0x21);
			keySimMap["Pause"] = new KeySim("Pause", 0x13);
			keySimMap["Period"] = new KeySim("Period", 0xBE);
			keySimMap["Quote"] = new KeySim("Quote", 0xDE);
			keySimMap["RAlt"] = new KeySim("RAlt", 0xA5);
			keySimMap["RBracket"] = new KeySim("RBracket", 0xDD);
			keySimMap["RControl"] = new KeySim("RControl", 0xA3);
			keySimMap["Return"] = new KeySim("Return", 0x0D);
			keySimMap["RShift"] = new KeySim("RShift", 0xA1);
			keySimMap["RSystem"] = new KeySim("RSystem", 0x00); //Unknown
			keySimMap["SemiColon"] = new KeySim("SemiColon", 0xBA);
			keySimMap["Slash"] = new KeySim("Slash", 0xBF);
			keySimMap["Space"] = new KeySim("Space", 0x20);
			keySimMap["Substract"] = new KeySim("Substract", 0x6D);
			keySimMap["Tab"] = new KeySim("Tab", 0x09);
			keySimMap["Tilde"] = new KeySim("Tilde", 0xC0);
		}

		void KeyBinder::setEnabled(bool state)
		{
			binderEnabled = state;
		}

		void KeyBinder::update()
		{
			if (binderEnabled)
			{
				typedef std::map<std::string, std::string>::iterator it_type;
				for (it_type iterator = actionMap.begin(); iterator != actionMap.end(); iterator++)
				{
					previousActionMap[iterator->first] = currentActionMap[iterator->first];
					currentActionMap[iterator->first] = sf::Keyboard::isKeyPressed(getKey(iterator->second)->getKey());
					if (!currentActionMap[iterator->first] && previousActionMap[iterator->first])
					{
						if (Functions::Map::keyInMap(iterator->first, actionDelayer))
						{
							actionDelayer[iterator->first] = 0;
						}
					}
				}
			}
		}

		bool KeyBinder::isActionReleased(std::string action)
		{
			if (binderEnabled)
			{
				if (!currentActionMap[action] && previousActionMap[action])
					return true;
				else
					return false;
			}
			else
				return false;
		}

		bool KeyBinder::isActionEnabled(std::string action)
		{
			if (binderEnabled)
			{
				if (currentActionMap[action])
				{
					if (Functions::Map::keyInMap(action, actionDelayer))
					{
						if (Time::getTickSinceEpoch() - actionDelayer[action] > baseActionDelayer[action])
						{
							actionDelayer[action] = Time::getTickSinceEpoch();
							return true;
						}
						else
							return false;
					}
					else
						return true;
				}
				else
					return false;
			}
			else
				return false;
		}

		bool KeyBinder::isActionDisabled(std::string action)
		{
			if (binderEnabled)
			{
				if (currentActionMap[action])
					return false;
				else
					return true;
			}
			else
				return true;
		}

		void KeyBinder::setActionDelay(std::string action, int delay)
		{
			baseActionDelayer[action] = delay;
			actionDelayer[action] = 0;
		}

		bool KeyBinder::isKeyPressed(std::string key)
		{
			return sf::Keyboard::isKeyPressed(getKey(key)->getKey());;
		}

		std::string KeyBinder::getFirstKeyPressed()
		{
			for (auto it = keyMap.begin(); it != keyMap.end(); it++)
			{
				if (sf::Keyboard::isKeyPressed(it->second->getKey()))
					return it->second->getName();
			}
			return "";
		}

		void KeyBinder::connectAction(std::string action, std::string key) {
			actionMap[action] = key;
		}

		void KeyBinder::simulateKey(std::string key, int mode)
		{
			INPUT ip;
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0;
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;

			ip.ki.wVk = keySimMap[key]->getKey();
			if (mode == 0x00 || mode == 0x01)
			{
				ip.ki.dwFlags = 0;
				SendInput(1, &ip, sizeof(INPUT));
			}
			
			if (mode == 0x00 || mode == 0x02)
			{
				ip.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &ip, sizeof(INPUT));
			}
		}

		bool KeyBinder::isActionToggled(std::string action)
		{
			if (binderEnabled)
			{
				if (currentActionMap[action] && !previousActionMap[action])
					return true;
				else
					return false;
			}
			else
				return false;
		}
	}
}

PsVitaKeys::PsVitaKeys()
{
	//DPad / Select / Start
	bitmasks[0]["Select"] = 1;
	bitmasks[0]["Start"] = 8;
	bitmasks[0]["Up"] = 16;
	bitmasks[0]["Right"] = 32;
	bitmasks[0]["Down"] = 64;
	bitmasks[0]["Left"] = -128;

	//Buttons & Triggers
	bitmasks[1]["LTrigger"] = 1;
	bitmasks[1]["RTrigger"] = 2;
	bitmasks[1]["Triangle"] = 16;
	bitmasks[1]["Circle"] = 32;
	bitmasks[1]["Cross"] = 64;
	bitmasks[1]["Square"] = -128;

	//MenuOpened
	bitmasks[2]["MenuOpened"] = 1;
}

std::vector<std::string> PsVitaKeys::getPressedKeys(char* data)
{
	std::vector<std::string> pressedKeys;
	for (int i = 0; i < bitmasks.size(); i++)
	{
		int currentBitcheck = data[i];
		for (auto it = bitmasks[i].begin(); it != bitmasks[i].end(); it++)
		{
			if (it->second & currentBitcheck)
				pressedKeys.push_back(it->first);
		}
	}
	return pressedKeys;
}
