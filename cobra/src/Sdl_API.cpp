#include "Sdl_API.h"
#include "Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "asset_manager.h"
#include "components/texture_component.h"
#include "logger.h"
#include "components/dynamic_text.h"
#include "imgui.h"
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_impl_sdl2.h>

Sdl_API::Sdl_API()
	: m_window(nullptr), m_event_src(new SDL_Event()), m_snake(nullptr)
{
	init_subsystems();
	get_metadata()->set_game_state(Game_State::RUNNING);
	init_event_handlers();
	setup_renderer(SDL_RENDERER_ACCELERATED);
	m_integrity = HEALTH;
	std::string msg = "SDL API started";
	Logger::s_get_instance().log(msg);
	Asset_Manager::get_instance().load_asset("C:\\Users\\guico\\source\\repos\\cpp-fundamentals\\cobra\\assets\\foods.png");
}

void Sdl_API::init_event_handlers()
{
	m_events.quit_event = _quit_event;
}

void Sdl_API::init_subsystems()
{
	if (SDL_Init(COBRA_SUBSYSTEMS) != 0)
	{
		m_integrity = NOT_HEALTH;
		std::string msg = "Failed to initalize SDL Video Subsystems";
		Logger::s_get_instance().log_err(msg);
	}

	if (TTF_Init() != 0)
	{
		m_integrity = NOT_HEALTH;
		std::string msg = "Failed to initialize SDL Font system";
		Logger::s_get_instance().log_err(msg);
	}
}

void Sdl_API::setup_window(const char* title, int x, int y, int w, int h)
{
	if (x == NULL) x = SDL_WINDOWPOS_CENTERED;
	if (y == NULL) y = SDL_WINDOWPOS_CENTERED;
	m_window_dimensions = { w, h };
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (m_window == nullptr) {
		m_integrity = NOT_HEALTH;
		std::string message;
		message += "Failed to created SDL window. Message -> ";
		message.append(SDL_GetError());
		Logger::s_get_instance().log_err(message);
	}
}

void Sdl_API::setup_renderer(SDL_RendererFlags flags)
{
	if (flags == NULL) flags = SDL_RENDERER_PRESENTVSYNC;
	if (m_window == nullptr) return;
	m_renderer = SDL_CreateRenderer(m_window, -1, flags);
	if (m_renderer == nullptr) {
		m_integrity = NOT_HEALTH;
		std::string message;
		message += "Failed to created SDL Renderer. Message -> ";
		message.append(SDL_GetError());
		Logger::s_get_instance().log_err(message);
	}
}

void Sdl_API::add_entities(const std::vector<const Game_Entity*>& entities)
{
	for (auto& entity : entities)
	{
		if (entity == nullptr)
		{
			std::string message;
			message = "Entity was not initialized";
			Logger::s_get_instance().log_err(message);
		}
		m_entities.push_back(entity);
	}
}

void Sdl_API::render()
{

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("test imgui");
	
	ImGui::Text("Hello world!");

	ImGui::SliderFloat("velocity", m_snake->get_slider_velocity(), 0.0f, 2.0f);

	ImGui::End();
	ImGui::Render();


	int frame_start_time = SDL_GetTicks();
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	m_bg_grid->render(m_renderer);
	for (const auto& e : m_entities)
	{
		if (e->is_visible())
		{
			e->render();
		}
	}
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), get_renderer());
	SDL_RenderPresent(m_renderer);

	int _elapsed = SDL_GetTicks() - frame_start_time;
	if (_elapsed < m_ms_between_frames) SDL_Delay(m_ms_between_frames - _elapsed);
}


void Sdl_API::update()
{
	if (!m_snake->m_is_game_over && m_snake->get_snake_moving() && get_metadata()->get_game_state() == Game_State::RUNNING)
		m_snake->update();
}

void Sdl_API::handle_events()
{
	while (SDL_PollEvent(m_event_src))
	{
		ImGui_ImplSDL2_ProcessEvent(m_event_src);
		switch (m_event_src->type)
		{
		case SDL_QUIT:
			terminate();
			break;
		case SDL_KEYDOWN: {
			switch (m_event_src->key.keysym.sym)
			{
			case SDLK_UP:
				if (!(m_snake->get_direction() == Snake_Direction::DOWN))
					m_snake->set_direction(UP);
				break;
			case SDLK_DOWN:
				if (!(m_snake->get_direction() == Snake_Direction::UP))
					m_snake->set_direction(DOWN);
				break;
			case SDLK_LEFT:
				if (!(m_snake->get_direction() == Snake_Direction::RIGHT))
					m_snake->set_direction(LEFT);
				break;
			case SDLK_RIGHT:
				if (!(m_snake->get_direction() == Snake_Direction::LEFT))
					m_snake->set_direction(RIGHT);
				break;
			case SDLK_KP_ENTER:
				m_snake->set_snake_moving(true);
				if (m_snake->m_is_game_over) {
					m_snake->restart();
				}
				break;
			case SDLK_ESCAPE:
				Game_Metadata* metadata = get_metadata();
				if (metadata->get_game_state() == Game_State::RUNNING)
				{
					metadata->set_game_state(Game_State::PAUSED);
				}
				else
				{
					metadata->set_game_state(Game_State::RUNNING);
				}
				break;
			}
		}
		}
	}
}

SDL_Renderer* Sdl_API::get_renderer() const { return m_renderer; }
SDL_Window* Sdl_API::get_window() const { return m_window; }
void Sdl_API::terminate() {
	TTF_Quit();
	get_metadata()->set_game_state(Game_State::TERMINATED);
}
bool Sdl_API::check_integrity() const { return m_integrity; }
Vector2 Sdl_API::get_win_dimensions() const { return m_window_dimensions; }


