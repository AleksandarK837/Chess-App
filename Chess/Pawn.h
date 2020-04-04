#pragma once
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(int row, int col, bool isWhite);
	bool movedTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;

private:
	bool isMoved;
};