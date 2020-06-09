#pragma once
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn(int row, int col, bool isWhite);
	void moveTo(int row, int col) override;
	Figure *clone() const override;
	std::string getFigureType() const override;

private:
	bool isMoved;
};