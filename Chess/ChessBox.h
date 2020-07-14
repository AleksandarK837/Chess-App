#pragma once
#include "Figure.h"

class ChessBox
{
public:
	ChessBox(int row, int column, Color color, const Figure &currentfigure);
	ChessBox(int row, int column, Color color);
	ChessBox(const ChessBox &rhs);
	ChessBox &operator=(const ChessBox &rhs);
	~ChessBox();

private:
	int row;
	int column;
	Color color;
	Figure *currentFigure;

public:
	int getRow() const;
	int getColumn() const;
	Color colorFigure() const;
	Figure *getFigure() const;
	void setFigure(const Figure &figure);

	void destroyFigure();
	bool isFigureOn();
private:
	void copyFrom(const ChessBox &rhs);
	void clear();
};