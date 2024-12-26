#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#define DEFAULT_TEXTURE_DIMENSIONS { 32, 32 }
#define DEFAULT_TEXTURE_POSITIONS { 32, 32 }

typedef struct RGBA {
	Uint8 R;
	Uint8 G;
	Uint8 B;
	Uint8 A;
	Uint32 format() const;
} RGBA;

typedef struct Cobra_Rect
{
	Cobra_Rect(
		int x, int y,
		int w, int h
	);

	typedef struct Dimensions
	{
		int w;
		int h;
		void set(int w, int h);
	} Dimensions;

	typedef struct Position
	{
		int x;
		int y;
		void set(int xpos, int ypos);
	} Position;

	Dimensions m_dimensions;
	Position m_position;
	SDL_Rect* get_generated_SDL_rect() const;
	void generate_SDL_rect();
private:
	SDL_Rect* m_SDL_rect;
};


class Texture_Component {
public:
	Texture_Component(SDL_Renderer*, const char*, RGBA);
	~Texture_Component();
	void render();
	SDL_Renderer* get_renderer() const;
	SDL_Texture* get_texture() const;
	Cobra_Rect* get_src_fraction_rect() const;
	Cobra_Rect* get_render_target_rect() const;
	void set_src_fraction_rect(Cobra_Rect*);
	void set_render_target_rect(Cobra_Rect*);
	void scale(float proportion);
	void rotate(double angle);
private:
	Cobra_Rect* m_src_fraction_rect;
	Cobra_Rect* m_render_target_rect;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	RGBA bg_mask;
};

