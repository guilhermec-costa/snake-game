#pragma once
#include "game.h"
#include <SDL2/SDL_video.h>
#include "snake_entity.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include "cobra_events.h"
#include "game_entity.h"
#include "vector"
#include <unordered_map>
#include "components/texture_component.h"

#define COBRA_SUBSYSTEMS (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)

struct Vector2 {
	int x;
	int y;
};

class Sdl_API : public IGame {
public:
	Sdl_API();
	void render() override;
	void update() override;
	void terminate() override;
	void handle_events() override;
	void setup_window(const char* title, int x, int y, int w, int h);
	//void add_text_component(const char* text, SDL_Color color, std::string identifier);
	inline void add_grid(Grid* grid) { m_bg_grid = grid; };
	Vector2 get_win_dimensions() const;
	void setup_renderer(SDL_RendererFlags);
	void init_subsystems();
	inline void set_active_snake(Snake_Entity* snake) {
		m_snake = snake;
	}
	bool check_integrity() const;
	void add_entities(const std::vector<const Game_Entity*>&);
	SDL_Renderer* get_renderer() const;
	SDL_Window* get_window() const;
	Texture_Component* texture_component;
	Snake_Entity* m_snake;
private:
	void init_event_handlers();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event* m_event_src;
	Vector2 m_window_dimensions;
	std::vector<const Game_Entity*> m_entities;
	std::unordered_map<std::string, SDL_Texture*> m_texts;
	Cobra_EVENTS m_events;
	Grid* m_bg_grid;
};
