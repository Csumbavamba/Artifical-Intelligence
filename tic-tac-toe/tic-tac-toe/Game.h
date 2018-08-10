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
	void SetUpGame();
	void PlayGame();
	Player * GetNextPlayerOnTurn();
	void GetPlayerInput(Player * playerOnTurn);
	bool IsGameOver();
	void ShowEndScreen();

private:
	GameBoard * gameBoard = nullptr;
	Player * player = nullptr;
	Player * AI = nullptr;
	GameState currentGameState = SETUP;
};

