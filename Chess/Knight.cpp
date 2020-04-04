#include "Knight.h"

Knight::Knight(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

bool Knight::movedTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		cout << "Position is not valid\n";
		return false;
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
		cout << "Invalid Knight Position\n";
		return false;
	}
	return true;
}

Figure * Knight::clone() const
{
	return new Knight(*this);
}

std::string Knight::getFigureType() const
{
	return "Knight";
}
