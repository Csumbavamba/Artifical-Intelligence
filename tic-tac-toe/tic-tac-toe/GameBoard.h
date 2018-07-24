#pragma once
class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	void DrawBoard();

	int GetBoardValue(int row, int column) const;
	void SetBoardValue(int row, int column, int value);

private:

	int board[3][3]{};
};

