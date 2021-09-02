#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include <openssl/crypto.h>
#include <openssl/sha.h>
#include <boost/filesystem.hpp>

#include "GUI.hpp"
#include "Cursor.hpp"
#include "KeyBind.hpp"
#include "RichText.hpp"
#include "CurlFunctions.hpp"
#include "tinydir.h"


class LogQueue
{
	private:
		std::vector<std::string> logContent;
	public:
		void push_back(std::string content);
		void set(std::string content);
		std::string returnComplexText();
};

class BubbleDetector
{
	private:
		int x;
		int y;
		int w;
		int h;
		std::string bubbleId;
		bool show;
	public:
		BubbleDetector(std::string bubbleId, int x, int y, int w, int h);
		GUI::Button* update(GUI::WidgetContainer* cont, int x, int y);
};

void addLog(std::string content);
void setLog(std::string content);
int main();