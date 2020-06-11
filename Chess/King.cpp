#include "King.h"

King::King(int row, int column, bool isWhite) : Figure(row, column, isWhite)
{
}

void King::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}

	//move king up, down, left, right, bottom left, bottom right, up left, up right
	int rowCoordinates[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int colCoordinates[] = { -1, 0, 1, 1, -1, -1, 0, 1 };
	bool isMoved = false;
	for (int i = 0; i < 8; i++)
	{
		if ((this->row + rowCoordinates[i] == row) && (this->column + colCoordinates[i] == column))
		{
			setRow(row);
			setColumn(column);
			isMoved = true;
			break;
		}
	}

	if (!isMoved)
	{
		throw std::logic_error("Position is not valid!\n");
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
