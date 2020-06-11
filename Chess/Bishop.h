#pragma once
#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop(int row, int column, bool isWhite);
	void moveTo(int row, int column) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};