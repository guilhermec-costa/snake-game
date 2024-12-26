#include "Game_Metadata.h"
#include <iostream>

Game_Metadata::Game_Metadata() : m_state(Game_State::RUNNING) {}
Game_State Game_Metadata::get_game_state() const { return m_state; }
void Game_Metadata::set_game_state(const Game_State& state) { this->m_state = state; }