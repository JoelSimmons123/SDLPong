#pragma once

#include <SDL_ttf.h>

class Score
{

public:

	Score();
	Score(SDL_Renderer* _renderer, int _x, int _y); //positioning
	~Score();

	void Update();
	void SetScore(int _Score) { m_score = _Score; } //setter
	void Draw();
	
	int GetScore() { return m_score; }  //getters for score and win status
	bool GetWinStaus() { return m_wonGame; }
	
private:
	SDL_Texture* m_text; //used for displaying the scores as text
	TTF_Font* m_font;

	SDL_Renderer* m_renderer; 

	int m_score;
	int m_x, m_y; //position for the text
	bool m_wonGame;
};