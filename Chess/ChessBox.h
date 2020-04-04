#pragma once
#include "Figure.h"

class ChessBox
{
public:
	ChessBox(int row, int col, bool isWhite, const Figure &currentfigure);
	ChessBox(int row, int col, bool isWhite);
	ChessBox(const ChessBox &rhs);
	ChessBox &operator=(const ChessBox &rhs);
	~ChessBox();

private:
	int row;
	int col;
	bool isWhite;
	Figure *currentFigure;

public:
	int getRow() const;
	int getCol() const;
	bool getIsWhite() const;
	Figure *getFigure() const;
	void setFigure(const Figure &figure);

	void destroyFigure();
	bool isFigureOn();

private:
	void copyFrom(const ChessBox &rhs);
	void clear();
};