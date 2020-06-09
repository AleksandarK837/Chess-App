#pragma once
#include <iostream>
#include "GlobalVariables.h"
using namespace std;
using namespace GlobalVaribles;

class Figure
{
public:
	Figure(int row, int col, bool isWhite);

protected:
	int row;
	int col;
	const bool isWhite;
	bool inPlay;

public:
	void setRow(int row);
	void setCol(int col);

	int getRow() const;
	int getCol() const;
	bool getIsWhite() const;

	bool isValidPosition(int row, int col) const;
	void destroyFigure();
	virtual void moveTo(int row, int col) = 0;
	virtual Figure *clone() const = 0;
	virtual string getFigureType() const = 0;
};
