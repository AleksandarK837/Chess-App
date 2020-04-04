#include "Queen.h"

Queen::Queen(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

bool Queen::movedTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		cout << "Position is not valid\n";
		return false;
	}

	if (this->row == row)
	{
		setCol(col); //move Queen like Rook up/down
	}
	else if (this->col = col)
	{
		setRow(row); //move Queen like Rook aside
	}
	else if (abs(this->col - col) == abs(this->row - row)) // move Queen like Bishop
	{
		setCol(col);
		setRow(row);
	}
	else
	{
		cout << "Invalid Queen coordinates\n";
		return false;
	}
	return true;
}

Figure * Queen::clone() const
{
	return new Queen(*this);
}

std::string Queen::getFigureType() const
{
	return "Queen";
}
