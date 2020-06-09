#pragma once
#include "Figure.h"

class Queen : public Figure
{
public:
	Queen(int row, int col, bool isWhite);
	void moveTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};