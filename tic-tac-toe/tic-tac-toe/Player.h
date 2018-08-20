#pragma once

class AIComponent;
class GameBoard;

class Player
{
public:
	Player(int playerNumber);
	~Player();

	bool PlaceSymbol(int row, int column);
	
	bool GetIsMyTurn() const;
	void SetIsMyTurn(bool isMyTurn);
	void SetGameBoard(GameBoard * gameBoard);

	// AI components
	void InitializeAI();
	AIComponent * GetAI();

private:

	bool isMyTurn;
	AIComponent * ai = nullptr;
	GameBoard * gameBoard = nullptr;
	int symbol;


};

