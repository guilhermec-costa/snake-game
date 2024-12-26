#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "entitites/texture_entity.h"
#include "entitites/snake_entity.h"
#include "Logger.h"
#include <SDL2/SDL_image.h>
#include <cmath>
#include "Sdl_API.h"
#include "cobra_events.h"
#include "game_entity.h"
#include "imgui.h"
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_impl_sdl2.h>
#include <memory>

#undef main SDL_main

SDL_Window* menu_window = nullptr;
int main(int argc, char* args[])
{
	std::unique_ptr<Sdl_API> game = std::make_unique<Sdl_API>();
	srand(time(NULL));

	if (game->check_integrity())
	{
		// init SDL process
		game->setup_window("COBRA", NULL, NULL, 800, 600);
		SDL_Surface* window_icon_sfc = IMG_Load("C:\\Users\\guico\\source\\repos\\cpp-fundamentals\\cobra\\assets\\red_apple.png");
		SDL_SetColorKey(window_icon_sfc, SDL_TRUE, SDL_MapRGBA(window_icon_sfc->format, 0xFF, 0, 0xF4, 0xFF));
		SDL_SetWindowIcon(game->get_window(), window_icon_sfc);
		SDL_FreeSurface(window_icon_sfc);

		game->setup_renderer(SDL_RENDERER_ACCELERATED);
		game->set_max_framerate(60);
		//menu_window = SDL_CreateWindow("menu window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 40, 40, SDL_WINDOW_SHOWN);

		Snake_Entity* snake_entity = new Snake_Entity(game->get_window(), game->get_renderer(), 
			new Collider2D(new Cobra_Rect{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 25, 25}), 5);
		Bounds snake_bounds = { 0, 800, 0, 600};
		snake_entity->set_bounds(snake_bounds);
		game->set_active_snake(snake_entity);
		
		const unsigned int cells = (game->get_win_dimensions().x * game->get_win_dimensions().y ) / pow(25, 2);
		Grid* grid = new Grid(game->get_renderer(), cells , 25 ,25, { 0x1e, 0x1e, 0x1e, SDL_ALPHA_OPAQUE });
		game->add_grid(grid);

		Texture_Entity* red_apple = new Texture_Entity(game->get_window(), game->get_renderer());
		red_apple->add_texture_component("C:\\Users\\guico\\source\\repos\\cpp-fundamentals\\cobra\\assets\\red_apple.png", { 0xFF, 0, 0xF4, 0xFF });
		red_apple->get_texture_component()->set_src_fraction_rect(NULL);
		red_apple->get_texture_component()->set_render_target_rect(new Cobra_Rect(400, 100, 44, 44));
		red_apple->add_collider2D(red_apple->get_texture_component()->get_render_target_rect());
		snake_entity->add_food(red_apple);

		const std::vector<const Game_Entity*> entities = { red_apple, snake_entity };
		game->add_entities(entities);

		// init imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplSDL2_InitForSDLRenderer(game->get_window(), game->get_renderer());
		ImGui_ImplSDLRenderer2_Init(game->get_renderer());

		while (game->get_metadata()->get_game_state() == Game_State::RUNNING ||
			game->get_metadata()->get_game_state() == Game_State::PAUSED)
		{
			game->handle_events();
			game->update();
			game->render();
		}
	}

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_DestroyWindow(menu_window);
	return 0;
}
