#include "Player.h"

Player::Player(SDL_Renderer* _renderer, std::string _file, int _w, int _h) :
	Sprite(_renderer, _file, 100, 100, _w, _h)
{	

}

void Player::Update(SDL_Event _e)
{
	bool mouseInput = false; //If false, keyboard is controll

	const Uint8* key = SDL_GetKeyboardState(NULL);

	
	int mouseY = 0, mouseX = 0; //mouse positions
	int midPaddleY = m_position.y + (m_position.h / 2); //y value for the middle of the paddle


	//mouse controls only active when the mouse is moving, so when the mouse is not moving the keyboard can control
	if (_e.type == SDL_MOUSEMOTION)
	{
		mouseX = _e.button.x; //get mouse x and y positions
		mouseY = _e.button.y;
		
		//If i make the paddle move towards mouseY, if the mouseY is not a multiple of 5, the paddle will keep going past it up and down to the closest
		//multiple of 5 above and below, fixedMouseY gets around this by rounding the mouseY up to the nearest 5
		int fixedMouseY = 5 - (mouseY % 5) + mouseY;

		if (midPaddleY < fixedMouseY) //moving towards mouse position rounded to 5
		{
			m_position.y += 5;
		}

		else if (midPaddleY > fixedMouseY) //moving towards mouse position rounded to 5
		{
			m_position.y -= 5;
		}
	}

	
	//keyboard controls
	if (key[SDL_SCANCODE_LEFT])
	{
		m_position.x -= 5;
	}
	
	if (key[SDL_SCANCODE_RIGHT])
	{
		m_position.x += 5;
	}

	if (key[SDL_SCANCODE_UP])
	{
		m_position.y -= 5;
	}

	if (key[SDL_SCANCODE_DOWN])
	{
		m_position.y += 5;
	}

	if (m_position.x < 0) //Adds border to left side of the screen
	{
		m_position.x = 0;
	}

	else if (m_position.x > 50) //Adds border to right side of the screen
	{
		m_position.x = 50;
	}

	else if (m_position.y < 0) //Adds border to the top of the screen
	{
		m_position.y = 0; 
	}

	else if (m_position.y > 400) //Adds border to the bottom of the screen
	{
		m_position.y = 400;
	}	
}

