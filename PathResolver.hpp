#pragma once

#include <string>
#include <typeinfo>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

#include "DataParser.hpp"

namespace mse
{
	namespace System
	{
		namespace Loaders
		{
			extern std::function<int(sf::Texture*, std::string)> textureLoader;
			extern std::function<int(Data::DataParser*, std::string)> dataLoader;
			extern std::function<int(sf::Font*, std::string)> fontLoader;
			extern std::function<int(std::vector<std::string>*, std::string)> dirPathLoader;
			extern std::function<int(std::vector<std::string>*, std::string)> filePathLoader;
		}
		class Path
		{
			private:
				std::string path;
			public:
				Path();
				Path(const Path& path);
				Path(std::string path);
				Path add(std::string path);
				std::string toString() const;
				template <typename R, typename F>
				R* loadResource(R* resource, F lambda);
				static std::vector<std::string> basePaths;
		};
		template<typename R>
		inline bool Path::checkType(R type, std::string expectedType)
		{
			return (std::string(typeid(R).name()) == expectedType);
		}
		template<typename R, typename F>
		inline R * Path::loadResource(R* resource, F lambda)
		{
			bool fullLoad = (basePaths.size() > 0) ? true : false;
			for (int i = 0; i < basePaths.size(); i++)
			{
				std::cout << "Testing Path : " << basePaths[i] + "/" + this->path << std::endl;
				int loadResponse = 0;
				try
				{
					loadResponse = lambda(resource, basePaths[i] + ((basePaths[i] != "") ? "/" : "") + this->path);
				}
				catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				if (loadResponse == 1)
					return resource;
				else if (loadResponse == 0)
					fullLoad = false;
			}
			if (fullLoad)
				return resource;
			else
			{
				std::cout << "<Error:PathResolver:Path>[loadResource] : Can't find resource : " << this->path << std::endl;
				return nullptr;
			}
		}
	}
}
