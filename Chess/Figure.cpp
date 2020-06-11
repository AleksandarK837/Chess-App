#include "Figure.h"

Figure::Figure(int row, int column, bool isWhite) : isWhite(isWhite)
{
	setRow(row);
	setColumn(column);
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

void Figure::setColumn(int column)
{
	if (column > COLUMN_SIZE - 1 and column < 0)
	{
		throw std::logic_error("Invalid column corrdinate!\n");
	}
	this->column = column;
}

int Figure::getRow() const
{
	return row;
}

int Figure::getColumn() const
{
	return column;
}

bool Figure::isWhiteFigure() const
{
	return isWhite;
}

bool Figure::isValidPosition(int row, int column) const
{
	if (this->row == row and this->column == column)
	{
		return false;
	}
	return true;
}

void Figure::destroyFigure()
{
	row = 0;
	column = 0;
	inPlay = false;
}
