#pragma once

#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "Score.h"
#include <SDL_mixer.h>
#include "Audio.h"

class Ball : public Sprite //Inheritance
{
public:

	Ball(SDL_Renderer* renderer, std::string _file, int _w, int _h, float _speed);

	void Update(Player* _paddle, Enemy* _enemy, Score* _playerScore, Score* _enemyScore, SDL_Event _e, Audio* _hitSound, Audio* _clapSound, Audio* _booSound);

	int GetPlayerScore() { return m_playerScore; } //used for displaying the scores
	int GetEnemyScore() { return m_enemyScore; } 

	float BallHitDirection(int _ballMidY, float _ySpeed, int _paddleMidY, int _paddleUpperMidY, int _paddleLowerMidY); //determines ball direction after paddle hit depending on area of the paddle hit - player and enemy
	
	bool CollisionDetection(Player* _paddle); //collision detection for the player paddle
	bool CollisionDetection(Enemy* _paddle); //collision detetction for the enemy paddle
	

private:
	
	float m_xSpeed; //distance ball will travel in x every update
	float m_ySpeed; //distance ball will travel in y every update

	bool m_onPlayerPaddle; //used for "kick off" after a goal
	bool m_onEnemyPaddle;
	bool m_playerCollision; //ball collision with player paddle
	bool m_enemyCollision;  //ball collision with enemy paddle

	int m_playerScore; //used to keep track of goals scored for player
	int m_enemyScore; //used to keep track of goals scored for player
};