#pragma once
#include "components/texture_component.h"
#include "components/collider2d.h"
#include "components/grid.h"
#include <SDL2/SDL_render.h>
#include "vector"

enum Visibility 
{
	NOT_VISIBLE,
	VISIBLE,
};

enum Status
{
	NOT_ACTIVE,
	ACTIVE,
};

enum Entity_Type {
	SNAKE,
	APPLE,
	GENERAL
};

class Game_Entity {

public:
	Game_Entity(SDL_Window* window, SDL_Renderer* renderer);
	~Game_Entity();
	void associate_window(SDL_Window* window);
	void add_texture_component(const char*, RGBA color);
	void add_collider2D(Cobra_Rect* rect);
	virtual void render() const = 0;
	void set_visibility(Visibility visibility);
	Visibility is_visible() const;
	Texture_Component* get_texture_component() const;
	Collider2D* get_collider(const unsigned int index) const;
	inline Entity_Type get_entity_type() const
	{
		return m_type;
	};
	inline void set_entity_type(const Entity_Type& type)
	{
		m_type = type;
	}
public:
	Visibility m_visibility;
	Status get_status() const;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
protected:
	Texture_Component* m_texture_component;
	std::vector<Collider2D*> m_colliders;
	Status m_status;
	Entity_Type m_type;
};
