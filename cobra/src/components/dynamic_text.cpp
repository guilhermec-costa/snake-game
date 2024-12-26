#include "components/dynamic_text.h"
#include "logger.h"

Dynamic_Text::Dynamic_Text(SDL_Renderer* renderer)
	: m_renderer(renderer), m_content_texture(nullptr)
{
	m_font = TTF_OpenFont("C:\\Users\\guico\\source\\repos\\cpp-fundamentals\\cobra\\assets\\fonts\\Minecraft.ttf", 40);
	if (m_font == nullptr)
	{
		std::string err;
		err.append("Failed to load font. ");
		err.append(SDL_GetError());
		Logger::s_get_instance().log_err(err);
	}
}

void Dynamic_Text::update(const std::string& content, SDL_Color color)
{
	SDL_Surface* score_sfc = TTF_RenderText_Solid(m_font, content.c_str(), color);
	m_content_texture = SDL_CreateTextureFromSurface(m_renderer, score_sfc);
	SDL_FreeSurface(score_sfc);
}

void Dynamic_Text::render(const SDL_Rect& r) const
{
	SDL_RenderCopy(m_renderer, m_content_texture, NULL, &r);
}
