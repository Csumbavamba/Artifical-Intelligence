#pragma once

class GameBoard;
class Player;

enum GameState
{
	SETUP,
	PLAYING,
	BOARDFULL,
	PLAYERWON,
	AIWON
};

class Game
{
public:
	Game();
	~Game();

	void ShowStartMenu();
	void SelectDifficulty();
	void SetUpGame();
	void SelectGameMode();
	void PlayGame();
	Player * GetNextPlayerOnTurn();
	void GetPlayerInput(Player * playerOnTurn);
	bool IsGameOver();
	void ShowEndScreen();
	void ResetGame();

	// TODO Create Pruning


private:
	GameBoard * gameBoard = nullptr;
	Player * player = nullptr;
	Player * AI = nullptr;
	GameState currentGameState = SETUP;

	bool isDifficultAI = false;
	bool isGameAgainstAI = true;
};

