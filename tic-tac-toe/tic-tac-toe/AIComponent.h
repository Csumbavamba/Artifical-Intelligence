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
	void GeneratePlayStates();
	void AddToPotentialPlayStates(PlayState* generatedPlayState);
	PlayState * SelectBestPlay();

private:
	Player * owner = nullptr;
	GameBoard * board = nullptr;
	PlayState * currentPlayState = nullptr;
	std::vector <PlayState*> potentialPlayStates;
	

	// Generate new states
		// Is there an end state?
			// If there is an end state --> give Score to state
			// Otherwise generate more states and check again

};

