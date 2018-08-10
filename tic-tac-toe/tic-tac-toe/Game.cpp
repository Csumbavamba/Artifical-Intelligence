#include "Game.h"
#include "GameBoard.h"
#include "Player.h"

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
	std::cout << "| 2. CHANGE DIFFICULTY  |" << std::endl;
	std::cout << "| 3.	 QUIT GAME	|" << std::endl;
	std::cout << "|=======================|" << std::endl;

	int menuChoice;

	std::cout << std::endl;
	std::cout << "Choice: ";
	std::cin >> menuChoice;

	switch (menuChoice)
	{
		case 1:
		{
			gameBoard->DrawBoard();
			currentGameState = PLAYING;
			PlayGame();
		}
		case 2:
		{
			// TODO select Difficulty
			ShowStartMenu();
		}
		case 3:
		{
			// TODO Show quit message
			return;
		}
		default:
			ShowStartMenu();
	}

	
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
			// TODO call AI function here
			GetPlayerInput(currentPlayerOnTurn);
		}

		gameBoard->DrawBoard();
	}

	ShowEndScreen();

}

Player * Game::GetNextPlayerOnTurn()
{
	// If it's the player's turn
	if (player->IsMyTurn())
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
		std::cout << "Select the row you want to place your symbol in: ";
		int row;
		std::cin >> row;
		std::cout << std::endl;

		std::cout << "Select the column you want to place your symbol in: ";
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
	std::cout << std::endl;
	std::cout << "GAME OVER!!!" << std::endl;
	Sleep(2000);

	ShowStartMenu();
}
