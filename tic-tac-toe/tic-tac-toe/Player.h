#pragma once

class AIComponent;

class Player
{
public:
	Player();
	~Player();

	void PlaceSymbol(int row, int column);
	
	bool IsMyTurn() const;
	void SetIsMyTurn(bool isMyTurn);

	// AI components
	void InitializeAI();
	AIComponent * GetAI();

private:

	bool isMyTurn;
	AIComponent * ai = nullptr;

};

