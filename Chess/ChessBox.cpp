#include "ChessBox.h"

ChessBox::ChessBox(int row, int column, bool isWhite, const Figure & currentfigure) : currentFigure(nullptr), row(row), column(column), isWhite(isWhite)
{
	setFigure(currentfigure);
}

ChessBox::ChessBox(int row, int column, bool isWhite) : row(row), column(column), isWhite(isWhite), currentFigure(nullptr)
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

bool ChessBox::getIsWhite() const
{
	return isWhite;
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
	isWhite = rhs.isWhite;
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
