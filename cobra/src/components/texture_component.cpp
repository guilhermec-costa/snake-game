#include "components/texture_component.h"
#include "components/grid.h"
#include "asset_manager.h"
#include <SDL2/SDL_pixels.h>
#include "iostream"

Uint32 RGBA::format() const
{
	Uint32 color = this->R;
	color <<= 8;
	color += this->G;
	color <<= 8;
	color += this->B;
	color <<= 8;
	color += this->A;

	return color;
}

Cobra_Rect::Cobra_Rect(
	int x = 0, int y = 0,
	int w = 0, int h = 0
)
{
	this->m_position.set(x, y);
	this->m_dimensions.set(w, h);
	this->generate_SDL_rect();
}

Texture_Component::~Texture_Component()
{
	delete m_src_fraction_rect;
	delete m_render_target_rect;
	delete m_texture;
}

void Cobra_Rect::Dimensions::set(int w, int h)
{
	this->w = w;
	this->h = h;
}

void Cobra_Rect::Position::set(int xpos, int ypos)
{
	x = xpos;
	y = ypos;
}

void Cobra_Rect::generate_SDL_rect()
{
	if (m_position.x == NULL && m_position.y == NULL &&
		m_dimensions.w == NULL && m_dimensions.h == NULL
		)
	{
		m_SDL_rect = NULL;
		return;
	}
	m_SDL_rect = new SDL_Rect{
		this->m_position.x,
		this->m_position.y,
		this->m_dimensions.w,
		this->m_dimensions.h
	};
}

Texture_Component::Texture_Component(SDL_Renderer* renderer, const char* path, RGBA mask)
	: bg_mask(mask), m_src_fraction_rect(new Cobra_Rect()), m_render_target_rect(new Cobra_Rect()), m_renderer(renderer)
{
	SDL_Surface* surface_path = Asset_Manager::get_instance().get_asset(path);
	SDL_SetColorKey(surface_path, SDL_TRUE, SDL_MapRGBA(surface_path->format, mask.R, mask.G, mask.B, mask.A));
	m_texture = SDL_CreateTextureFromSurface(get_renderer(), surface_path);
}

void Texture_Component::render()
{
	SDL_RenderCopy(m_renderer, m_texture, m_src_fraction_rect->get_generated_SDL_rect(), m_render_target_rect->get_generated_SDL_rect());
}

void Texture_Component::set_src_fraction_rect(Cobra_Rect* const src_rect)
{
	if (src_rect != nullptr)
	{
		*m_src_fraction_rect = *src_rect;
	}
	else {
		m_src_fraction_rect = new Cobra_Rect();
	}
};

void Texture_Component::set_render_target_rect(Cobra_Rect* const dst_rect)
{
	if (dst_rect != nullptr)
	{
		*m_render_target_rect = *dst_rect;
	}
	else
	{
		m_render_target_rect = new Cobra_Rect();
	}
}

void Texture_Component::scale(float scale_in)
{
	Cobra_Rect* dst_rect = get_render_target_rect();
	if (scale_in > 0.0f) {
		dst_rect->m_dimensions.set((int)(dst_rect->m_dimensions.w * (1 + scale_in)), (int)(dst_rect->m_dimensions.h * (1 + scale_in)));
	}
	else {
		dst_rect->m_dimensions.set((int)(dst_rect->m_dimensions.w * (1 + scale_in)), (int)(dst_rect->m_dimensions.h * (1 + scale_in)));
	}
	set_render_target_rect(dst_rect);
	dst_rect->generate_SDL_rect();
}

void Texture_Component::rotate(double angle)
{
	const SDL_Rect* src_rect = get_src_fraction_rect()->get_generated_SDL_rect();
	const SDL_Rect* dst_rect = get_render_target_rect()->get_generated_SDL_rect();
	SDL_RenderCopyEx(m_renderer, this->get_texture(), src_rect, dst_rect, angle, NULL, SDL_FLIP_HORIZONTAL);
}

Cobra_Rect* Texture_Component::get_src_fraction_rect() const { return m_src_fraction_rect; }
Cobra_Rect* Texture_Component::get_render_target_rect() const { return m_render_target_rect; }
SDL_Rect* Cobra_Rect::get_generated_SDL_rect() const { return m_SDL_rect; }
inline SDL_Renderer* Texture_Component::get_renderer() const { return m_renderer; }
inline SDL_Texture* Texture_Component::get_texture() const { return m_texture; }
