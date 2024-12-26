#include "components/Audio_Manager.h"
#include "logger.h"
#include <string>

Cobra_Audio::Cobra_Audio(const char* audiopath)
{
	if (SDL_LoadWAV(audiopath, &m_spec, &m_wave_start, &m_wave_length) == nullptr) {
		std::string err;
		err.append("Failed to load audio from \"");
		err.append(audiopath);
		err.append("\"");
		Logger::s_get_instance().log_err(err);
	}
}

Cobra_Audio::~Cobra_Audio()
{
	SDL_FreeWAV(m_wave_start);
	SDL_CloseAudioDevice(m_device);
}

void Cobra_Audio::play_sound() 
{
	std::cout << "playing audio" << std::endl;
	SDL_QueueAudio(m_device, m_wave_start, m_wave_length);
	SDL_PauseAudioDevice(m_device, 0);
}

void Cobra_Audio::stop_sound()
{
	SDL_PauseAudioDevice(m_device, 1);
}

void Cobra_Audio::setup_device()
{
	m_device = SDL_OpenAudioDevice(nullptr, 0, &m_spec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (m_device == 0)
	{
		std::string err = "Failed to load audio device from computer";
		Logger::s_get_instance().log_err(err);
	}
}
