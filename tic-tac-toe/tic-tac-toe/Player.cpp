#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::PlaceSymbol(int row, int column)
{
}

bool Player::IsMyTurn() const
{
	return isMyTurn;
}

void Player::SetIsMyTurn(bool isMyTurn)
{
	this->isMyTurn = isMyTurn;
}

void Player::InitializeAI()
{

}

AIComponent * Player::GetAI()
{
	return ai;
}
