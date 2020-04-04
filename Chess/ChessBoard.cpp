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


bool ChessBoard::movedFigureTo(ChessBox & start, ChessBox & end)
{
	Figure &currentFigure = *start.getFigure();
	if (currentFigure.getFigureType() == "Pawn")
	{
		if (!movedPawnTo(currentFigure, end.getRow(), end.getCol()))
		{
			return false;
		}
	}
	else if (currentFigure.getFigureType() == "Knight")
	{
		if (!movedKnightTo(currentFigure, end.getRow(), end.getCol()))
		{
			return false;
		}
	}
	else
	{
		if (!movedOtherFigures(currentFigure, end.getRow(), end.getCol())) //move king and queen like rook or bishop
		{
			return false;
		}
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
					if (chessBoard[row][column]->getFigure()->getFigureType() == "Rook" || chessBoard[row][column]->getFigure()->getFigureType() == "Queen")
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
	//check Bishop
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
					if (chessBoard[row][column]->getFigure()->getFigureType() == "Bishop" || chessBoard[row][column]->getFigure()->getFigureType() == "Queen")
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
	throw "The king was not found!";
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
}

bool ChessBoard::freePathBetweenBoxesBishop(const ChessBox & start, const ChessBox & end)
{
	if (((end.getRow() > end.getCol()) && (end.getCol() > start.getCol())) && (((end.getRow() - start.getRow()) == (end.getCol() - start.getCol()))))
	{// down right
		int row = start.getRow() + 1;
		int column = start.getCol() + 1;
		while (column < end.getCol())
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
	else if (((end.getRow() > start.getRow()) && (start.getCol() > end.getCol())) && ((end.getRow() - start.getRow()) == (start.getCol() - end.getCol())))
	{// up right

		int row = start.getRow() + 1;
		int column = start.getCol() - 1;
		while (row < end.getRow())
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
	else if ((((start.getRow() > end.getRow()) && (end.getCol() > start.getCol()))) && ((start.getRow() - end.getRow()) == (end.getCol() - start.getCol())))
	{// down left

		int row = start.getRow() - 1;
		int column = start.getCol() + 1;
		while (column < end.getCol())
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
	else if ((((start.getRow() > end.getRow()) && (start.getCol() > end.getCol()))) && ((start.getRow() - end.getRow()) == (start.getCol() - end.getCol())))
	{// up left

		int row = start.getRow() - 1;
		int column = start.getCol() - 1;

		while (column > end.getCol())
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

	return true;
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

bool ChessBoard::movedKnightTo(Figure &knight, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[knight.getRow()][knight.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];
	if (chessBoxEnd.isFigureOn())
	{
		if (chessBoxEnd.getFigure()->getIsWhite() == knight.getIsWhite())
		{ //check if there is figure with the same color at this box
			cout << "You cannot capture your own figure!\n";
			return false;
		}
		else
		{ //destroy opponent's figure and replace it with the horse
			if (!knight.movedTo(row, col))
			{
				return false;
			}
			Figure *endBoxFigure = chessBoxEnd.getFigure()->clone();
			chessBoxEnd.setFigure(knight);
			chessBoxStart.destroyFigure();

			if (isInChess(knight.getIsWhite()))
			{
				knight.movedTo(chessBoxStart.getCol(), chessBoxStart.getCol()); //back to last position
				chessBoxStart.setFigure(knight);
				chessBoxEnd.setFigure(*endBoxFigure); //restore desotroyed figure
				delete endBoxFigure;
				return false;
			}
			delete endBoxFigure;
		}
	}
	else
	{
		if (!knight.movedTo(row, col))
		{
			return false;
		}
		chessBoxEnd.setFigure(knight);
		chessBoxStart.destroyFigure();

		if (isInChess(knight.getIsWhite()))
		{ //back to last position
			knight.movedTo(chessBoxStart.getRow(), chessBoxStart.getCol());
			chessBoxStart.setFigure(knight);
			chessBoxEnd.destroyFigure();
			return false;
		}
	}
	return true;
}

bool ChessBoard::movedPawnTo(Figure & pawn, int row, int col)
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
				{ // //destroy opponent's figure and replace it with the pawn
					if (!pawn.movedTo(row, col))
					{
						return false;
					}
					Figure *endBoxFigure = chessBoxEnd.getFigure()->clone();
					chessBoxEnd.setFigure(pawn);
					chessBoxStart.destroyFigure();

					if (isInChess(pawn.getIsWhite()))
					{
						pawn.movedTo(chessBoxStart.getCol(), chessBoxStart.getCol()); //back to last position
						chessBoxStart.setFigure(pawn);
						chessBoxEnd.setFigure(*endBoxFigure); //restore desotroyed figure
						delete endBoxFigure;
						return false;
					}
					delete endBoxFigure;
				}
				else
				{
					cout << "You cannot capture your own figure!";
					return false;
				}
			}
			else
			{
				cout << "Invalid pawn coordinates! Cannot move there without capturing opponent's figure\n";
				return false;
			}

		}
		else
		{
			if (!chessBoxEnd.isFigureOn())
			{ // move pawn to the new position
				if (!pawn.movedTo(row, col))
				{
					return false;
				}
				chessBoxEnd.setFigure(pawn);
				chessBoxStart.destroyFigure();

				if (isInChess(pawn.getIsWhite()))
				{ //back to last position
					pawn.movedTo(chessBoxStart.getRow(), chessBoxStart.getCol());
					chessBoxStart.setFigure(pawn);
					chessBoxEnd.destroyFigure();
					return false;
				}
			}
			else
			{
				cout << "Pawn cannot capture figure on this coordiantes!\n";
				return false;
			}
		}
	}
	else
	{
		cout << "The path between the boxes is not free\n";
		return false;
	}
	return true;
}

bool ChessBoard::movedOtherFigures(Figure & figure, int row, int col)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getCol()];
	ChessBox &chessBoxEnd = *chessBoard[row][col];

	if (PathBetweenBoxesFree(chessBoxStart, chessBoxEnd))
	{
		if (chessBoxEnd.isFigureOn())
		{
			if (chessBoxStart.getFigure()->getIsWhite() == chessBoxEnd.getFigure()->getIsWhite())
			{ //check if there is figure with the same color at this box
				cout << "Invalid movement! You cannot attack your figure!\n";
				return false;
			}
			else
			{ //destroy opponent's figure and replace it with the current

				if (!figure.movedTo(row, col))
				{
					return false;
				}
				Figure *endBoxFigure = chessBoxEnd.getFigure()->clone();
				chessBoxEnd.setFigure(figure);
				chessBoxStart.destroyFigure();

				if (isInChess(figure.getIsWhite()))
				{
					figure.movedTo(chessBoxStart.getCol(), chessBoxStart.getCol()); //back to last position
					chessBoxStart.setFigure(figure);
					chessBoxEnd.setFigure(*endBoxFigure); //restore desotroyed figure
					delete endBoxFigure;
					return false;
				}
				delete endBoxFigure;
			}
		}
		else
		{ // if there is no figure at end position
			if (!figure.movedTo(row, col))
			{
				return false;
			}
			chessBoxEnd.setFigure(figure);
			chessBoxStart.destroyFigure();

			if (isInChess(figure.getIsWhite()))
			{ //back to last position
				figure.movedTo(chessBoxStart.getRow(), chessBoxStart.getCol());
				chessBoxStart.setFigure(figure);
				chessBoxEnd.destroyFigure();
				return false;
			}
		}
	}
	else
	{
		cout << "The path between the boxes is not free\n";
		return false;
	}
	return true;
}