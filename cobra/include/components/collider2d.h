#pragma once
#include "components/texture_component.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

class Collider2D {
public:
	Collider2D(Cobra_Rect*);
	~Collider2D();
	bool is_colliding(const SDL_Rect* rect) const;
	void render(SDL_Renderer* renderer) const;
	void render(SDL_Surface* surface, const SDL_Rect* rect, RGBA color) const;
	void place_outline(RGBA color);
	bool m_outlined;
	Cobra_Rect* get_dst_rect() const;
public:
	Cobra_Rect* m_dst_rect;
private:
	RGBA* m_outline_color;
};
