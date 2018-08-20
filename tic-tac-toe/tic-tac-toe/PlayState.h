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
	PlayState(int changedRow, int changedColumn);
	~PlayState();

	void SetupPlayState();

	ScorePreference GetScorePreference() const;
	void SetScorePreference(ScorePreference scorePreference);
	PlayState * GetParentState() const;
	void SetParentState(PlayState * parentState);
	std::vector<PlayState*> GetChildrenPlayStates();
	void AddToChildren(PlayState * child);

	int GetBoardValue(int row, int column) const;

	int GetScore() const;
	void SetScore(int score);
	int GetChangedRow() const;
	void SetChangedRow(int changedRow);
	int GetChangedColumn() const;
	void SetChangedColumn(int changedColumn);
	void SetBoardValue(int row, int column, int value);


	bool IsEndState();	
	int GetWinningPlayer();
	bool IsLastStep();
	


private:

	int board[3][3]{}; // Contains the current state of the game
	int score;
	
	int changedRow;
	int changedColumn;

	ScorePreference scorePreference;
	PlayState * parentPlayState = nullptr; // Previous step
	std::vector<PlayState*> childrenPlayStates; // Next steps


};

