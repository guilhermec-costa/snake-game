#pragma once
#include "game_entity.h"
#include "texture_entity.h"
#include <SDL2/SDL_ttf.h>
#include <deque>
#include "components/dynamic_text.h"
#include "components/Audio_Manager.h"

enum Snake_Direction {
	UP = 'U',
	DOWN = 'D',
	LEFT = 'L',
	RIGHT = 'R'
};

typedef struct Bounds {
    int X_MIN;
    int X_MAX;
    int Y_MIN;
    int Y_MAX;

    // Construtor
    Bounds(int xmin, int xmax, int ymin, int ymax) 
        : X_MIN(xmin), X_MAX(xmax), Y_MIN(ymin), Y_MAX(ymax) {}
} Bounds;

class Snake_Entity : public Game_Entity
{
public:
	Snake_Entity(SDL_Window* window, SDL_Renderer* renderer, Collider2D* head_rect, const unsigned length);
	~Snake_Entity();
	void render() const override;
	bool m_is_game_over;
	void update();
	void adjust_snake();
	void restart();
	void check_food_collision(SDL_Rect* apple);
	void collide_itself();
	void belly_effect();
	inline void add_food(Texture_Entity* rect) {
		m_apple = rect;
	};
	void game_over();
	inline void set_snake_moving(bool state) { m_snake_moving = state; }
	inline bool get_snake_moving() const { return m_snake_moving; }
	void set_length(const unsigned int length);
	void set_direction(const Snake_Direction direction);
	inline void set_bounds(const Bounds bounds) { 
		m_bounds = bounds; 
	};
	inline Snake_Direction get_direction() const
	{
		return m_direction;
	};
	inline int get_length() const
	{
		return m_length;
	}
	inline float* get_slider_velocity() const { return slider_velocity; }
private:
	unsigned int m_length, m_initial_length, m_initial_x, m_initial_y;
	Snake_Direction m_direction;
	Bounds m_bounds;
	Collider2D* head_rect;
	Texture_Entity* m_apple;
	unsigned int apples_eaten;
	bool m_snake_moving, is_expanding;
	int animation_progress;
	std::deque<SDL_Rect> _m_rq;
	Dynamic_Text* score_text;
	Dynamic_Text* game_over_text;
	Cobra_Audio* m_apple_eaten_audio;
	int m_last_time_updated;
	float* slider_velocity;
};
