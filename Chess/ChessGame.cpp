#include "ChessGame.h"

ChessGame::ChessGame() :isWhitePlayerTurn(true)
{
}

void ChessGame::startGame()
{
	chessBoard.placeFigures();
}

void ChessGame::moveFigure(ChessBox & start, ChessBox & end)
{
	if (start.getFigure()->getIsWhite() == isWhitePlayerTurn)
	{
		if (chessBoard.moveFigureTo(start, end))
		{
			isWhitePlayerTurn = !isWhitePlayerTurn;
		}
		else
		{
			cout<<"Move again!\n";
		}
	}
	else
	{
		cout << "It's opponet's turn now\n";
	}
}
