#pragma once
#include <iostream>
#include "GlobalVariables.h"
using namespace std;
using namespace GlobalVaribles;

class Figure
{
public:
	Figure(int row, int column, Color color);

protected:
	int row;
	int column;
	Color color;
	bool inPlay;

public:
	void setRow(int row);
	void setColumn(int column);

	int getRow() const;
	int getColumn() const;
	Color colorFigure() const;

	bool isValidPosition(int row, int column) const;
	void destroyFigure();
	virtual void moveTo(int row, int column) = 0;
	virtual Figure *clone() const = 0;
	virtual string getFigureType() const = 0;
};
