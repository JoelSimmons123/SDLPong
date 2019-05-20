#include "ScrollBkg.h"
#include <string>

ScrollBkg::ScrollBkg(SDL_Renderer* _renderer, std::string _imagefile, float _speed, int _w, int _h)
{
	m_w = _w;  //store incoming parameters that are needed later
	m_speed = _speed;
	m_x = 0;	 //start x at 0

	m_image = new Sprite(_renderer, _imagefile, 0, 0, _w, _h);
}

ScrollBkg::~ScrollBkg()
{
	delete m_image; //free up image used by sprite
}

void ScrollBkg::Update()
{
	m_x -= m_speed; //scroll along

	if (m_x < -m_w)
	{
		m_x += m_w;
	}
}

void ScrollBkg::Draw()
{
	//draw two copies of image, one at 'x', one at 'x + w'
	m_image->SetX(m_x);
	m_image->Draw();

	m_image->SetX(m_x + m_w);
	m_image->Draw();
}