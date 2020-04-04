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
	void moveFigure(ChessBox &start, ChessBox &end);
};