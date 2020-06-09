#include "Rook.h"

Rook::Rook(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

void Rook::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!");
	}

	// we move rook only up/down or only aside
	if (this->row == row)
	{
		setCol(col);
	}
	else if (this->col == col)
	{
		setRow(row);
	}
	else
	{
		throw std::logic_error("Invalid Rook position!");
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
