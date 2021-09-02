#include "PathResolver.hpp"

namespace mse
{
	namespace System
	{
		namespace Loaders
		{
			std::function<int(sf::Texture*, std::string)> textureLoader = [](sf::Texture* obj, std::string path) -> int { return obj->loadFromFile(path); };
			std::function<int(Data::DataParser*, std::string)> dataLoader = [](mse::Data::DataParser* obj, std::string path) -> int { return obj->parseFile(path); };
			std::function<int(sf::Font*, std::string)> fontLoader = [](sf::Font* obj, std::string path) -> int { return obj->loadFromFile(path); };
			std::function<int(std::vector<std::string>*, std::string)> dirPathLoader = [](std::vector<std::string>* obj, std::string path) -> int {
				std::vector<std::string> newPaths = Functions::File::listDirInDir(path);
				obj->insert(obj->end(), newPaths.begin(), newPaths.end());
				return 0x002;
			};
			std::function<int(std::vector<std::string>*, std::string)> filePathLoader = [](std::vector<std::string>* obj, std::string path) -> int {
				std::vector<std::string> newFiles = Functions::File::listFileInDir(path);
				obj->insert(obj->end(), newFiles.begin(), newFiles.end());
				return 0x002;
			};
		}
		std::vector<std::string> Path::basePaths = std::vector<std::string>();
		Path::Path()
		{
			this->path = "";
		}
		Path::Path(const Path& path)
		{
			this->path = path.toString();
		}
		Path::Path(std::string path)
		{
			this->path = path;
		}
		Path Path::add(std::string path)
		{
			return Path(this->path + "/" + path);
		}
		std::string Path::toString() const
		{
			return this->path;
		}
	}
}