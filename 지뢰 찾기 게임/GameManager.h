#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Common.h"
#include "Student.h"
#include "myplayer.h"
#include "Game.h"
class GameManager
{
private :
	//게임을 플레이할 player1과 player2
	Assistant player1;
	myplayer player2;
	
	//실제 Game보드
	Game game;
	
	//플레이어들의 점수를 저장할 변수
	int player1Score;
	int player2Score;
public :
	GameManager();

	//게임을 플레이할 메소드
	void play();
};
#endif