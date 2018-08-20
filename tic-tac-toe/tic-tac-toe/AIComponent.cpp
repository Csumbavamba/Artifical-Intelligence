#include "AIComponent.h"
#include "PlayState.h"
#include "Player.h"
#include "GameBoard.h"

#include <time.h>
#include <vector>
#include <algorithm>


AIComponent::AIComponent()
{
	std::srand(unsigned(time(0)));
}


AIComponent::~AIComponent()
{
	delete currentPlayState;
}

void AIComponent::SetOwningPlayer(Player * owner)
{
	this->owner = owner;
}

void AIComponent::SetGameBoard(GameBoard * gameBoard)
{
	board = gameBoard;
}


void AIComponent::SetDifficulty(bool isDifficultAI)
{
	this->isDifficultAI = isDifficultAI;
}

void AIComponent::GenerateCurrentPlayStateFromGameBoard(GameBoard * gameBoard)
{
	currentPlayState = new PlayState();

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			// Copy the values from the gameBoard
			currentPlayState->SetBoardValue(i, j, gameBoard->GetBoardValue(i, j));
		}
	}
}

// Creates  Children states (depth first)
void AIComponent::GenerateChildrenPlayStates(PlayState * parentPlayState)
{
	// If current state is not and endstate
	if (!parentPlayState->IsEndState())
	{
		// Generate PlayStates based on the newly populated area
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (parentPlayState->GetBoardValue(i, j) == 0)
				{
					PlayState * childPlayState = new PlayState(i, j);
					childPlayState->SetParentState(parentPlayState);
					parentPlayState->AddToChildren(childPlayState);
					childPlayState->SetupPlayState();

					// Stop Generating once it's an endstate
					if (!childPlayState->IsEndState())
					{
						GenerateChildrenPlayStates(childPlayState);
					}
					
				}
			}
		}
	}
}

void AIComponent::CreateFirstRoundOfPlayStates()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (currentPlayState->GetBoardValue(i, j) == 0)
			{
				// Setup
				PlayState * potentialMove = new PlayState(i, j);
				potentialMove->SetParentState(currentPlayState);
				currentPlayState->AddToChildren(potentialMove);
				potentialMove->SetScorePreference(MINIMUM); // AI should select the move that gives the maximum point (out of the minimum children)
				potentialMove->SetupPlayState();

				// Add it to potential moves
				AddToPotentialPlayStates(potentialMove);
			}
			
		}
	}
}

void AIComponent::AddToPotentialPlayStates(PlayState * generatedPlayState)
{
	potentialPlayStates.push_back(generatedPlayState);
}

void AIComponent::ClearPotentialPlayStates()
{
	potentialPlayStates.clear();
}

void AIComponent::CalculatePotentialPlayStateScores()
{
	// Go through each element of the vector (calculate their score)
	for (PlayState * potentialMove : potentialPlayStates)
	{
		GenerateChildrenPlayStates(potentialMove);
		potentialMove->SetScore(MinimiseScore(potentialMove));
	}

}

int AIComponent::MaximiseScore(PlayState * startingPlayState)
{
	int highestScore = -999;

	for (PlayState * playerMovement : startingPlayState->GetChildrenPlayStates())
	{

		// If Player Won return -10
		if (playerMovement->GetWinningPlayer() == 1)
		{
			return -10;
		}
		// If AI won return 10
		else if (playerMovement->GetWinningPlayer() == 2)
		{
			return 10;
		}
		// If full board return 0
		else if (playerMovement->IsLastStep() == true)
		{
			return 0;
		}

		// Otherwise, Select the minimum from their children
		playerMovement->SetScore(MinimiseScore(playerMovement));

		if (playerMovement->GetScore() > highestScore)
		{
			childrenChecked++;
			highestScore = playerMovement->GetScore();

			// Pruning - COMMENT out to see the difference
			if (highestScore == 10)
			{
				return highestScore;
			}
		}
			
	}

	return highestScore;
}

int AIComponent::MinimiseScore(PlayState * startingPlayState)
{
	int lowestScore = 999; 

	for (PlayState * AIMovement : startingPlayState->GetChildrenPlayStates())
	{

		// If Player Won return -10
		if (AIMovement->GetWinningPlayer() == 1)
		{
			return -10;
		}
		// If AI won return 10
		else if (AIMovement->GetWinningPlayer() == 2)
		{
			return 10;
		}
		// If full board return 0
		else if (AIMovement->IsLastStep() == true)
		{
			return 0;
		}

		// Otherwise, Select the maximum from their children
		AIMovement->SetScore(MaximiseScore(AIMovement));

		if (AIMovement->GetScore() < lowestScore)
		{
			childrenChecked++;
			lowestScore = AIMovement->GetScore();

			// Pruning - COMMENT out to see the difference
			if (lowestScore == -10)
			{
				return lowestScore;
			}
		}
			


	}

	return lowestScore;
}

PlayState * AIComponent::SelectBestPlay()
{
	if (potentialPlayStates.empty()) { return nullptr; }

	PlayState * bestPlay = potentialPlayStates.at(0);

	// Go through the generated gameState first moves
	for (PlayState * move : potentialPlayStates)
	{
		// If next move would win you the game, take that move
		if (move->GetWinningPlayer() == 2)
		{
			bestPlay = move;
			return bestPlay;
		}
		else if (move->GetScore() > bestPlay->GetScore())
			bestPlay = move;
	}

	return bestPlay;
}

void AIComponent::PlaceSymbol()
{
	GenerateCurrentPlayStateFromGameBoard(board);
	CreateFirstRoundOfPlayStates();
	CalculatePotentialPlayStateScores();

	PlayState * bestPlay = nullptr;

	if (isDifficultAI)
	{
		bestPlay = SelectBestPlay();
	}
	else
	{
		bestPlay = SelectRandomPlayState();
	}
		

	if (bestPlay == nullptr) { return; }

	// Get the changeRow and changeColumn positions for the ideal play
	int moveRow = bestPlay->GetChangedRow();
	int moveColumn = bestPlay->GetChangedColumn();

	// Place Symbol to that position
	owner->PlaceSymbol(moveRow, moveColumn);
	ClearPotentialPlayStates();

	// Reset currentPlayState
	delete currentPlayState;
	currentPlayState = nullptr;
}

int AIComponent::GetChildrenChecked() const
{
	return childrenChecked;
}

PlayState * AIComponent::SelectRandomPlayState()
{
	if (potentialPlayStates.empty()) { return nullptr; }

	// Randomize elements
	std::random_shuffle(potentialPlayStates.begin(), potentialPlayStates.end());

	return potentialPlayStates.back();

}

