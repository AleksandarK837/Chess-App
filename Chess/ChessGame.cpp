#include "ChessGame.h"

ChessGame::ChessGame() :isWhitePlayerTurn(true)
{
}

void ChessGame::startGame()
{
	chessBoard.placeFigures();
}

void ChessGame::moveFigure(ChessBox start, ChessBox end)
{
	if (start.getFigure()->getIsWhite() == isWhitePlayerTurn)
	{
		if (chessBoard.moveFigureTo(start, end))
		{
			isWhitePlayerTurn = !isWhitePlayerTurn;
		}
		else
		{
			cout << "Move again!\n";
		}
	}
	else
	{
		throw std::logic_error("It's opponet's turn now!\n");
	}
}

void ChessGame::moveFigure(int fromRow, int fromColumn, int toRow, int toColumn)
{
	try
	{
		const ChessBox &start = chessBoard.getChessBoxByCoordinates(fromRow, fromColumn);
		const ChessBox &end = chessBoard.getChessBoxByCoordinates(toRow, toColumn);
		moveFigure(start, end);
	}
	catch (const std::logic_error &e)
	{
		cerr << e.what();
	}
}
