#include "Audio.h"

Audio::~Audio()
{
	SDL_CloseAudioDevice(m_deviceID); //when object destroyed, audio device is closed and the WAV sound file is freed, memory management
	SDL_FreeWAV(m_wavBuffer);
}

void Audio::Load(const char* _filename)
{
	SDL_LoadWAV(_filename, &m_wavSpec, &m_wavBuffer, &m_wavLength);   //loads the _filename sound file into the audio device
	m_deviceID = SDL_OpenAudioDevice(NULL, 0, &m_wavSpec, NULL, 0);
}

void Audio::Play()
{
	SDL_QueueAudio(m_deviceID, m_wavBuffer, m_wavLength); //the audio is put into the queue
	SDL_PauseAudioDevice(m_deviceID, 0);              //then the queue is UNpaused (0 as second parameter)
}

void Audio::Stop()
{
	SDL_PauseAudioDevice(m_deviceID, 1); //audio is paused, if needed to be 
}
