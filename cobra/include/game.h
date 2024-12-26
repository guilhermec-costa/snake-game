#pragma once
#include "Game_Metadata.h"

class IGame {
public:
	~IGame() {
		delete m_metadata;
	};
protected:
	Game_Metadata* m_metadata;
	int m_max_framerate;
	double m_ms_between_frames;
	unsigned short m_integrity;
	IGame() : m_metadata(new Game_Metadata()), m_integrity(HEALTH), m_max_framerate(60), m_ms_between_frames(16.6){};
public:
	virtual void terminate() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handle_events() = 0;
	Game_Metadata* get_metadata()
	{
		return this->m_metadata;
	}
	void set_max_framerate(int framerate)
	{
		m_max_framerate = framerate;
		m_ms_between_frames = 1000 / m_max_framerate;
	}
};

