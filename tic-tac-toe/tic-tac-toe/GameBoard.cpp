#include "GameBoard.h"
#include <iostream>



GameBoard::GameBoard()
{
}


GameBoard::~GameBoard()
{
}

void GameBoard::DrawBoard()
{
	system("cls");

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			// Player 2
			if (board[i][j] == 2)
			{
				std::cout << "| O |";
			}
			// Player 1
			else if (board[i][j] == 1)
			{
				std::cout << "| X |";
			}
			// Empty
			else
			{
				std::cout << "|   |";
			}
		}

		std::cout << std::endl;
	}
}

int GameBoard::GetBoardValue(int row, int column) const
{
	return board [row][column];
}

void GameBoard::SetBoardValue(int row, int column, int value)
{
}
