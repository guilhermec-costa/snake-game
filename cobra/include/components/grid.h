#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include "components/grid.h"
#include "components/collider2d.h"
#include <iostream>
#include <vector>

class Grid {
public:
	Grid(SDL_Renderer* renderer, const unsigned int n_cells,
		const unsigned int cell_width, const unsigned int cell_height, RGBA outline_color
	);
	~Grid();
	void update();
	void render(SDL_Renderer* renderer);
	void paint(SDL_Renderer* renderer, const SDL_Rect* rect, RGBA color) const;
	unsigned int m_cell_width;
	unsigned int m_cell_height;
	RGBA m_outline_color;
	Uint32* m_buffer;
	SDL_Rect* root_rect;
private:
	std::vector<SDL_Texture*> m_textures;
};

