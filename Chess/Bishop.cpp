#include "Bishop.h"

Bishop::Bishop(int row, int column, bool isWhite) : Figure(row, column, isWhite)
{
}

void Bishop::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	if (abs(this->row - row) != abs(this->column - column))
	{
		throw std::logic_error("Invalid Bishop coordinates!\n");
	}
	setRow(row);
	setColumn(column);
}

Figure * Bishop::clone() const
{
	return new Bishop(*this);
}

std::string Bishop::getFigureType() const
{
	return "Bishop";
}


