#include "ball.h"
#include "Enemy.h"
#include "Score.h"
#include <Windows.h>
#include "Audio.h"

Ball::Ball(SDL_Renderer* _renderer, std::string _file, int _w, int _h, float _speed) :
	Sprite(_renderer, _file, 300, 100, _w, _h)
{
	m_xSpeed = _speed;  //speed balltravels in x
	m_ySpeed = m_xSpeed / 2; //speed that the ball travels in y

	m_onPlayerPaddle = true;  //ball starts on the player paddle so they can kick off
	m_onEnemyPaddle = false;
}

void Ball::Update(Player* _paddle, Enemy* _enemy, Score* _playerScore, Score* _enemyScore, SDL_Event _e, Audio* _hitSound, Audio* _clapSound, Audio* _booSound)
{
	const Uint8* key = SDL_GetKeyboardState(NULL); //used to determine keyboard input


	//The following ints are all used to decide which direction the ball gets hit in after it hits the paddles///////

	int paddleMidY = _paddle->GetY() + (_paddle->GetH() / 2); //midpoint
	int paddleUpperMidY = paddleMidY - ((paddleMidY - _paddle->GetY()) / 2); //quarter of the way down from top
	int paddleLowerMidY = paddleMidY + ((paddleMidY - _paddle->GetY()) / 2); //3 quarters of the the way down from the top

	int enemyMidY = _enemy->GetY() + (_enemy->GetH() / 2); //mid point
	int enemyUpperMidY = enemyMidY - ((enemyMidY - _enemy->GetY()) / 2); //quarter of the way down from the top
	int enemyLowerMidY = enemyMidY + ((enemyMidY - _enemy->GetY()) / 2); //quarter of the way down from the top

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int ballMidY = this->GetY() + (this->GetH() / 2); //y value for the middle of the ball

	if (!m_onPlayerPaddle) //if ball is not on the player paddle for kick off
	{
		m_playerCollision = CollisionDetection(_paddle); //detects for collision with user paddle
	}

	if (!m_onEnemyPaddle) //if ball is not on enemy paddle for kick off
	{
		m_enemyCollision = CollisionDetection(_enemy); //detects for collision with enemy paddle
	}
	

	if (m_playerCollision) //if ball collides with player paddle
	{
		_hitSound->Play(); //ball hit sound is played on collision
		m_ySpeed = BallHitDirection(ballMidY, m_ySpeed, paddleMidY, paddleUpperMidY, paddleLowerMidY); //yspeed is determined by where on the paddle it hit
		m_xSpeed = 10; //Make sure ball bounces back towards enemy regardless of hit location
	}
	else if (m_enemyCollision)  //if ball collides with enemy paddle
	{
		_hitSound->Play(); //hit sound is played
		m_ySpeed = BallHitDirection(ballMidY, m_ySpeed, enemyMidY, enemyUpperMidY, enemyLowerMidY); //yseed is determined by where on the paddle it hit
		m_xSpeed = -10; //makes sure the ball bounces towards the player regardless of hit location
	}

	
	if (!m_onPlayerPaddle && !m_onEnemyPaddle)
	{
		m_position.x += m_xSpeed;   //if not on either paddle, keep moving
		m_position.y += m_ySpeed;
	}
	
	else if (m_onPlayerPaddle) // if the ball is on player paddle for kick off
	{
		m_position.x = _paddle->GetX() + 31; //position ball slightly away from paddle so not colliding
		m_position.y = _paddle->GetY() + 85;

		if (key[SDL_SCANCODE_SPACE] || _e.type == SDL_MOUSEBUTTONDOWN) //if mouse clicked or space pressed
		{
			_hitSound->Play(); //hit sound is played 
			m_onPlayerPaddle = false; //made false and speed set back to 10
			m_xSpeed = 10; //made sure the ball is heading towards the enemy
		}
	}

	else if (m_onEnemyPaddle) //if the ball is on enemy paddle for kick off
	{
		m_position.x = _enemy->GetX() - 29; //position ball slightly away from paddle so not colliding
		m_position.y = _enemy->GetY() + 85;
		
		m_onEnemyPaddle = false; //made false and speed set back to -10
		m_xSpeed = -10; //makes sure the ball heads towards the player		
	}

	if (m_position.y < 0 || m_position.y > 570) //bounces ball off the top and bottom of the screen
	{
		m_ySpeed *= -1; //y speed is reversed
	}

	if (m_position.x < 0) //Goal scored against player
	{
		_booSound->Play(); //boo sound is played when the enemy scores

		m_onPlayerPaddle = true; //used to stop ball movement while player takes kick off
		_enemyScore->SetScore(_enemyScore->GetScore() + 1); //increments score
	}

	else if (m_position.x > 994) //Goal scored against enemy
	{
		_clapSound->Play(); //applause sound is played when the player scores

		m_onEnemyPaddle = true; //moves ball to enemy paddle for enemy kick off
		_playerScore->SetScore(_playerScore->GetScore() + 1); //increments score
	}
}

bool Ball::CollisionDetection(Player* _paddle)
{
	if (_paddle->GetX() > this->GetX() + this->GetW()) //if the paddle left x is more than the right side of the ball
	{
		return false;  //No collision
	}

	if (_paddle->GetX() + _paddle->GetW() < this->GetX()) //if the paddle right x is less than the left side of the ball
	{
		return false;  //No collision
	}

	if (_paddle->GetY() > this->GetY() + this->GetH()) //if the paddle top y is more than the ball bottom y
	{
		return false;  //No collision
	}

	if (_paddle->GetY() + _paddle->GetH() < this->GetY()) //if the paddle bottom y is less than the ball top y
	{
		return false;  //No collision
	}

	//if none of the above are triggered, then there is a collision
	return true;
}


bool Ball::CollisionDetection(Enemy* _enemy)
{
	if (_enemy->GetX() > this->GetX() + this->GetW()) //if the enemy paddle left x is more than the right side of the ball
	{
		return false;  //No collision
	}

	if (_enemy->GetX() + _enemy->GetW() < this->GetX()) //if the enemy paddle right x is less than the left side of the ball
	{
		return false;  //No collision
	}

	if (_enemy->GetY() > this->GetY() + this->GetH())  //if the enemy paddle top y is more than the ball bottom y
	{
		return false;  //No collision
	}

	if (_enemy->GetY() + _enemy->GetH() < this->GetY()) //if the enemy paddle bottom y is less than the ball top y
	{
		return false;  //No collision
	}

	return true;
}

float Ball::BallHitDirection(int _ballMidY, float _ySpeed, int _paddleMidY, int _paddleUpperMidY, int _paddleLowerMidY)
{
	if (_ballMidY >= _paddleMidY) //ball lower than mid paddle
	{
		if (_ballMidY > _paddleLowerMidY) //ball hits bottom quarter of paddle
		{
			_ySpeed = 10; //then make it bounce downwards	
		}

		else //Ball hits between mid point and bottom quarter
		{
			_ySpeed = 5; //make it bounce downwards at half the y speed as normal
		}
		
	}

	else if (_ballMidY < _paddleMidY) //if ball hits upper paddle - send ball upwards
	{
		if (_ballMidY < _paddleUpperMidY) //hits top quarter of paddle
		{
			_ySpeed = -10; //make it bounce upwards
		}
		
		else //ball hits between mid point and top quarter
		{
			_ySpeed = -5; //make it bounce upwards at half the y speed as normal
		}
	}

	return _ySpeed; //y speed is returned
}