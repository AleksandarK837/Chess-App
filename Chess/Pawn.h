#pragma once
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(int row, int column, Color color);
	void moveTo(int row, int column) override;
	Figure *clone() const override;
	std::string getFigureType() const override;

private:
	bool isMoved;
};