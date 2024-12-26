#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>

class Dynamic_Text {
public:
	Dynamic_Text(SDL_Renderer* renderer);
	void render(const SDL_Rect& r) const;
	void update(const std::string&, SDL_Color color);
private:
	TTF_Font* m_font;
	SDL_Texture* m_content_texture;
	SDL_Renderer* m_renderer;
};
