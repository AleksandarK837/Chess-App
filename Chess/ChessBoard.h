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
	void placeFigures(); //fill the chess board
	bool moveFigureTo(ChessBox &start, ChessBox &end);

private:
	void moveKnightTo(Figure &knight, int row, int col);
	void movePawnTo(Figure &pawn, int row, int col);
	void moveOtherFigures(Figure &figure, int row, int col);
	void moveToNonEmptyBox(Figure &figure, int row, int col);
	void moveToEmptyBox(Figure &figure, int row, int col);

	bool PathBetweenBoxesFree(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesRook(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesBishop(const ChessBox &start, const ChessBox &end);


	bool isInChess(bool isWhiteKing) const;
	bool areValidChessBoxCoordinates(int row, int col) const;
	ChessBox &getKingsBox(bool isWhiteKing) const;

	void copyFrom(const ChessBoard &rhs);
	void clear();

public:
	ChessBox &getChessBoxByCoordinates(int row, int column) const;
};