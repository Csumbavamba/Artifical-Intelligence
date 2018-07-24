// The game has to do this:
// Have a 3*3 map
// Have 2 players (player 2 can be controlled by an AI)
// Have an AI that decides on what should be the next step

// Win game if you have 3 consequitive symbols
#include "Player.h"
#include "GameBoard.h"

#include <iostream>


int main()
{
	GameBoard gameBoard;
	Player player1, player2;

	gameBoard.DrawBoard();

	int wait;
	std::cin >> wait;

	return 0;
}