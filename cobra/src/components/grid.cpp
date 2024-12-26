#include "components/grid.h"
#include "iostream"

Grid::Grid(SDL_Renderer* renderer, const unsigned int n_cells,
	const unsigned int cell_width, const unsigned int cell_height, RGBA outlined_color
) : m_cell_width(cell_width), m_cell_height(cell_height), m_outline_color(outlined_color)
{
	m_buffer = new Uint32[cell_width * cell_height];
	root_rect = new SDL_Rect{ 0, 0, 25, 25 };
	for (int i = 0; i <= n_cells; i++)
	{
		SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, cell_width, cell_height);
		m_textures.push_back(texture);
	}
};

Grid::~Grid()
{
	for (const SDL_Texture* texture : m_textures)
		delete texture;

	delete[] m_buffer;
}

void Grid::render(SDL_Renderer* renderer)
{
	SDL_Rect rect = { 0, 0, m_cell_width, m_cell_height };
	for (int y = 0; y < m_cell_height; y++) {
		for (int x = 0; x < m_cell_width; x++) {
			if (x == 0 || x == m_cell_width - 1 || y == 0 || y == m_cell_height - 1) {
				m_buffer[(y * m_cell_width) + x] = m_outline_color.format();
			}
			else
			{
				m_buffer[(y * m_cell_width) + x] = 0;
			}
		}
	}

	for (auto& texture : m_textures) {
		SDL_UpdateTexture(texture, NULL, m_buffer, m_cell_width * sizeof(Uint32));
		SDL_RenderCopy(renderer, texture, NULL, &rect);
		if (rect.x < 800 - 25) {
			rect.x += 25;
		}
		else {
			rect.x = 0;
			rect.y += 25;
		}
	}
}

void Grid::paint(SDL_Renderer* renderer, const SDL_Rect* rect, RGBA color) const
{
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
	SDL_RenderFillRect(renderer, rect);
}

