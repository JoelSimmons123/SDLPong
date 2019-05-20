#pragma once
#include "Sprite.h"

class Button : public Sprite //Inheritance
{
public:
	Button(SDL_Renderer* _renderer, std::string _file, int _w, int _h);

	bool Update(SDL_Event _e);

};
