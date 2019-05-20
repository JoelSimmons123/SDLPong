#pragma once

#include "Sprite.h"
#include <string>

class ScrollBkg 
{
public:

	//Constructor and destructor
	ScrollBkg(SDL_Renderer* _renderer, std::string _imageFile, float _speed, int _w, int _h);
	~ScrollBkg();

	void Update(); //Does scrolling, call every frame
	void Draw(); //Does drawing, call every frame

private:

	Sprite* m_image; // sprite that this background uses
	float m_x;	   // current x position (Changes as scrolls)
	float m_speed;   // scroll speed
	int m_w;		   // width of image used
};
