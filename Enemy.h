#pragma once

#include "Sprite.h"


class Enemy : public Sprite //Inheritance
{
public:

	Enemy(SDL_Renderer* _renderer, std::string _file, int _w, int _h, int _speed);

	void Update(int _ballY); //ball passed in as enemy will move towards the ball at all times

private:

	int m_speed; //y speed
};
