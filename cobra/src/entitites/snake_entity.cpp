#include "snake_entity.h"
#include "logger.h"
#include <algorithm>
#include <iterator>
#include <sstream>

Snake_Entity::Snake_Entity(SDL_Window* window, SDL_Renderer* renderer, Collider2D* head_rect, const unsigned length)
	: Game_Entity(window, renderer), m_length(length),
	m_direction(Snake_Direction::DOWN), head_rect(head_rect), m_apple(nullptr),
	m_is_game_over(false), m_bounds(Bounds {0, 0, 0, 0}), apples_eaten(0), m_initial_length(length),
	m_initial_x(head_rect->get_dst_rect()->m_position.x), m_initial_y(head_rect->get_dst_rect()->m_position.y)
{
	set_entity_type(Entity_Type::SNAKE);
	score_text = new Dynamic_Text(renderer);
	score_text->update("Score 0", { 255, 255, 255, 255 });
	slider_velocity = new float(1.0f);
	game_over_text = new Dynamic_Text(renderer);
	game_over_text->update("Game Over!", { 255, 255, 255, 255 });
	m_apple_eaten_audio = new Cobra_Audio("C:\\Users\\guico\\source\\repos\\cpp-fundamentals\\cobra\\assets\\eat.wav");
	m_apple_eaten_audio->setup_device();
};

void Snake_Entity::render() const
{
	if (get_snake_moving()) {
		score_text->render({ 650, 550, 130, 32 });
		if (_m_rq.size() > 0) {

			int width = _m_rq[0].w, height = _m_rq[0].h;
			Uint32* buffer = new Uint32[width * height];
			for (auto it = _m_rq.begin(); it != _m_rq.end(); ++it)
			{
				for (int y = 0; y < height; y++) {
					for (int x = 0; x < width; x++) {
						//if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						//	buffer[(y * width) + x] = 0xFFFFFFFF;
						//}
						//else
						//{
							if (it == _m_rq.begin()) buffer[(y * width) + x] = 0xFF0000FF;
							else buffer[(y * width) + x] = 0x00FF00FF;
						//}
					}
				}
				SDL_Texture* texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
				SDL_UpdateTexture(texture, NULL, buffer, sizeof(Uint32) * width);
				SDL_RenderCopy(m_renderer, texture, NULL, &(*it));
				SDL_DestroyTexture(texture);
			}

			delete[] buffer;
		}
	}
	if (m_is_game_over)
		game_over_text->render({ 100, 175, 600, 150 });
}

void Snake_Entity::check_food_collision(SDL_Rect* food)
{
	if (head_rect->is_colliding(food)) {
		//belly_effect();
		m_apple_eaten_audio->play_sound();
		apples_eaten++;
		m_length += 15;
		SDL_Rect* apple_rect = m_apple->get_collider(0)->get_dst_rect()->get_generated_SDL_rect();
		apple_rect->x = (rand() % (int)(800 - apple_rect->w * 1.5)) + 1;
		apple_rect->y = (rand() % (int)(600 - apple_rect->y * 1.5)) + 1;
		std::stringstream ss;
		ss << "Score " << apples_eaten;
		score_text->update(ss.str(), { 255, 255, 255, 255 });
	}
}

void Snake_Entity::update()
{
	collide_itself();
	check_food_collision(m_apple->get_texture_component()->get_render_target_rect()->get_generated_SDL_rect());
	adjust_snake();
	if (is_expanding) {
		int body_counter = 0;
		const int max_animation_frames = 15;
		const float expansion_amount = 1;
		const float max_expansion = 3.0;
		float expansion_step = (animation_progress < max_animation_frames / 2.5) ? expansion_amount : -expansion_amount;
		if (animation_progress < max_animation_frames) {
			for (auto& segment : _m_rq) {
				if (m_direction == Snake_Direction::RIGHT || m_direction == Snake_Direction::LEFT) {
					segment.y += (expansion_step / max_animation_frames) * max_expansion;
				}
				else if (m_direction == Snake_Direction::UP || m_direction == Snake_Direction::DOWN) {
					segment.x += (expansion_step / max_animation_frames) * max_expansion;
				}
			}
			animation_progress++;
		}
		else {
			is_expanding = false;
			animation_progress = 0;  // Reset the progress for the next expansion
		}
	}
	switch (m_direction)
	{
	case UP:
		head_rect->get_dst_rect()->get_generated_SDL_rect()->y -= 7 * (*slider_velocity);
		break;
	case DOWN:
		head_rect->get_dst_rect()->get_generated_SDL_rect()->y += 7 * (*slider_velocity);
		break;
	case LEFT:
		head_rect->get_dst_rect()->get_generated_SDL_rect()->x -= 7 * (*slider_velocity);
		break;
	case RIGHT:
		head_rect->get_dst_rect()->get_generated_SDL_rect()->x += 7 * (*slider_velocity);
		break;
	}

	_m_rq.push_front(*head_rect->get_dst_rect()->get_generated_SDL_rect());
	while (_m_rq.size() > m_length)
	{
		_m_rq.pop_back();
	}
}

void Snake_Entity::restart()
{
	SDL_RenderClear(m_renderer);
	SDL_Rect* _head_rect = head_rect->get_dst_rect()->get_generated_SDL_rect();
	_head_rect->x = m_initial_x;
	_head_rect->y = m_initial_y;
	if (_m_rq.size() > 1) {
		_m_rq.erase(_m_rq.begin(), _m_rq.end());
	}
	m_is_game_over = false;
	m_direction = Snake_Direction::DOWN;
	apples_eaten = 0;
	std::stringstream ss;
	ss << "Score " << apples_eaten;
	score_text->update(ss.str(), { 255, 255, 255, 255 });
}

void Snake_Entity::collide_itself()
{
	if (_m_rq.size() > 0)
	{
		SDL_Rect* _head_rect = head_rect->get_dst_rect()->get_generated_SDL_rect();
		for (auto it = std::next(_m_rq.begin()); it != _m_rq.end(); ++it) {
			if (_head_rect->x == it->x && _head_rect->y == it->y) game_over();
		}
	}
}

void Snake_Entity::adjust_snake()
{
	SDL_Rect* _head_rect = head_rect->get_dst_rect()->get_generated_SDL_rect();
	if (_head_rect->x <= m_bounds.X_MIN) {
		_head_rect->x = m_bounds.X_MAX + 1;
		return;
	}
	if (_head_rect->x >= m_bounds.X_MAX) {
		_head_rect->x = m_bounds.X_MIN + 1;
		return;
	}
	if (_head_rect->y <= m_bounds.Y_MIN) {
		_head_rect->y = m_bounds.Y_MAX + 1;
		return;
	}
	if (_head_rect->y >= m_bounds.Y_MAX) {
		_head_rect->y = m_bounds.X_MIN + 1;
	}
}

void Snake_Entity::belly_effect()
{
	if (_m_rq.size() > 0)
	{
		is_expanding = true;
		animation_progress = 0;
	}
}

void Snake_Entity::game_over()
{
	std::cout << "game over" << std::endl;
	m_length = m_initial_length;
	m_is_game_over = true;
	set_snake_moving(false);
}

Snake_Entity::~Snake_Entity()
{
	delete head_rect;
}

void Snake_Entity::set_length(const unsigned int length) { m_length = length; }
void Snake_Entity::set_direction(const Snake_Direction direction) { m_direction = direction; }
