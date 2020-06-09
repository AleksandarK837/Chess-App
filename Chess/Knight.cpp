#include "Knight.h"

Knight::Knight(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

void Knight::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!");
	}

	// we move horse (2 steps up/down and 1 aside) or (1 step up/down  and 2 aside)
	int absRow = abs(this->row - row);
	int absCol = abs(this->col - col);

	if ((absRow == 2 && absCol == 1) || (absRow == 1 and absCol == 2))
	{
		setRow(row);
		setCol(col);
	}
	else
	{
		throw std::logic_error("Invalid Knight Position!");
	}
}

Figure * Knight::clone() const
{
	return new Knight(*this);
}

std::string Knight::getFigureType() const
{
	return "Knight";
}
