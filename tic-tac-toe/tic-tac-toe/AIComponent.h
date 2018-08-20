#pragma once
#include <vector>

class Player;
class GameBoard;
class PlayState;


class AIComponent
{
public:
	AIComponent();
	~AIComponent();

	void SetOwningPlayer(Player * owner);
	void SetGameBoard(GameBoard * gameBoard);
	void SetDifficulty(bool difficultAI);

	void GenerateCurrentPlayStateFromGameBoard(GameBoard * gameBoard);
	void GenerateChildrenPlayStates(PlayState * parentPlayState);
	void CreateFirstRoundOfPlayStates();

	void AddToPotentialPlayStates(PlayState* generatedPlayState); 
	void ClearPotentialPlayStates();

	void CalculatePotentialPlayStateScores();
	int MaximiseScore(PlayState * startingPlayState);
	int MinimiseScore(PlayState * startingPlayState);
	PlayState * SelectBestPlay(); // Select best play from the avialable next steps
	PlayState * SelectRandomPlayState(); // Easy AI
	void PlaceSymbol();
	
	int GetChildrenChecked() const; // Check for Pruning
	
	

private:
	Player * owner = nullptr;
	GameBoard * board = nullptr;
	PlayState * currentPlayState = nullptr;
	std::vector <PlayState*> potentialPlayStates;

	int childrenChecked = 0;

	bool isDifficultAI = true;
	

};

