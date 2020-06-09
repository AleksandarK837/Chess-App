#include "Figure.h"

Figure::Figure(int row, int col, bool isWhite) : isWhite(isWhite)
{
	setRow(row);
	setCol(col);
	inPlay = true;
}

void Figure::setRow(int row)
{
	if (row > ROW_SIZE - 1 || row < 0)
	{
		throw std::logic_error("Invalid row corrdinate!\n");
	}
	this->row = row;
}

void Figure::setCol(int col)
{
	if (col > COL_SIZE - 1 and col < 0)
	{
		throw std::logic_error("Invalid column corrdinate!\n");
	}
	this->col = col;
}

int Figure::getRow() const
{
	return row;
}

int Figure::getCol() const
{
	return col;
}

bool Figure::getIsWhite() const
{
	return isWhite;
}

bool Figure::isValidPosition(int row, int col) const
{
	if (this->row == row and this->col == col)
	{
		return false;
	}
	return true;
}

void Figure::destroyFigure()
{
	row = 0;
	col = 0;
	inPlay = false;
}
