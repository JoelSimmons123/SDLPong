#pragma once
#include <SDL.h>

class Audio 
{
public:

	~Audio(); //deconstructor
	void Load(const char* _filename); //loads the sound file into the object
	void Play(); //plays the sound
	void Stop(); //stops the sound

private:

	SDL_AudioSpec m_wavSpec;   //used for loading the sounds into the audio device
	Uint32 m_wavLength;
	Uint8* m_wavBuffer;
	SDL_AudioDeviceID m_deviceID; //audio device used to play the sound, set to default later on
};