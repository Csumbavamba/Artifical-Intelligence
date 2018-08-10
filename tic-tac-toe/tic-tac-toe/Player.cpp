#include "Player.h"
#include "GameBoard.h"
#include "AIComponent.h"



Player::Player(int playerNumber)
	:symbol(playerNumber)
{
}


Player::~Player()
{
}

bool Player::PlaceSymbol(int row, int column)
{
	// Check if placement is valid	
	if (row <= 2 && row >= 0 && column <= 2 && column >= 0)
	{
		// if board is not taken put symbol on board
		if (gameBoard->GetBoardValue(row, column) == 0)
		{
			gameBoard->SetBoardValue(row, column, symbol);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	
		
}

bool Player::IsMyTurn() const
{
	return isMyTurn;
}

void Player::SetIsMyTurn(bool isMyTurn)
{
	this->isMyTurn = isMyTurn;
}

void Player::SetGameBoard(GameBoard * gameBoard)
{
	this->gameBoard = gameBoard;
}


void Player::InitializeAI()
{
	ai = new AIComponent();
	ai->SetOwningPlayer(this);
}

AIComponent * Player::GetAI()
{
	return ai;
}
