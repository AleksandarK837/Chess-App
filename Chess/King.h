#pragma once
#include "Figure.h"

class King : public Figure
{
public:
	King(int row, int col, bool isWhite);
	void moveTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};