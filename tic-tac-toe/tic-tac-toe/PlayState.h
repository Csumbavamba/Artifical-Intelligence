#pragma once

#include <vector>

enum ScorePreference
{
	MINIMUM,
	MAXIMUM
};


class PlayState
{
public:
	PlayState();
	~PlayState();

	ScorePreference GetScorePreference() const;
	void SetScorePreference(ScorePreference scorePreference);
	PlayState * GetParentState() const;
	void SetParentState(PlayState * parentState);
	int GetScore() const;
	void SetScore(int score);
	bool GetIsEndState() const;

	int CalculateScore();	
	bool IsLastStep();


private:
	int board[3][3]{}; // Contains the current state of the game
	int score;
	bool isEndState = false;

	ScorePreference scorePreference;
	PlayState * parentPlayState = nullptr; // Previous step
	std::vector<PlayState*> ChildrenPlayStates; // Next steps


};

