#include "Rook.h"

Rook::Rook(int row, int column, bool isWhite) : Figure(row, column, isWhite)
{
}

void Rook::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	// we move rook only up/down or only aside
	if (this->row == row)
	{
		setColumn(column);
	}
	else if (this->column == column)
	{
		setRow(row);
	}
	else
	{
		throw std::logic_error("Invalid Rook position!\n");
	}
}

Figure * Rook::clone() const
{
	return new Rook(*this);
}

std::string Rook::getFigureType() const
{
	return "Rook";
}
