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
	if (start.getFigure()->isWhiteFigure() == isWhitePlayerTurn)
	{
		chessBoard.moveFigureTo(start, end);
	}
	else
	{
		throw std::logic_error("It's opponet's turn now!\n");
	}
}

void ChessGame::moveFigure(int fromRow, char fromColumn, int toRow, char toColumn)
{

	try
	{
		const ChessBox &startBox = chessBoard.getChessBoxByCoordinates(fromRow - 1, (int)fromColumn - 97);
		const ChessBox &endBox = chessBoard.getChessBoxByCoordinates(toRow - 1, (int)toColumn - 97);
		moveFigure(startBox, endBox);
		isWhitePlayerTurn = !isWhitePlayerTurn;
		cout << "Successfully moved from " << fromRow << fromColumn << " to " << toRow << toColumn << endl;
	}
	catch (const std::logic_error &e)
	{
		cerr << e.what();
	}
	catch (const std::bad_alloc &b)
	{
		cerr << b.what();
	}
}
