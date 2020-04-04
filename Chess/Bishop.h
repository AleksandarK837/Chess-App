#pragma once
#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop(int row, int col, bool isWhite);
	bool movedTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};