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
	ChessBox *chessBoard[ROW_SIZE][COLUMN_SIZE];

public:
	void placeFigures(); //fill the chess board
	void moveFigureTo(ChessBox &start, ChessBox &end);
	bool isCheckmate(Color color);

private:
	void moveKnightTo(Figure &knight, int row, int column);
	void movePawnTo(Figure &pawn, int row, int column);
	void moveOtherFigures(Figure &figure, int row, int column);
	void destroyOponentsFigure(Figure &figure, int row, int column);
	void moveToEmptyBox(Figure &figure, int row, int column);

	bool PathBetweenBoxesFree(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesRook(const ChessBox &start, const ChessBox &end);
	bool freePathBetweenBoxesBishop(const ChessBox &start, const ChessBox &end);

	bool playerHasPossileMoves(const Figure &figure);
	bool canMoveKing(int kingRowPosition, int kingColumnPosition);
	bool protectKingWithKnight(int knightRowPosition, int knightColumnPosition);
	bool protectKingWithPawn(int pawnRowPosition, int pawnColumnPosition);
	bool protectKingWithBishop(int bishopRowPosition, int bishopColumnPosition);
	bool protectKingWithRook(int rookRowPosition, int rookColumnPosition);

	bool isInChess(Color colorKing) const;
	bool areValidChessBoxCoordinates(int row, int column) const;
	const ChessBox &getKingsBox(Color colorKing) const;

	void copyFrom(const ChessBoard &rhs);
	void clear();

public:
	const ChessBox &getChessBoxByCoordinates(int row, int column) const;
};