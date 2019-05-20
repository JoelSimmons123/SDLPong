#pragma once

#include <SDL.h>
#include <string>

class Sprite
{
public:
	Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h); //constructor
	~Sprite(); //destructor

	virtual void Draw();

	void SetX(int _x) { m_position.x = _x; } //setters for x and y
	void SetY(int _y) { m_position.y = _y; }

	int GetX() { return m_position.x; }  //getters  for x, y, w & h
	int GetY() { return m_position.y; }
	int GetW() { return m_position.w; }
	int GetH() { return m_position.h; }

protected:
	SDL_Renderer* m_renderer; //SDL renderer used for drawing

	SDL_Texture* m_image; //Sprite image

	SDL_Rect m_position; //rectangle used for x/y pos and width/height of the sprite
};