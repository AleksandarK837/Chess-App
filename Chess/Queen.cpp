#include "Queen.h"

Queen::Queen(int row, int column, bool isWhite) : Figure(row, column, isWhite)
{
}

void Queen::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	if (this->row == row)
	{
		setColumn(column); //move Queen like Rook up/down
	}
	else if (this->column = column)
	{
		setRow(row); //move Queen like Rook left/right
	}
	else if (abs(this->column - column) == abs(this->row - row)) // move Queen like Bishop
	{
		setColumn(column);
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
