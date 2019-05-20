#pragma once

#include "Sprite.h"
#include <string>

class Player : public Sprite //Inheritance
{
public:

	Player(SDL_Renderer* renderer, std::string _file, int _w, int _h);

	void Update(SDL_Event _e);
};