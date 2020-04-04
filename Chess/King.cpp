#include "King.h"

King::King(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
}

bool King::movedTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		cout << "Position is not valid\n";
		return false;
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
		cout << "Position is not valid\n";
		return false;
	}
	return true;
}

Figure * King::clone() const
{
	return new King(*this);
}

std::string King::getFigureType() const
{
	return "King";
}
