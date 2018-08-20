#include "PlayState.h"
#include "Game.h"

#include <vector>
#include <algorithm>



PlayState::PlayState()
	:scorePreference(MAXIMUM)
{
}

PlayState::PlayState(int changedRow, int changedColumn)
	: changedRow(changedRow)
	, changedColumn(changedColumn)
{
}


PlayState::~PlayState()
{
}

void PlayState::SetupPlayState()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (parentPlayState != nullptr)
				board[i][j] = parentPlayState->board[i][j]; // Copy state of the board
		}
	}

	// If this is the first PlayState
	if (parentPlayState != nullptr)
	{

		int symbol;
		// If this was a player turn
		if (parentPlayState->GetScorePreference() == MINIMUM) // MAXIMUM
		{
			scorePreference = MAXIMUM;
			symbol = 1;
		}
		// If this was an AI turn
		else
		{
			scorePreference = MINIMUM;
			symbol = 2;
		}

		board[changedRow][changedColumn] = symbol;
	}

	
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

std::vector<PlayState*> PlayState::GetChildrenPlayStates()
{
	return childrenPlayStates;
}

void PlayState::AddToChildren(PlayState * child)
{
	childrenPlayStates.push_back(child);
}

int PlayState::GetBoardValue(int row, int column) const
{
	return board[row][column];
}

void PlayState::SetBoardValue(int row, int column, int value)
{
	board[row][column] = value;
}

int PlayState::GetScore() const
{
	return score;
}

void PlayState::SetScore(int score)
{
	this->score = score;
}



int PlayState::GetChangedRow() const
{
	return changedRow;
}

void PlayState::SetChangedRow(int changedRow)
{
	this->changedRow = changedRow;
}

int PlayState::GetChangedColumn() const
{
	return changedColumn;
}

void PlayState::SetChangedColumn(int changedColumn)
{
	this->changedColumn = changedColumn;
}





bool PlayState::IsEndState()
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
		return true;
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
		// AI WON
		return true;
	}

	if (IsLastStep())
	{
		return true;
	}

	return false;
}

int PlayState::GetWinningPlayer()
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
		return 1;
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
		// AI WON
		return 2;
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
