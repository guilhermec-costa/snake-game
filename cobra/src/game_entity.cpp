#include "game_entity.h"
#include <iostream>

Game_Entity::Game_Entity(SDL_Window* window, SDL_Renderer* renderer)
	: m_texture_component(nullptr), m_renderer(renderer),
	m_visibility(Visibility::VISIBLE), m_status(NOT_ACTIVE),
	m_window(window), m_type(Entity_Type::GENERAL)
{}

Game_Entity::~Game_Entity()
{
	delete m_texture_component;
	for (const Collider2D* collider : m_colliders)
	{
		delete collider;
	}
}

void Game_Entity::add_texture_component(const char* path, RGBA rgba) { m_texture_component = new Texture_Component(m_renderer, path, rgba); }
void Game_Entity::add_collider2D(Cobra_Rect* rect) { m_colliders.push_back(new Collider2D(rect)); }
void Game_Entity::set_visibility(Visibility visibility) { m_visibility = visibility; }
void Game_Entity::associate_window(SDL_Window* window) { m_window = window; }

Texture_Component* Game_Entity::get_texture_component() const { return m_texture_component; }
Visibility Game_Entity::is_visible() const { return m_visibility; }
Collider2D* Game_Entity::get_collider(const unsigned int index) const { return m_colliders[index]; }
Status Game_Entity::get_status() const { return m_status; }