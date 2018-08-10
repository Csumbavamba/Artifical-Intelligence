#pragma once
#include <vector>

class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	void DrawBoard();

	int GetBoardValue(int row, int column) const;
	void SetBoardValue(int row, int column, int value);
	void ClearBoard();

private:

	int board[3][3]{}; // 0 for empty, 1 for player1 2 for player2


};

