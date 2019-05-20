#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Sprite.h"
#include "Player.h"
#include "ScrollBkg.h"
#include "ball.h"
#include "Enemy.h"
#include "Score.h"
#include "Button.h"
#include "Audio.h"

void GameLoop(SDL_Window* window, SDL_Renderer* renderer); //
void DisplayText(SDL_Renderer* _renderer, std::string _textStr, int _x, int _y, int _size); //displays text onto the window that is passed in as _textStr

int main(int, char**)
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("PAUSE");
		return 0;
	}

	// try to create the window, log error and pause if fail
	window = SDL_CreateWindow("Pong", 100, 100, 1024, 600, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 0;
	}

	// try to create the renderer, log error and pause if fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() == -1)
	{
		std::cout << "TTF init error: " << TTF_GetError() << std::endl;
		return false;
	}

	// this function call goes into the actual game loop
	GameLoop(window, renderer);

	// clean up, free any memeory we have use
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

void GameLoop(SDL_Window* window, SDL_Renderer* renderer)
{
	// Load audio files

	bool start = false; //used for start menu
	bool quit = false; //used for game loop
	bool playerWon = false, enemyWon = false; //used when game is won or lost

	SDL_Event e; //event used for mouse clicks/movement/quits

	Player* paddle = new Player(renderer, "paddle.bmp", 30, 200);		    //user paddle
	ScrollBkg* bkg = new ScrollBkg(renderer, "bkg.bmp", 5, 1024, 600);	    //background
	Ball* ball = new Ball(renderer, "ball.bmp", 30, 30, -10);			    //ball for the game
	Enemy* enemy = new Enemy(renderer, "enemy.bmp", 30, 200, 4);			//opponent paddle
	Score* playerScore = new Score(renderer, 10, 0);						//player score count
	Score* enemyScore = new Score(renderer, 970, 0);                        //enemy score count
	Button* exitButton = new Button(renderer, "exitButton.bmp", 400, 200);  //quit button at the end
	Button* playButton = new Button(renderer, "playButton.bmp", 400, 200);  //play button at the start

	//Background music
	Audio* backMusic = new Audio();
	backMusic->Load("backgroundMusic.wav");

	//Setting up sound effects
	Audio* hitSound = new Audio();   //ball hit sound
	hitSound->Load("hit.wav");       //loads the sound file
	Audio* clapSound = new Audio();  //applause for goal
	clapSound->Load("applause.wav"); //loads the sound file
	Audio* booSound = new Audio();   //boo for enemy goal
	booSound->Load("boo.wav");       //loads the sound file
	Audio* winMusic = new Audio();   //victory music for winning the game
	winMusic->Load("victory.wav");   //loads the sound file
	Audio* lossMusic = new Audio();  //defeat music for losing the game
	lossMusic->Load("defeat.wav");   //loads the sound file

	std::string outcome = ""; //used for you win/you lose text

	//instructions split into 3 strings so they can all fit on the screen easily
	std::string instructionsText = "Instructions: Use the arrow keys to move the paddle, or move the mouse to make the ";
	std::string instructionsText2 = "paddle follow it. \nWhen the ball is on your paddle, press the spacebar or left click to shoot it.";
	std::string instructionsText3 = "To score a point, get the ball past your opponent, first to 5 goals wins!    ";

	backMusic->Play();//play the background music

	while (!start && !quit) //start menu loop
	{
		while (SDL_PollEvent(&e)) //allow closing sdl window to quit the game
		{
			if (e.type == SDL_QUIT) { quit = true; }
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		bkg->Update();  //background is running on the start screen
		start = playButton->Update(e);  //start variable changed to true when button is clicked

		bkg->Draw(); //background drawn
		playButton->Draw(); //button drawn

		DisplayText(renderer, instructionsText, 0, 450, 25);  //all 3 of the strings are displayed on the screen for the user to read
		DisplayText(renderer, instructionsText2, 0, 485, 25);
		DisplayText(renderer, instructionsText3, 0, 520, 25);

		SDL_RenderPresent(renderer);
	}

	while (!quit) //main game loop
	{
		while ((!playerWon && !enemyWon) && !quit)
		{
			while (SDL_PollEvent(&e)) //allow closing sdl window to quit the game
			{
				if (e.type == SDL_QUIT) { quit = true; }
			}

			//first clear the renderer
			SDL_RenderClear(renderer);

			bkg->Update(); 
			ball->Update(paddle, enemy, playerScore, enemyScore, e, hitSound, clapSound, booSound); //ball update is passed both paddles for collision detection, the scores for incrementation, the sdl event for clicking of the mouse, and sounds to play on various occasions
			paddle->Update(e);  //paddle passed the sdl event for mouse movement so it can be mouse controlled
			enemy->Update(ball->GetY());  //enemy is passed the ball position in y so it can follow it
			playerScore->Update();       //scores are updated
			enemyScore->Update();

			bkg->Draw();  //everything is drawn
			ball->Draw();
			paddle->Draw();
			enemy->Draw();
			playerScore->Draw();
			enemyScore->Draw();


			playerWon = playerScore->GetWinStaus();  //win status for both players is obtained from each object so the game knows when to stop the game
			enemyWon = enemyScore->GetWinStaus();

			//update the screen
			SDL_RenderPresent(renderer);
		}

		//Stops the background music because loss/victory music takes over
		backMusic->Stop();

		//game won by player
		if (playerWon)
		{
			winMusic->Play(); //victory music plays
			outcome = "You win!";  //text to be displayed will be "You win!"
		}

		//game won by enemy
		else
		{
			lossMusic->Play();  //defeat music plays
			outcome = "You lose!";   //text to be displayed will be "You lose!"
		}

		bool exit = false; //different bool to quit, just for the button

		while (!quit && !exit) //loops while the user hasnt clicked the x on the window, and the button to exit hasnt been clicked
		{
			while (SDL_PollEvent(&e)) //allow closing sdl window to quit the game
			{
				if (e.type == SDL_QUIT) { quit = true; }
			}

			SDL_RenderClear(renderer);

			bkg->Update(); //scrolling background still running
			exit = exitButton->Update(e);  //exit is set to true if the quit button is pressed, so the loop will exit

			bkg->Draw();          //button and background are drawn
			exitButton->Draw();   

			DisplayText(renderer, outcome, 350, 100, 75);  //text is displayed with the outcome text set by the win/loss condition earlier (outcome)

			SDL_RenderPresent(renderer);
		}
		quit = true;
	}

	//memory management

	Mix_CloseAudio();

	delete bkg;
	delete paddle;
	delete ball;
	delete enemy;
	delete exitButton;
	delete playButton;
	delete hitSound;
	delete clapSound;
	delete booSound;
	delete winMusic;
	delete lossMusic;
	delete backMusic;
}


void DisplayText(SDL_Renderer* _renderer, std::string _textStr, int _x, int _y, int _size)
{
	//TTF used to draw score onto the screen
	TTF_Font* font = TTF_OpenFont("font.ttf", _size); //downloaded font is selected, size 75
	SDL_Color colour = { 0, 0, 0, 255 }; //colour set to black
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, _textStr.c_str(), colour); //surface made using the outcome string converted into a char* for rendertextsolid to work
	SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface); //texture made for the text from the textsurface
	SDL_Rect textRect; //rect used for positioning text

	textRect.x = _x; //positioning from objects values of x and y
	textRect.y = _y;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h); //queries the text texture just created with the rect

	SDL_FreeSurface(textSurface); //frees the memory from  textSurface

	SDL_RenderCopy(_renderer, text, NULL, &textRect);  //adds the text to the renderer along with everything else
}
