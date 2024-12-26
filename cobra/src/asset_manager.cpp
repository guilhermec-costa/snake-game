#include "asset_manager.h"
#include "logger.h"
#include <SDL2/SDL_image.h>

Asset_Manager::Asset_Manager() {};
Asset_Manager::Asset_Manager(const Asset_Manager&) {}
inline Asset_Manager* Asset_Manager::operator=(const Asset_Manager&)
{
	return this;
}

Asset_Manager& Asset_Manager::get_instance()
{
	static Asset_Manager* instance = new Asset_Manager();
	return *instance;
}

void Asset_Manager::load_asset(const char* path)
{
	auto loaded_asset = m_surfaces.find(path);
	std::string message;
	message = "Asset on ";

	if (loaded_asset != m_surfaces.end())
	{
		message.append(path);
		message += "is already loaded";
		Logger::s_get_instance().log_err(message.append(path));
		return;
	}
	SDL_Surface* sfc = IMG_Load(path);
	m_surfaces.insert(std::make_pair(path, sfc));

	message.append(path);
	message += " loaded";
	Logger::s_get_instance().log(message);
}

SDL_Surface* Asset_Manager::get_asset(const char* path)
{
	auto loaded_asset = m_surfaces.find(path);
	if (loaded_asset == m_surfaces.end())
	{
		load_asset(path);
	}

	return m_surfaces[path];
}