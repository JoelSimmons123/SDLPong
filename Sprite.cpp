#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* _renderer, std::string _file, int _x, int _y, int _w, int _h) //constuctor for the class, when new sprite created setup all the variables etc
{
	SDL_Surface* bmpFile = SDL_LoadBMP(_file.c_str());        //loads the bmp into the sprite from _file
	m_image = SDL_CreateTextureFromSurface(_renderer, bmpFile); //
	SDL_FreeSurface(bmpFile); //memory management

	m_position.x = _x; //initial position oc x/y & w/h of sprite, based on incoming parameters (_x, _y, _w & _h)
	m_position.y = _y;
	m_position.w = _w;
	m_position.h = _h;

	m_renderer = _renderer;
}

Sprite::~Sprite() //destructor function
{
	if (m_image)
	{
		SDL_DestroyTexture(m_image); //destroy the image on destruction of the sprite
	}
}

void Sprite::Draw()
{
	if (m_image)
	{
		SDL_RenderCopy(m_renderer, m_image, NULL, &m_position); //draw the sprite
	}
}