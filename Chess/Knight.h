#pragma once
#include "Figure.h"

class Knight : public Figure
{
public:
	Knight(int row, int col, bool isWhite);
	void moveTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};
