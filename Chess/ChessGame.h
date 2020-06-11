#pragma once
#include "ChessBoard.h"

class ChessGame
{
public:
	ChessGame();

private:
	bool isWhitePlayerTurn;
	ChessBoard chessBoard;

public:
	void startGame();
	void moveFigure(int fromRow, char fromColumn, int toRow, char toColumn);

private:
	void moveFigure(ChessBox start, ChessBox end);
};