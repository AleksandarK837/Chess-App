#include "Knight.h"

Knight::Knight(int row, int column, bool isWhite) : Figure(row, column, isWhite)
{
}

void Knight::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	// we move horse (2 steps up/down and 1 aside) or (1 step up/down  and 2 aside)
	int absRow = abs(this->row - row);
	int absCol = abs(this->column - column);

	if ((absRow == 2 && absCol == 1) || (absRow == 1 and absCol == 2))
	{
		setRow(row);
		setColumn(column);
	}
	else
	{
		throw std::logic_error("Invalid Knight Position!\n");
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
