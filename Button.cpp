#include "Button.h"
#include "Sprite.h"
#include <iostream>

Button::Button(SDL_Renderer* _renderer, std::string _file, int _w, int _h) :
	Sprite(_renderer, _file, 300, 200, _w, _h)
{

}

bool Button::Update(SDL_Event _e)
{
	int mouseX, mouseY; //used to get mouse position

	if (_e.type == SDL_MOUSEBUTTONDOWN) //if mouse clicked
	{
		mouseX = _e.button.x; //get mouse x and y positions
		mouseY = _e.button.y;


		if (mouseX >= this->GetX() && mouseX <= (this->GetX() + this->GetW()) //if clicked left and right of button on x
		&& mouseY >= this->GetY() && mouseY <= (this->GetY() + this->GetH())) //if between top and bottom of button on y
		{
			return true; //play is returned as true to start, or exit is returned as true, so the game can clean up then quit
		}
	}	

	return false; //if not clicked in the button then do not quit
}