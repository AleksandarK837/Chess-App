#pragma once
#include "ChessBox.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

class ChessBoard
{
public:
	ChessBoard();
	ChessBoard(const ChessBoard &rhs);
	ChessBoard &operator=(const ChessBoard &rhs);
	~ChessBoard();

private:
	ChessBox *chessBoard[ROW_SIZE][COL_SIZE];

public:
	bool movedFigureTo(ChessBox &start, ChessBox &end);
	void placeFigures(); //fill the chess board

private:
	bool movedKnightTo(Figure &knight, int row, int col);
	bool movedPawnTo(Figure &pawn, int row, int col);
	bool movedOtherFigures(Figure &figure, int row, int col);

	bool PathBetweenBoxesFree(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesRook(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesBishop(const ChessBox &start, const ChessBox &end);


	bool isInChess(bool isWhiteKing) const;
	bool areValidChessBoxCoordinates(int row, int col) const;
	ChessBox &getKingsBox(bool isWhiteKing) const;

	void copyFrom(const ChessBoard &rhs);
	void clear();
};