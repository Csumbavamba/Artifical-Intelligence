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

	std::cout << "     0    1    2 " << std::endl;
	std::cout << "   --------------" << std::endl;

	for (int i = 0; i < 3; ++i)
	{
		std::cout << i << "  ";
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

	std::cout << std::endl;
}

int GameBoard::GetBoardValue(int row, int column) const
{
	return board [row][column];
}

void GameBoard::SetBoardValue(int row, int column, int value)
{
	board[row][column] = value;
}

void GameBoard::ClearBoard()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			board[i][j] = 0;
		}
	}
}
