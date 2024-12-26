#pragma once
#include "game_entity.h"

class Texture_Entity : public Game_Entity
{
public:
	Texture_Entity(SDL_Window* window, SDL_Renderer* renderer)
		: Game_Entity(window, renderer) {};
	void render() const override;
};
