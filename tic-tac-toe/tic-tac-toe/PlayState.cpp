#include "PlayState.h"
#include "Game.h"



PlayState::PlayState()
{
}


PlayState::~PlayState()
{
}

ScorePreference PlayState::GetScorePreference() const
{
	return scorePreference;
}

void PlayState::SetScorePreference(ScorePreference scorePreference)
{
	this->scorePreference = scorePreference;
}

PlayState * PlayState::GetParentState() const
{
	return parentPlayState;
}

void PlayState::SetParentState(PlayState * parentPlayState)
{
	this->parentPlayState = parentPlayState;
}

int PlayState::GetScore() const
{
	return score;
}

void PlayState::SetScore(int score)
{
	this->score = score;
}

bool PlayState::GetIsEndState() const
{
	return isEndState;
}



int PlayState::CalculateScore()
{
	// Check if player won
	if ((board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) ||	// Row Victory
		(board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) ||	// Row Victory
		(board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) ||	// Row Victory

		(board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) ||	// Column Victory
		(board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) ||	// Column Victory 
		(board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) ||	// Column Victory

		(board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) ||	// Diagonal Victory
		(board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1))	// Diagonal Victory
	{
		// PLAYER WON
		isEndState = true;
		return -10;
	}


	// Check if AI won
	if ((board[0][0] == 2 && board[0][1] == 2 && board[0][2] == 2) ||	// Row Victory
		(board[1][0] == 2 && board[1][1] == 2 && board[1][2] == 2) ||	// Row Victory
		(board[2][0] == 2 && board[2][1] == 2 && board[2][2] == 2) ||	// Row Victory

		(board[0][0] == 2 && board[1][0] == 2 && board[2][0] == 2) ||	// Column Victory
		(board[0][1] == 2 && board[1][1] == 2 && board[2][1] == 2) ||	// Column Victory 
		(board[0][2] == 2 && board[1][2] == 2 && board[2][2] == 2) ||	// Column Victory

		(board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2) ||	// Diagonal Victory
		(board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2))	// Diagonal Victory
	{
		// AIO WON
		isEndState = true;
		return 10;
	}

	if (IsLastStep())
	{
		isEndState = true;
	}

	return 0;
}

bool PlayState::IsLastStep()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
