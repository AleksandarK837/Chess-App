#include "Rook.h"

Rook::Rook(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

bool Rook::movedTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		cout << "Position is not valid\n";
		return false;
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
		cout << "Invalid rook position\n";
		return false;
	}
	return true;
}

Figure * Rook::clone() const
{
	return new Rook(*this);
}

std::string Rook::getFigureType() const
{
	return "Rook";
}
