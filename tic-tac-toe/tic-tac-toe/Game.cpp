#include "Game.h"
#include "GameBoard.h"
#include "Player.h"
#include "AIComponent.h"

#include <iostream>
#include <Windows.h>



Game::Game()
{
}


Game::~Game()
{
	delete gameBoard;
	delete player;
	delete AI;
}

void Game::ShowStartMenu()
{	
	system("cls");

	std::cout << "|=======================|" << std::endl;
	std::cout << "| 1.  START A NEW GAME  |" << std::endl;
	std::cout << "| 2.	 QUIT GAME	|" << std::endl;
	std::cout << "|=======================|" << std::endl;

	int menuChoice;

	std::cout << std::endl;
	std::cout << "Choice: ";
	std::cin >> menuChoice;

	switch (menuChoice)
	{
		case 1: // Start New Game
		{
			SelectGameMode();
			break;
		}
		case 2: // Change Difficulty
		{
			return;
		}
		default:
			ShowStartMenu();
			break;
	}

	
}

void Game::SelectDifficulty()
{
	system("cls");

	std::cout << "|=======================|" << std::endl;
	std::cout << "| 1.	DUMB AI		|" << std::endl;
	std::cout << "| 2.	SMART AI	|" << std::endl;
	std::cout << "|=======================|" << std::endl;

	int difficultyChoice;

	std::cout << std::endl;
	std::cout << "Select Difficulty: ";
	std::cin >> difficultyChoice;

	std::cout << std::endl;

	switch (difficultyChoice)
	{
	case 1: // DUMB AI
	{
		isDifficultAI = false;
		std::cout << "Difficulty set to EASY...";
		break;
	}
	case 2: // SMART AI
	{
		isDifficultAI = true;
		std::cout << "Difficulty set to HARD...";
		break;

	}
	default:
		SelectDifficulty();
	}
	
	Sleep(2000);

	AI->GetAI()->SetDifficulty(isDifficultAI);

	// Start the Game
	gameBoard->DrawBoard();
	currentGameState = PLAYING;
	PlayGame();

}

void Game::SetUpGame()
{
	// Initialize variables
	gameBoard = new GameBoard();
	player = new Player(1);
	AI = new Player(2);

	player->SetIsMyTurn(true);
	AI->SetIsMyTurn(false);

	player->SetGameBoard(gameBoard);
	AI->SetGameBoard(gameBoard);

}

void Game::SelectGameMode()
{
	system("cls");

	std::cout << "|=======================|" << std::endl;
	std::cout << "| 1. Human vs Human	|" << std::endl;
	std::cout << "| 2. Human vs Computer	|" << std::endl;
	std::cout << "|=======================|" << std::endl;

	int gameModeChoice;

	std::cout << std::endl;
	std::cout << "Choice: ";
	std::cin >> gameModeChoice;

	std::cout << std::endl;

	switch (gameModeChoice)
	{
	case 1: // Human vs Human
	{
		std::cout << "Get Ready For Battle!!!";
		isGameAgainstAI = false;
		break;
	}
	case 2: // vs Computer
	{
		std::cout << "Computer Initializing...";
		isGameAgainstAI = true;
		AI->InitializeAI();
		break;

	}
	}

	Sleep(2000);

	SelectDifficulty();

	
}

void Game::PlayGame()
{
	while (!IsGameOver())
	{
		Player * currentPlayerOnTurn = GetNextPlayerOnTurn();

		if (currentPlayerOnTurn == player)
		{
			GetPlayerInput(currentPlayerOnTurn);
		}
		else
		{
			if (isGameAgainstAI) // IF AI
			{
				Sleep(500);
				AI->GetAI()->PlaceSymbol();
			}
			else
			{
				GetPlayerInput(currentPlayerOnTurn);
			}
		}

		gameBoard->DrawBoard();

		// Uncomment to Check for Pruning Difference - Need to comment in AI Component as well
		// std::cout << AI->GetAI()->GetChildrenChecked() << std::endl;
	}

	ShowEndScreen();

}

Player * Game::GetNextPlayerOnTurn()
{
	// If it's the player's turn
	if (player->GetIsMyTurn())
	{
		player->SetIsMyTurn(false);
		AI->SetIsMyTurn(true);
		return player;
	}
	// If it's the AI's turn
	else
	{
		player->SetIsMyTurn(true);
		AI->SetIsMyTurn(false);
		return AI;
	}
}

void Game::GetPlayerInput(Player * playerOnTurn)
{
	bool validMove = false;

	// Get Player Input until it's valid
	do
	{
		std::cout << "Row to place on: ";
		int row;
		std::cin >> row;
		std::cout << std::endl;

		std::cout << "COLUMN to place on: ";
		int column;
		std::cin >> column;
		std::cout << std::endl;

		if (!playerOnTurn->PlaceSymbol(row, column))
		{
			std::cout << "Invalid movement." << std::endl;
			Sleep(2000);

			gameBoard->DrawBoard();
			
			
		}
		else
		{
			validMove = true;
		}

	} while (validMove == false);

	

}

bool Game::IsGameOver()
{
	// Check if player won
	if ((gameBoard->GetBoardValue(0, 0) == 1 && gameBoard->GetBoardValue(0, 1) == 1 && gameBoard->GetBoardValue(0, 2) == 1) ||	// Row Victory
		(gameBoard->GetBoardValue(1, 0) == 1 && gameBoard->GetBoardValue(1, 1) == 1 && gameBoard->GetBoardValue(1, 2) == 1) ||	// Row Victory
		(gameBoard->GetBoardValue(2, 0) == 1 && gameBoard->GetBoardValue(2, 1) == 1 && gameBoard->GetBoardValue(2, 2) == 1) ||	// Row Victory

		(gameBoard->GetBoardValue(0, 0) == 1 && gameBoard->GetBoardValue(1, 0) == 1 && gameBoard->GetBoardValue(2, 0) == 1) ||	// Column Victory
		(gameBoard->GetBoardValue(0, 1) == 1 && gameBoard->GetBoardValue(1, 1) == 1 && gameBoard->GetBoardValue(2, 1) == 1) ||	// Column Victory 
		(gameBoard->GetBoardValue(0, 2) == 1 && gameBoard->GetBoardValue(1, 2) == 1 && gameBoard->GetBoardValue(2, 2) == 1) ||	// Column Victory

		(gameBoard->GetBoardValue(0, 0) == 1 && gameBoard->GetBoardValue(1, 1) == 1 && gameBoard->GetBoardValue(2, 2) == 1) ||	// Diagonal Victory
		(gameBoard->GetBoardValue(0, 2) == 1 && gameBoard->GetBoardValue(1, 1) == 1 && gameBoard->GetBoardValue(2, 0) == 1))	// Diagonal Victory
	{
		currentGameState = PLAYERWON;
		return true;
	}
	// Check if AI won
	else if ((gameBoard->GetBoardValue(0, 0) == 2 && gameBoard->GetBoardValue(0, 1) == 2 && gameBoard->GetBoardValue(0, 2) == 2) ||	// Row Victory
		(gameBoard->GetBoardValue(1, 0) == 2 && gameBoard->GetBoardValue(1, 1) == 2 && gameBoard->GetBoardValue(1, 2) == 2) ||	// Row Victory
		(gameBoard->GetBoardValue(2, 0) == 2 && gameBoard->GetBoardValue(2, 1) == 2 && gameBoard->GetBoardValue(2, 2) == 2) ||	// Row Victory

		(gameBoard->GetBoardValue(0, 0) == 2 && gameBoard->GetBoardValue(1, 0) == 2 && gameBoard->GetBoardValue(2, 0) == 2) ||	// Column Victory
		(gameBoard->GetBoardValue(0, 1) == 2 && gameBoard->GetBoardValue(1, 1) == 2 && gameBoard->GetBoardValue(2, 1) == 2) ||	// Column Victory 
		(gameBoard->GetBoardValue(0, 2) == 2 && gameBoard->GetBoardValue(1, 2) == 2 && gameBoard->GetBoardValue(2, 2) == 2) ||	// Column Victory

		(gameBoard->GetBoardValue(0, 0) == 2 && gameBoard->GetBoardValue(1, 1) == 2 && gameBoard->GetBoardValue(2, 2) == 2) ||	// Diagonal Victory
		(gameBoard->GetBoardValue(0, 2) == 2 && gameBoard->GetBoardValue(1, 1) == 2 && gameBoard->GetBoardValue(2, 0) == 2))	// Diagonal Victory
	{
		currentGameState = AIWON;
		return true;
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (gameBoard->GetBoardValue(i, j) == 0)
				{
					return false;
				}
			}
		}
	}

	currentGameState = BOARDFULL;
	return true;
}

void Game::ShowEndScreen()
{
	if (currentGameState == PLAYERWON)
	{
		if (isGameAgainstAI)
		{
			std::cout << std::endl;
			std::cout << "CONGRATULATIONS YOU HAVE WON!!!" << std::endl;
		}
		else
		{
			std::cout << std::endl;
			std::cout << "Player 1 Won!!" << std::endl;
		}
		
	}
	else if (currentGameState == AIWON)
	{
		if (isGameAgainstAI)
		{
			std::cout << std::endl;
			std::cout << "SHAME!!!" << std::endl;
		}
		else
		{
			std::cout << std::endl;
			std::cout << "Player 2 Won!!" << std::endl;
		}

		
	}
	else
	{
		std::cout << std::endl;
		std::cout << "IT'S A DRAW!!!" << std::endl;
	}
	
	Sleep(2000);

	ResetGame();
	ShowStartMenu();
}

void Game::ResetGame()
{
	delete gameBoard;
	delete player;
	delete AI;

	gameBoard = nullptr;
	player = nullptr;
	AI = nullptr;

	SetUpGame();

}
