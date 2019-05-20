#include "Enemy.h"
#include "ball.h"


Enemy::Enemy(SDL_Renderer* _renderer, std::string _file, int _w, int _h, int _speed) :
	Sprite(_renderer, _file, 964, 100, _w, _h)
{
	m_speed = _speed;
}


void Enemy::Update(int _ballY)
{
	if (_ballY > m_position.y) //follow the ball down if it is lower than the enemy
	{
		m_position.y += m_speed;
	}

	else if (_ballY < m_position.y) //follow the ball up if it is higher than the enemy
	{
		m_position.y -= m_speed;
	}

	if (m_position.y < 0) //Adds border to the top of the screen
	{
		m_position.y = 0;
	}

	else if (m_position.y > 400) //Adds border to the bottom of the screen
	{
		m_position.y = 400;
	}
}

