#pragma once

constexpr int HEALTH = 1;
constexpr int NOT_HEALTH = 0;

enum Game_State {
	RUNNING = 0,
	PAUSED = 1,
	TERMINATED = 2
} ;

struct Game_Metadata {
private:
	Game_State m_state;
public:
	Game_Metadata();
	void set_game_state(const Game_State&);
	Game_State get_game_state() const;
};
