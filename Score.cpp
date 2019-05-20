#include "Score.h"
#include <string>

Score::Score()
{

}

Score::Score(SDL_Renderer* _renderer, int _x, int _y)
{
	this->m_score = 0; //start score at 0
	this->m_font = TTF_OpenFont("font.ttf", 50); //give the text a font and size
	this->m_x = _x;  //x and y for text to be
	this->m_y = _y;

	this->m_wonGame = false; 

	m_renderer = _renderer;
}

void Score::Draw()
{

	std::string scoreStr = std::to_string(this->m_score); //converts to string, so it can be used in the surface as a char*

	//TTF used to draw score onto the screen
	TTF_Font *font = TTF_OpenFont("font.ttf", 50); //downloaded font is selected, size 50
	SDL_Color colour = { 0, 0, 0, 255 }; //colour set to black
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), colour); //surface made using the score converted into a char* for rendertextsolid to work
	SDL_Texture *text = SDL_CreateTextureFromSurface(m_renderer, textSurface); //texture made for the text from the textsurface
	SDL_Rect textRect; //rect used for positioning text

	textRect.x = this->m_x; //positioning from object values of x and y
	textRect.y = this->m_y;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h); //queries the text texture just created with the rect

	SDL_FreeSurface(textSurface); //frees the memory from textSurface

	SDL_RenderCopy(m_renderer, text, NULL, &textRect);  //adds the text to the renderer along with everything else
}

void Score::Update()
{
	if (this->m_score >= 5) //when score reaches this value, the game ends
	{
		this->m_wonGame = true; //the wonGame variable on the playerScore or enemyScore is set to true, depending on who reached the winning number of points
	}
}