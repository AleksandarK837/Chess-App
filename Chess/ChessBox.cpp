#include "ChessBox.h"

ChessBox::ChessBox(int row, int column, Color color, const Figure & currentfigure) : currentFigure(nullptr), row(row), column(column), color(color)
{
	setFigure(currentfigure);
}

ChessBox::ChessBox(int row, int column, Color color) : row(row), column(column), color(color), currentFigure(nullptr)
{
}

ChessBox::ChessBox(const ChessBox & rhs) : currentFigure(nullptr)
{
	copyFrom(rhs);
}

ChessBox & ChessBox::operator=(const ChessBox & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

ChessBox::~ChessBox()
{
	clear();
}

int ChessBox::getRow() const
{
	return row;
}

int ChessBox::getColumn() const
{
	return column;
}

Color ChessBox::colorFigure() const
{
	return color;
}

Figure * ChessBox::getFigure() const
{
	return currentFigure;
}

void ChessBox::setFigure(const Figure & figure)
{
	delete[]currentFigure;
	currentFigure = figure.clone();
}

void ChessBox::destroyFigure()
{
	delete currentFigure;
	currentFigure = nullptr;
}

bool ChessBox::isFigureOn()
{
	if (currentFigure == nullptr)
	{
		return false;
	}
	return true;
}

void ChessBox::copyFrom(const ChessBox & rhs)
{
	row = rhs.row;
	column = rhs.column;
	color = rhs.color;
	if (rhs.currentFigure != nullptr)
	{
		currentFigure = rhs.currentFigure->clone();
	}
}

void ChessBox::clear()
{
	row = column = 0;
	delete currentFigure;
	currentFigure = nullptr;
}
