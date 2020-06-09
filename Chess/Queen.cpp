#include "Queen.h"

Queen::Queen(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

void Queen::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	if (this->row == row)
	{
		setCol(col); //move Queen like Rook up/down
	}
	else if (this->col = col)
	{
		setRow(row); //move Queen like Rook left/right
	}
	else if (abs(this->col - col) == abs(this->row - row)) // move Queen like Bishop
	{
		setCol(col);
		setRow(row);
	}
	else
	{
		throw std::logic_error("Invalid Queen coordinates!\n");
	}
}

Figure * Queen::clone() const
{
	return new Queen(*this);
}

std::string Queen::getFigureType() const
{
	return "Queen";
}
