//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

#include "DataParser.hpp"
#include "TimeManager.hpp"

class PsVitaKeys {
	private:
		std::map<int, std::map<std::string, int>> bitmasks;
	public:
		PsVitaKeys();
		std::vector<std::string> getPressedKeys(char* data);
};

namespace mse
{
	namespace Input
	{
		class KeyClass
		{
			private:
				sf::Keyboard::Key key;
				std::string name;
				std::string returnChar;
				std::string type;
			public:
				KeyClass(sf::Keyboard::Key key, std::string name, std::string returnChar, std::string type);
				sf::Keyboard::Key getKey();
				std::string getType();
				std::string getName();
		};

		class KeySim
		{
			private:
				std::string name;
				int keycode;
			public:
				KeySim(std::string name, int keycode);
				std::string getName();
				int getKey();
		};

		class KeyBinder
		{
			private:
				std::map<std::string, std::string> actionMap;
				std::map<std::string, KeyClass*> keyMap;
				std::map<std::string, KeySim*> keySimMap;
				std::map<std::string, bool> currentActionMap;
				std::map<std::string, bool> previousActionMap;
				std::map<std::string, int> baseActionDelayer;
				std::map<std::string, unsigned long long int> actionDelayer;
				std::string getActionKey(std::string action);
				KeyClass* getKey(std::string key);
				bool binderEnabled;

			public:
				KeyBinder();
				void connectAction(std::string action, std::string key);
				void simulateKey(std::string key, int mode);
				bool isActionToggled(std::string action);
				bool isActionReleased(std::string action);
				bool isActionEnabled(std::string action);
				bool isActionDisabled(std::string action);
				void setActionDelay(std::string action, int delay);
				bool isKeyPressed(std::string key);
				std::string getFirstKeyPressed();
				void update();
				void setEnabled(bool state);
		};
	}
}