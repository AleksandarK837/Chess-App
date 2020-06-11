#pragma once
#include "Figure.h"

class Rook : public Figure
{
public:
	Rook(int row, int column, bool isWhite);
	void moveTo(int row, int column) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};