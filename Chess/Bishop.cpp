#include "Bishop.h"

Bishop::Bishop(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

bool Bishop::movedTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		cout << "Position is not valid\n";
		return false;
	}

	if (abs(this->row - row) != abs(this->col - col))
	{
		cout << "Invalid bishop coordinates\n";
		return false;
	}

	setRow(row);
	setCol(col);
	return true;
}

Figure * Bishop::clone() const
{
	return new Bishop(*this);
}

std::string Bishop::getFigureType() const
{
	return "Bishop";
}


