#pragma once
#include "unordered_map"
#include <SDL2/SDL_surface.h>

class Asset_Manager {
private:
	Asset_Manager();
	Asset_Manager(const Asset_Manager&);
	inline Asset_Manager* operator=(const Asset_Manager&);
	std::unordered_map<const char*, SDL_Surface*> m_surfaces;
public:
	static Asset_Manager& get_instance();
	void load_asset(const char*);
	SDL_Surface* get_asset(const char*);
};
