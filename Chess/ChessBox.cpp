#include "ChessBox.h"

ChessBox::ChessBox(int row, int col, bool isWhite, const Figure & currentfigure) : currentFigure(nullptr), row(row), col(col), isWhite(isWhite)
{
	setFigure(currentfigure);
}

ChessBox::ChessBox(int row, int col, bool isWhite) : row(row), col(col), isWhite(isWhite), currentFigure(nullptr)
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

int ChessBox::getCol() const
{
	return col;
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
	col = rhs.col;
	isWhite = rhs.isWhite;
	currentFigure = rhs.currentFigure->clone();
}

void ChessBox::clear()
{
	row = col = 0;
	delete currentFigure;
	currentFigure = nullptr;
}
