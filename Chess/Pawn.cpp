#include "Pawn.h"

Pawn::Pawn(int row, int column, Color color) : Figure(row, column, color)
{
	isMoved = false;
}

void Pawn::moveTo(int row, int column)
{
	if (!isValidPosition(row, column))
	{
		throw std::logic_error("Position is not valid!\n");
	}
	if (this->color == white)
	{
		bool moveOneStepUp = (this->row + 1 == row && this->column == column);
		bool moveTwoStepsUp = (this->row + 2 == row && this->column == column);
		bool moveUpLeft = (this->row + 1 == row and this->column - 1 == column);
		bool moveUpRight = (this->row + 1 == row and this->column + 1 == column);

		if (this->isMoved)
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight)
			{
				setRow(row);
				setColumn(column);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!\n");
			}
		}
		else
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight || moveTwoStepsUp)
			{
				setRow(row);
				setColumn(column);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!\n");
			}
			this->isMoved = true;
		}
	}
	else
	{
		bool moveOneStepUp = (this->row - 1 == row && this->column == column);
		bool moveTwoStepsUp = (this->row - 2 == row && this->column == column);
		bool moveUpLeft = (this->row - 1 == row and this->column - 1 == column);
		bool moveUpRight = (this->row - 1 == row and this->column + 1 == column);

		if (this->isMoved)
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight)
			{
				setRow(row);
				setColumn(column);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!\n");
			}
		}
		else
		{
			if (moveOneStepUp || moveUpLeft || moveUpRight || moveTwoStepsUp)
			{
				setRow(row);
				setColumn(column);
			}
			else
			{
				throw std::logic_error("Invalid Pawn Position!\n");
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
