#include "King.h"

King::King(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

void King::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!");
	}

	//move king up, down, left, right, bottom left, bottom right, up left, up right
	int rowCoordinates[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int colCoordinates[] = { -1, 0, 1, 1, -1, -1, 0, 1 };
	bool isMoved = false;
	for (int i = 0; i < 8; i++)
	{
		if ((this->row + rowCoordinates[i] == row) && (this->col + colCoordinates[i] == col))
		{
			setRow(row);
			setCol(col);
			isMoved = true;
			break;
		}
	}

	if (!isMoved)
	{
		throw std::logic_error("Position is not valid!");
	}
}

Figure * King::clone() const
{
	return new King(*this);
}

std::string King::getFigureType() const
{
	return "King";
}
