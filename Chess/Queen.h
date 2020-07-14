#pragma once
#include "Figure.h"

class Queen : public Figure
{
public:
	Queen(int row, int column, Color color);
	void moveTo(int row, int column) override;
	Figure *clone() const override;
	std::string getFigureType() const override;
};