#pragma once
#include <SDL2/SDL_audio.h>

class IAudio {
public:
	virtual void play_sound() = 0;
	virtual void stop_sound() = 0;
};


class Cobra_Audio : public IAudio {
public:
	Cobra_Audio(const char* audiopath);
	~Cobra_Audio();
	void play_sound() override;
	void stop_sound() override;
	void setup_device();
private:
	SDL_AudioDeviceID m_device;
	SDL_AudioSpec m_spec;
	Uint8* m_wave_start;
	Uint32 m_wave_length;
};
