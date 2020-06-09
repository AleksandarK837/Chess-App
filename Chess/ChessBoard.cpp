#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	**chessBoard = nullptr;
}

ChessBoard::ChessBoard(const ChessBoard & rhs)
{
	copyFrom(rhs);
}

ChessBoard & ChessBoard::operator=(const ChessBoard & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

ChessBoard::~ChessBoard()
{
	clear();
}


bool ChessBoard::moveFigureTo(ChessBox & start, ChessBox & end)
{
	Figure &currentFigure = *start.getFigure();
	try
	{
		if (currentFigure.getFigureType() == "Pawn")
		{
			movePawnTo(currentFigure, end.getRow(), end.getCol());
		}
		else if (currentFigure.getFigureType() == "Knight")
		{
			moveKnightTo(currentFigure, end.getRow(), end.getCol());
		}
		else
		{ //move king and queen like rook or bishop
			moveOtherFigures(currentFigure, end.getRow(), end.getCol());
		}
	}
	catch (const std::logic_error &e)
	{
		cerr << e.what();
		return false;
	}
	return true;
}

bool ChessBoard::isInChess(bool isWhiteKing) const
{
	const ChessBox &kingSBox = getKingsBox(isWhiteKing);

	// check rook and queen
	int rowChange[] = { -1,1,0,0 };
	int columnChange[] = { 0, 0, 1, -1 };
	for (int i = 0; i < 4; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getCol();
		row = row + rowChange[i];
		column = column + columnChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->getIsWhite() != isWhiteKing)
				{
					const Figure &figure = *chessBoard[row][column]->getFigure();
					if (figure.getFigureType() == "Rook" || figure.getFigureType() == "Queen")
					{
						return true;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			row = row + rowChange[i];
			column = column + columnChange[i];
		}
	}
	//check knight 
	int rowKnightChange[] = { 1, 1, -1, -1, 2, -2, 2, -2 };
	int columnKnightChange[] = { 2, -2, 2, -2, 1, 1, -1, -1 };
	for (int i = 0; i < 8; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getCol();
		row = row + rowKnightChange[i];
		column = column + columnKnightChange[i];

		if (areValidChessBoxCoordinates(row, column))
		{
			if ((chessBoard[row][column]->isFigureOn()) && (chessBoard[row][column]->getFigure()->getIsWhite() != isWhiteKing))
			{
				if (chessBoard[row][column]->getFigure()->getFigureType() == "Knight")
				{
					return true;
				}
			}
		}
	}
	//check Bishop and Queen
	int rowBishopChange[] = { 1, 1, -1, -1 };
	int columnBishopChange[] = { -1, 1, -1, 1 };
	for (int i = 0; i < 4; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getCol();
		row = row + rowBishopChange[i];
		column = column + columnBishopChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->getIsWhite() != isWhiteKing)
				{
					const Figure &figure = *chessBoard[row][column]->getFigure();
					if (figure.getFigureType() == "Bishop" || figure.getFigureType() == "Queen")
					{
						return true;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			row = row + rowBishopChange[i];
			column = column + columnBishopChange[i];
		}
	}

	//check Pawn
	int pawnColumnChange[] = { -1, 1 }; // pawn must be left or right king's position
	int pawnRowChange = 1; //if the king si white - the pawn is one row up

	if (!isWhiteKing)
	{
		pawnRowChange = -1; // if the king is black - the pawn is one row down
	}

	for (int i = 0; i < 2; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getCol();
		row = row + pawnRowChange;
		column = column + pawnColumnChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			const Figure &figure = *chessBoard[row][column]->getFigure();
			if ((chessBoard[row][column]->isFigureOn()) && ((figure.getIsWhite() != isWhiteKing) && (figure.getFigureType() == "Pawn")))
			{
				return true;
			}
		}

		//check King
		int rowKingChange[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
		int columnKingChange[] = { 1, 0, -1, 1, -1, -1, 0, 1 };
		for (int i = 0; i < 8; i++)
		{
			int row = kingSBox.getRow();
			int column = kingSBox.getCol();
			row = row + rowKingChange[i];
			column = column + columnKingChange[i];
			if (areValidChessBoxCoordinates(row, column))
			{
				const Figure &figure = *chessBoard[row][column]->getFigure();
				if (chessBoard[row][column]->isFigureOn())
				{
					if ((figure.getIsWhite() != isWhiteKing) && (figure.getFigureType() == "King"))
					{
						return true;
					}
				}

			}
		}
		return false;
	}
}

bool ChessBoard::PathBetweenBoxesFree(const ChessBox &start, const ChessBox &end)
{
	if (freePathBetweenBoxesBishop(start, end) || freePathBetweenBoxesRook(start, end))
	{
		return true;
	}
	return false;
}

ChessBox & ChessBoard::getKingsBox(bool isWhiteKing) const
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			Figure &figure = *chessBoard[i][j]->getFigure();
			if ((chessBoard[i][j]->isFigureOn()) && (figure.getFigureType() == "King" && (figure.getIsWhite() == isWhiteKing)))
			{
				return *chessBoard[i][j];
			}
		}
	}
	throw std::logic_error("The king was not found!\n");
}

bool ChessBoard::areValidChessBoxCoordinates(int row, int col) const
{
	if (row > ROW_SIZE - 1 || row < 0 || col > COL_SIZE - 1 || col < 0)
	{
		return false;
	}
	return true;
}

bool ChessBoard::freePathBetweenBoxesRook(const ChessBox & start, const ChessBox & end)
{
	if (start.getRow() == end.getRow()) //move only by row
	{
		int startRow = start.getRow();

		if (start.getCol() < end.getCol()) //move right
		{
			for (int i = start.getCol() + 1; i < end.getCol(); i++)
			{
				if (chessBoard[startRow][i]->isFigureOn())
				{
					return false;
				}
			}
			return true;
		}
		else if (start.getCol() > end.getCol()) //move left
		{
			for (int i = end.getCol() + 1; i < start.getCol(); i++)
			{
				if (chessBoard[startRow][i]->isFigureOn())
				{
					return false;
				}

			}
			return true;
		}
	}
	else if (start.getCol() == end.getCol()) //move only by column
	{
		int startCol = start.getCol();

		if (start.getRow() < end.getRow()) //move up
		{
			for (int i = start.getRow() + 1; i < end.getRow(); i++)
			{
				if (chessBoard[i][startCol]->isFigureOn())
				{
					return false;
				}

			}
			return true;
		}
		else if (start.getRow() > end.getRow()) //move down
		{
			for (int i = end.getRow() + 1; i < start.getRow(); i++)
			{
				if (chessBoard[i][startCol]->isFigureOn())
				{
					return false;
				}

			}
			return true;
		}
	}
	return false;
}

bool ChessBoard::freePathBetweenBoxesBishop(const ChessBox & start, const ChessBox & end)
{
	bool correctBishopEndBox = (abs(start.getRow() - end.getRow())) == abs((start.getCol() - end.getCol()));
	if (((end.getRow() < start.getRow()) && (end.getCol() > start.getCol())) && correctBishopEndBox)
	{// down right
		int row = start.getRow() - 1;
		int column = start.getCol() + 1;
		while (row != end.getRow() && column != end.getCol())
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				return false;
			}
			row--;
			column++;
		}
		return true;
	}
	else if (((end.getRow() > start.getRow()) && (end.getCol() > start.getCol())) && correctBishopEndBox)
	{// up right
		int row = start.getRow() + 1;
		int column = start.getCol() + 1;
		while (row != end.getRow() && column != end.getCol())
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				return false;
			}
			row++;
			column++;
		}
		return true;
	}
	else if ((((end.getRow() < start.getRow()) && (end.getCol() < start.getCol()))) && correctBishopEndBox)
	{// down left
		int row = start.getRow() - 1;
		int column = start.getCol() - 1;
		while (row != end.getRow() && column != end.getCol())
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				return false;
			}
			row--;
			column--;
		}
		return true;
	}
	else if ((((end.getRow() > start.getRow()) && (end.getCol() < start.getCol()))) && correctBishopEndBox)
	{// up left
		int row = start.getRow() + 1;
		int column = start.getCol() - 1;

		while (row != end.getRow() && column != end.getCol())
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				return false;
			}
			row++;
			column--;
		}
		return true;
	}
	return false;
}


void ChessBoard::placeFigures()
{
	bool isWhiteBox = true;
	for (int i = 0; i < COL_SIZE; i++)
	{
		chessBoard[1][i] = new ChessBox(1, i, isWhiteBox, Pawn(1, i, true)); // place white pawns
		chessBoard[6][i] = new ChessBox(6, i, !isWhiteBox, Pawn(6, i, false)); //place black pawns
		isWhiteBox = !isWhiteBox;
	}

	isWhiteBox = false;
	for (int i = 0; i < COL_SIZE; i++)
	{
		if (i == 0 || i == 7)
		{
			chessBoard[0][i] = new ChessBox(0, i, isWhiteBox, Rook(0, i, true)); //place white Rook
			chessBoard[7][i] = new ChessBox(7, i, !isWhiteBox, Rook(7, i, false)); //place black Rook
		}
		else if (i == 1 || i == 6)
		{
			chessBoard[0][i] = new ChessBox(0, i, isWhiteBox, Knight(0, i, true)); //place white Knight
			chessBoard[7][i] = new ChessBox(7, i, !isWhiteBox, Knight(7, i, false)); //place black Knight
		}
		else if (i == 2 || i == 5)
		{
			chessBoard[0][i] = new ChessBox(0, i, isWhiteBox, Bishop(0, i, true)); //place white Bishop
			chessBoard[7][i] = new ChessBox(7, i, !isWhiteBox, Bishop(7, i, false)); //place black Bishop
		}
		else if (i == 3)
		{
			chessBoard[0][i] = new ChessBox(0, i, isWhiteBox, Queen(0, i, true)); //place white Queen
			chessBoard[7][i] = new ChessBox(7, i, !isWhiteBox, Queen(7, i, false)); //place black Queen
		}
		else
		{
			chessBoard[0][i] = new ChessBox(0, i, isWhiteBox, King(0, i, true)); //place white King
			chessBoard[7][i] = new ChessBox(7, i, !isWhiteBox, King(7, i, false)); //place black King
		}
		isWhiteBox = !isWhiteBox;
	}
	isWhiteBox = true;
	for (int i = 2; i < ROW_SIZE - 2; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			chessBoard[i][j] = new ChessBox(i, j, isWhiteBox); // place empty boxes
			isWhiteBox = !isWhiteBox;
		}
	}
}

ChessBox & ChessBoard::getChessBoxByCoordinates(int row, int column) const
{
	if (!areValidChessBoxCoordinates(row, column))
	{
		throw std::logic_error("Invalid chessbox coordinates!");
	}
	return *chessBoard[row][column];
}

void ChessBoard::copyFrom(const ChessBoard & rhs)
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (rhs.chessBoard[i][j]->getFigure() == nullptr)
			{
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getCol(), rhs.chessBoard[i][j]->getIsWhite());
			}
			else
			{
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getCol(), rhs.chessBoard[i][j]->getIsWhite(),
					*rhs.chessBoard[i][j]->getFigure());
			}
		}
	}
}

void ChessBoard::clear()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			delete chessBoard[i][j];
		}
	}
}

void ChessBoard::moveKnightTo(Figure &knight, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[knight.getRow()][knight.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];
	if (chessBoxEnd.isFigureOn())
	{
		if (chessBoxEnd.getFigure()->getIsWhite() == knight.getIsWhite())
		{
			throw std::logic_error("You cannot capture your own figure!\n");
		}
		else
		{ //destroy opponent's figure and replace it with the horse
			moveToNonEmptyBox(knight, row, col);
		}
	}
	else
	{
		moveToEmptyBox(knight, row, col);
	}
}

void ChessBoard::movePawnTo(Figure &pawn, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[pawn.getRow()][pawn.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];

	if (PathBetweenBoxesFree(chessBoxStart, chessBoxEnd))
	{
		if ((chessBoxStart.getCol() - chessBoxEnd.getCol() != 0))
		{//check if the pawn is trying to destroy a figure
			if (chessBoxEnd.isFigureOn())
			{
				if (chessBoxEnd.getFigure()->getIsWhite() != pawn.getIsWhite())
				{ //destroy opponent's figure and replace it with the pawn
					moveToNonEmptyBox(pawn, row, col);
				}
				else
				{
					throw std::logic_error("You cannot capture your own figure!\n");
				}
			}
			else
			{
				throw std::logic_error("Invalid pawn coordinates! Cannot move there without capturing opponent's figure!\n");
			}

		}
		else
		{
			if (!chessBoxEnd.isFigureOn())
			{ 
				moveToEmptyBox(pawn, row, col);
			}
			else
			{
				throw std::logic_error("Pawn cannot capture figure on this coordiantes!\n");
			}
		}
	}
	else
	{
		throw std::logic_error("The path between the boxes is not free!\n");
	}

	if (pawn.getIsWhite() && pawn.getCol() == COL_SIZE - 1)
	{ // reborn Queen with white pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getCol(), true));
	}
	else if (!pawn.getIsWhite() && pawn.getCol() == 0)
	{ // reborn Queen with black pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getCol(), false));
	}
}

void ChessBoard::moveOtherFigures(Figure & figure, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];

	if (PathBetweenBoxesFree(chessBoxStart, chessBoxEnd))
	{
		if (chessBoxEnd.isFigureOn())
		{
			if (chessBoxStart.getFigure()->getIsWhite() == chessBoxEnd.getFigure()->getIsWhite())
			{ 
				throw std::logic_error("Invalid movement! You cannot attack your figure!\n");
			}
			else
			{ //destroy opponent's figure and replace it with the current
				moveToNonEmptyBox(figure, row, col);
			}
		}
		else
		{
			moveToEmptyBox(figure, row, col);
		}
	}
	else
	{
		throw std::logic_error("The path between the boxes is not free!\n");
	}
}

void ChessBoard::moveToNonEmptyBox(Figure & figure, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];
	Figure *endBoxFigure = nullptr;

	endBoxFigure = chessBoxEnd.getFigure()->clone();
	figure.moveTo(row, col);
	chessBoxEnd.setFigure(figure);
	chessBoxStart.destroyFigure();

	if (isInChess(figure.getIsWhite()))
	{
		//back to last position
		figure.setRow(chessBoxStart.getRow());
		figure.setCol(chessBoxStart.getCol());
		chessBoxStart.setFigure(figure);
		chessBoxEnd.setFigure(*endBoxFigure); //restore desotroyed figure

		delete endBoxFigure;
		throw std::logic_error("You are in chess! Protect your king!\n");
	}
	delete endBoxFigure;
}

void ChessBoard::moveToEmptyBox(Figure & figure, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];

	figure.moveTo(row, col);
	chessBoxEnd.setFigure(figure);
	chessBoxStart.destroyFigure();

	if (isInChess(figure.getIsWhite()))
	{ //back to last position
		figure.setRow(chessBoxStart.getRow());
		figure.setCol(chessBoxStart.getCol());

		chessBoxStart.setFigure(figure);
		chessBoxEnd.destroyFigure();
		throw std::logic_error("You are in chess! Protect your king!\n");
	}
}
