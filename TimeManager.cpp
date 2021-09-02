//Author : Sygmei
//Key : 976938ef7d46c286a2027d73f3a99467bcfa8ff0c1e10bd0016139744ef5404f4eb4d069709f9831f6de74a094944bf0f1c5bf89109e9855290336a66420376f

#include "TimeManager.hpp"

namespace mse
{
	namespace Time
	{
		//TimeMonitor
		void TimeMonitor::startTick(std::string id)
		{
			chronoSMap[id] = std::chrono::high_resolution_clock::now();
		}
		void TimeMonitor::endTick(std::string id)
		{
			chronoEMap[id] = std::chrono::high_resolution_clock::now();
			chronoRMap[id] = std::chrono::duration_cast<std::chrono::microseconds>(chronoEMap[id] - chronoSMap[id]);
			std::cout << "#PROFILER : " << id << " took " << chronoRMap[id].count() << " microseconds to execute" << std::endl;
		}
		void TimeMonitor::summary()
		{
			std::cout << "##### FULL PROFILER SUMMARY #####" << std::endl;
			std::string key;
			std::chrono::microseconds value;
			std::chrono::microseconds totalSec;
			for (auto iterator = chronoRMap.begin(); iterator != chronoRMap.end(); iterator++) {
				key = iterator->first;
				value = iterator->second;
				std::cout << "     #> " << key << " took " << value.count() << " microseconds to execute" << std::endl;
				totalSec += value;
				if (chronoCMap.find(key) == chronoCMap.end()) {
					chronoCMap[key] = value;
				}
				else {
					chronoCMap[key] += value;
				}
				if (chronoOMap.find(key) == chronoOMap.end()) {
					chronoOMap[key] = 1;
				}
				else {
					chronoOMap[key]++;
				}

			}
			std::cout << "    #>> " << "Loop elapsed in " << totalSec.count() << " microseconds" << std::endl;
			std::cout << "##### END OF PROFILER SUMMARY #####" << std::endl;
			chronoSMap.clear();
			chronoEMap.clear();
			chronoRMap.clear();
		}
		void TimeMonitor::endSummary()
		{
			std::cout << "##### FULL PROFILER END SUMMARY #####" << std::endl;
			std::string key;
			std::chrono::microseconds value;
			std::chrono::microseconds totalSec;
			for (auto iterator = chronoCMap.begin(); iterator != chronoCMap.end(); iterator++) {
				key = iterator->first;
				value = iterator->second;
				std::cout << "    #> " << key << " took " << value.count() << " microseconds in total and has been called " << chronoOMap[key] << " times" << std::endl;
				std::cout << "        #>> (Ratio:" << chronoOMap[key] * value.count() << ")" << std::endl;
				totalSec += value;
			}
			std::cout << "    #>>> " << "Operation elapsed in " << totalSec.count() << " microseconds" << std::endl;
			std::cout << "##### END OF PROFILER END SUMMARY #####" << std::endl;
			chronoSMap.clear();
			chronoEMap.clear();
			chronoRMap.clear();
			chronoCMap.clear();
			chronoOMap.clear();
		}

		//FPS Counter
		void FPSCounter::tick()
		{
			if (getTickSinceEpoch() - lastTick <= 1000)
			{
				fpsCounter++;
			}
			else
			{
				saveFPS = fpsCounter;
				fpsCounter = 0;
				lastTick = getTickSinceEpoch();
				canUpdateFPS = true;
			}
		}
		void FPSCounter::loadFont(sf::Font &font)
		{
			text.setFont(font);
			text.setCharacterSize(24);
			text.setColor(sf::Color::White);
		}
		sf::Text FPSCounter::getFPS()
		{
			if (canUpdateFPS)
			{
				canUpdateFPS = false;
				text.setString(std::to_string(saveFPS) + " FPS");
				return text;
			}
			else
			{
				return text;
			}
		}

		//Chronometer
		Chronometer::Chronometer()
		{

		}
		void Chronometer::start() {
			chronoStart = std::chrono::high_resolution_clock::now();
			chronoCurrent = std::chrono::high_resolution_clock::now();
			started = true;
		}
		void Chronometer::stop() {
			started = false;
		}
		unsigned long long int Chronometer::getTime() {
			if (started) chronoCurrent = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(chronoCurrent - chronoStart).count();
		}
		void Chronometer::setLimit(unsigned long long int limit) {
			this->limit = limit;
		}
		bool Chronometer::limitExceeded() {
			std::cout << "Limit : " << limit << std::endl;
			std::cout << "Current : " << this->getTime() << std::endl;
			return (this->getTime() > limit);
		}

		double getTickSinceEpoch()
		{
			return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
		}

		double getTickSinceEpochMicro()
		{
			return std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1);
		}
	}
}