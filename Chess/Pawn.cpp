#include "Pawn.h"

Pawn::Pawn(int row, int col, bool isWhite) : Figure(row, col, isWhite)
{
	isMoved = false;
}

void Pawn::moveTo(int row, int col)
{
	if (!isValidPosition(row, col))
	{
		throw std::logic_error("Position is not valid!");
	}
	if (this->isWhite)
	{
		bool moveOneStepUp = (this->row + 1 == row && this->col == col);
		bool moveTwoStepsUp = (this->row + 2 == row && this->col == col);
		bool moveUpLeft = (this->row + 1 == row and this->col - 1 == col);
		bool moveUpRight = (this->row + 1 == row and this->col + 1 == col);

		if (this->isMoved)
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight)
			{
				setRow(row);
				setCol(col);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!");
			}
		}
		else
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight || moveTwoStepsUp)
			{
				setRow(row);
				setCol(col);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!");
			}
			this->isMoved = true;
		}
	}
	else
	{
		bool moveOneStepUp = (this->row - 1 == row && this->col == col);
		bool moveTwoStepsUp = (this->row - 2 == row && this->col == col);
		bool moveUpLeft = (this->row - 1 == row and this->col - 1 == col);
		bool moveUpRight = (this->row - 1 == row and this->col + 1 == col);

		if (this->isMoved)
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight)
			{
				setRow(row);
				setCol(col);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!");
			}
		}
		else
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight || moveTwoStepsUp)
			{
				setRow(row);
				setCol(col);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!");
			}
			this->isMoved = true;
		}
	}
}

Figure * Pawn::clone() const
{
	return new Pawn(*this);
}

std::string Pawn::getFigureType() const
{
	return "Pawn";
}
