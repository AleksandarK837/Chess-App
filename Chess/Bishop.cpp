#include "Bishop.h"

Bishop::Bishop(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

void Bishop::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!");
	}

	if (abs(this->row - row) != abs(this->col - col))
	{
		throw std::logic_error("Invalid Bishop coordinates!");
	}
	setRow(row);
	setCol(col);
}

Figure * Bishop::clone() const
{
	return new Bishop(*this);
}

std::string Bishop::getFigureType() const
{
	return "Bishop";
}


