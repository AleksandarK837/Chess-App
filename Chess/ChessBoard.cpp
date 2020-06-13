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

void ChessBoard::moveFigureTo(ChessBox & start, ChessBox & end)
{
	Figure &currentFigure = *start.getFigure();
	if (currentFigure.getFigureType() == "Pawn")
	{
		movePawnTo(currentFigure, end.getRow(), end.getColumn());
	}
	else if (currentFigure.getFigureType() == "Knight")
	{
		moveKnightTo(currentFigure, end.getRow(), end.getColumn());
	}
	else
	{ //move king and queen like rook or bishop
		moveOtherFigures(currentFigure, end.getRow(), end.getColumn());
	}
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
		int column = kingSBox.getColumn();
		row = row + rowChange[i];
		column = column + columnChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->isWhiteFigure() != isWhiteKing)
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
		int column = kingSBox.getColumn();
		row = row + rowKnightChange[i];
		column = column + columnKnightChange[i];

		if (areValidChessBoxCoordinates(row, column))
		{
			if ((chessBoard[row][column]->isFigureOn()) && (chessBoard[row][column]->getFigure()->isWhiteFigure() != isWhiteKing))
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
		int column = kingSBox.getColumn();
		row = row + rowBishopChange[i];
		column = column + columnBishopChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->isWhiteFigure() != isWhiteKing)
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
		int column = kingSBox.getColumn();
		row = row + pawnRowChange;
		column = column + pawnColumnChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			const Figure &figure = *chessBoard[row][column]->getFigure();
			if ((chessBoard[row][column]->isFigureOn()) && ((figure.isWhiteFigure() != isWhiteKing) && (figure.getFigureType() == "Pawn")))
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
			int column = kingSBox.getColumn();
			row = row + rowKingChange[i];
			column = column + columnKingChange[i];
			if (areValidChessBoxCoordinates(row, column))
			{
				const Figure &figure = *chessBoard[row][column]->getFigure();
				if (chessBoard[row][column]->isFigureOn())
				{
					if ((figure.isWhiteFigure() != isWhiteKing) && (figure.getFigureType() == "King"))
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

const ChessBox & ChessBoard::getKingsBox(bool isWhiteKing) const
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			const Figure &figure = *chessBoard[i][j]->getFigure();
			if ((chessBoard[i][j]->isFigureOn()) && (figure.getFigureType() == "King" && (figure.isWhiteFigure() == isWhiteKing)))
			{
				return *chessBoard[i][j];
			}
		}
	}
	throw std::logic_error("The king was not found!\n");
}

bool ChessBoard::areValidChessBoxCoordinates(int row, int column) const
{
	if (row > ROW_SIZE - 1 || row < 0 || column > COLUMN_SIZE - 1 || column < 0)
	{
		return false;
	}
	return true;
}

bool ChessBoard::freePathBetweenBoxesRook(const ChessBox & start, const ChessBox & end)
{
	if (start.getRow() == end.getRow())
	{ //move only by row
		int startRow = start.getRow();

		if (start.getColumn() < end.getColumn())
		{ //move right
			for (int i = start.getColumn() + 1; i < end.getColumn(); i++)
			{
				if (chessBoard[startRow][i]->isFigureOn())
				{
					return false;
				}
			}
			return true;
		}
		else if (start.getColumn() > end.getColumn())
		{ //move left
			for (int i = end.getColumn() + 1; i < start.getColumn(); i++)
			{
				if (chessBoard[startRow][i]->isFigureOn())
				{
					return false;
				}

			}
			return true;
		}
	}
	else if (start.getColumn() == end.getColumn())
	{ //move only by column
		int startCol = start.getColumn();

		if (start.getRow() < end.getRow())
		{ //move up
			for (int i = start.getRow() + 1; i < end.getRow(); i++)
			{
				if (chessBoard[i][startCol]->isFigureOn())
				{
					return false;
				}

			}
			return true;
		}
		else if (start.getRow() > end.getRow())
		{ //move down
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
	bool correctBishopEndBox = (abs(start.getRow() - end.getRow())) == abs((start.getColumn() - end.getColumn()));
	if (((end.getRow() < start.getRow()) && (end.getColumn() > start.getColumn())) && correctBishopEndBox)
	{// down right
		int row = start.getRow() - 1;
		int column = start.getColumn() + 1;
		while (row != end.getRow() && column != end.getColumn())
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
	else if (((end.getRow() > start.getRow()) && (end.getColumn() > start.getColumn())) && correctBishopEndBox)
	{// up right
		int row = start.getRow() + 1;
		int column = start.getColumn() + 1;
		while (row != end.getRow() && column != end.getColumn())
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
	else if ((((end.getRow() < start.getRow()) && (end.getColumn() < start.getColumn()))) && correctBishopEndBox)
	{// down left
		int row = start.getRow() - 1;
		int column = start.getColumn() - 1;
		while (row != end.getRow() && column != end.getColumn())
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
	else if ((((end.getRow() > start.getRow()) && (end.getColumn() < start.getColumn()))) && correctBishopEndBox)
	{// up left
		int row = start.getRow() + 1;
		int column = start.getColumn() - 1;

		while (row != end.getRow() && column != end.getColumn())
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
	for (int i = 0; i < COLUMN_SIZE; i++)
	{
		chessBoard[1][i] = new ChessBox(1, i, isWhiteBox, Pawn(1, i, true)); // place white pawns
		chessBoard[6][i] = new ChessBox(6, i, !isWhiteBox, Pawn(6, i, false)); //place black pawns
		isWhiteBox = !isWhiteBox;
	}

	isWhiteBox = false;
	for (int i = 0; i < COLUMN_SIZE; i++)
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
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			chessBoard[i][j] = new ChessBox(i, j, isWhiteBox); // place empty boxes
			isWhiteBox = !isWhiteBox;
		}
	}
}

bool ChessBoard::isCheckmate(bool isWhitePlayer)
{
	if (!isInChess(isWhitePlayer))
	{
		return false;
	}

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			if (chessBoard[i][j]->isFigureOn())
			{
				Figure *currentFigure = chessBoard[i][j]->getFigure();
				if (currentFigure->isWhiteFigure() == isWhitePlayer)
				{
					if (playerHasPossileMoves(*currentFigure))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool ChessBoard::playerHasPossileMoves(const Figure &figure)
{
	int rowBishopChange[] = { 1, 1, -1, -1 };
	int columnBishopChange[] = { -1, 1, -1, 1 };

	int rowRookChange[] = { -1,1,0,0 };
	int columnRookChange[] = { 0, 0, 1, -1 };

	int row = figure.getRow();
	int column = figure.getColumn();
	if (figure.getFigureType() == "Knight")
	{
		return protectKingWithKnight(row, column);
	}
	else if (figure.getFigureType() == "Pawn")
	{
		return protectKingWithPawn(row, column);
	}
	else if (figure.getFigureType() == "Bishop")
	{
		return protectKingWithOtherFigures(row, column, rowBishopChange, columnBishopChange);
	}
	else if (figure.getFigureType() == "Rook")
	{
		return protectKingWithOtherFigures(row, column, rowRookChange, columnRookChange);
	}
	else if (figure.getFigureType() == "Queen")
	{ // move Queen like rook or bishop
		return protectKingWithOtherFigures(row, column, rowBishopChange, columnBishopChange) ||
			   protectKingWithOtherFigures(row, column, rowRookChange, columnRookChange);
	}
	else
	{
		return canMoveKing(row, column);
	}
}

bool ChessBoard::protectKingWithKnight(int knightRowPosition, int knightColumnPosition)
{
	int rowKnightChange[] = { 1, 1, -1, -1, 2, -2, 2, -2 };
	int columnKnightChange[] = { 2, -2, 2, -2, 1, 1, -1, -1 };
	ChessBox &startBox = *chessBoard[knightRowPosition][knightColumnPosition];
	Figure *knightMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < 8; i++)
	{
		int row = knightRowPosition;
		int column = knightColumnPosition;
		row = row + rowKnightChange[i];
		column = column + columnKnightChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->isWhiteFigure() != knightMovements->isWhiteFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					knightMovements->setRow(row);
					knightMovements->setColumn(column);
					endBox.setFigure(*knightMovements);
					if (!isInChess(knightMovements->isWhiteFigure()))
					{
						knightMovements->setRow(knightRowPosition);
						knightMovements->setColumn(knightColumnPosition);
						startBox.setFigure(*knightMovements);
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						delete knightMovements;
						return true;
					}
					else
					{
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
					}
				}
			}
			else
			{
				ChessBox &endBox = *chessBoard[row][column];
				knightMovements->setRow(row);
				knightMovements->setColumn(column);
				endBox.setFigure(*knightMovements);
				if (!isInChess(knightMovements->isWhiteFigure()))
				{
					knightMovements->setRow(knightRowPosition);
					knightMovements->setColumn(knightColumnPosition);
					startBox.setFigure(*knightMovements);
					endBox.destroyFigure();
					delete knightMovements;
					return true;
				}
				else
				{
					endBox.destroyFigure();
				}
			}
		}
	}
	knightMovements->setRow(knightRowPosition);
	knightMovements->setColumn(knightColumnPosition);
	startBox.setFigure(*knightMovements);
	delete knightMovements;
	return false;
}

bool ChessBoard::protectKingWithPawn(int pawnRowPosition, int pawnColumnPosition)
{
	ChessBox &startBox = *chessBoard[pawnRowPosition][pawnColumnPosition];
	Figure *pawnMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();
	int row = pawnRowPosition;
	int column = pawnColumnPosition;
	int pawnRowChange = 1;
	int pawnColumnChange[] = { -1, 1 };
	if (!pawnMovements->isWhiteFigure())
	{
		pawnRowChange = -1;
	}

	if (!chessBoard[row + pawnRowChange][column]->isFigureOn())
	{
		ChessBox &endBox = *chessBoard[row + pawnRowChange][column];
		pawnMovements->setRow(row + pawnRowChange);
		pawnMovements->setColumn(column);
		endBox.setFigure(*pawnMovements);
		if (!isInChess(pawnMovements->isWhiteFigure()))
		{
			pawnMovements->setRow(pawnRowPosition);
			pawnMovements->setColumn(pawnColumnPosition);
			startBox.setFigure(*pawnMovements);
			endBox.destroyFigure();
			delete pawnMovements;
			return true;
		}
		else
		{
			endBox.destroyFigure();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (areValidChessBoxCoordinates(row + pawnRowChange, column + pawnColumnChange[i]))
		{
			if (chessBoard[row + pawnRowChange][column + pawnColumnChange[i]]->isFigureOn())
			{
				if (chessBoard[row + pawnRowChange][column + pawnColumnChange[i]]->getFigure()->isWhiteFigure() != pawnMovements->isWhiteFigure())
				{
					ChessBox &endBox = *chessBoard[row + pawnRowChange][column + pawnColumnChange[i]];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					pawnMovements->setRow(row + pawnRowChange);
					pawnMovements->setColumn(column + pawnColumnChange[i]);
					endBox.setFigure(*pawnMovements);
					if (!isInChess(pawnMovements->isWhiteFigure()))
					{
						pawnMovements->setRow(pawnRowPosition);
						pawnMovements->setColumn(pawnColumnPosition);
						startBox.setFigure(*pawnMovements);
						endBox.setFigure(*endBoxFigure);
						delete pawnMovements;
						delete endBoxFigure;
						return true;
					}
					else
					{
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
					}
				}
			}
		}
	}
	pawnMovements->setRow(pawnRowPosition);
	pawnMovements->setColumn(pawnColumnPosition);
	startBox.setFigure(*pawnMovements);
	delete pawnMovements;
	return false;
}

bool ChessBoard::canMoveKing(int kingRowPosition, int kingColumnPosition)
{
	int rowKingChange[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	int columnKingChange[] = { 1, 0, -1, 1, -1, -1, 0, 1 };
	ChessBox &startBox = *chessBoard[kingRowPosition][kingColumnPosition];
	Figure *kingMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < 8; i++)
	{
		int row = kingRowPosition;
		int column = kingColumnPosition;
		row = row + rowKingChange[i];
		column = column + columnKingChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->isWhiteFigure() != kingMovements->isWhiteFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					kingMovements->setRow(row);
					kingMovements->setColumn(column);
					endBox.setFigure(*kingMovements);
					if (!isInChess(kingMovements->isWhiteFigure()))
					{
						kingMovements->setRow(kingRowPosition);
						kingMovements->setColumn(kingColumnPosition);
						startBox.setFigure(*kingMovements);
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						delete kingMovements;
						return true;
					}
					else
					{
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
					}
				}
			}
			else
			{
				ChessBox &endBox = *chessBoard[row][column];
				kingMovements->setRow(row);
				kingMovements->setColumn(column);
				endBox.setFigure(*kingMovements);
				if (!isInChess(kingMovements->isWhiteFigure()))
				{
					kingMovements->setRow(kingRowPosition);
					kingMovements->setColumn(kingColumnPosition);
					startBox.setFigure(*kingMovements);
					endBox.destroyFigure();
					delete kingMovements;
					return true;
				}
				else
				{
					endBox.destroyFigure();
				}
			}
		}
	}
	kingMovements->setRow(kingRowPosition);
	kingMovements->setColumn(kingColumnPosition);
	startBox.setFigure(*kingMovements);
	delete kingMovements;
	return false;
}

bool ChessBoard::protectKingWithOtherFigures(int figureRowPosition, int figureColumnPosition, int rowChange[], int columnChange[])
{
	ChessBox &startBox = *chessBoard[figureRowPosition][figureColumnPosition];
	Figure *figureMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < 4; i++)
	{
		int row = figureRowPosition;
		int column = figureColumnPosition;
		row = row + rowChange[i];
		column = column + columnChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->isWhiteFigure() != figureMovements->isWhiteFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					figureMovements->setRow(row);
					figureMovements->setColumn(column);
					endBox.setFigure(*figureMovements);
					if (!isInChess(figureMovements->isWhiteFigure()))
					{
						figureMovements->setRow(figureRowPosition);
						figureMovements->setColumn(figureColumnPosition);
						startBox.setFigure(*figureMovements);
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						delete figureMovements;
						return true;
					}
					else
					{
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						break;
					}
				}
				else
				{
					break;
				}
			}
			else
			{
				ChessBox &endBox = *chessBoard[row][column];
				figureMovements->setRow(row);
				figureMovements->setColumn(column);
				endBox.setFigure(*figureMovements);
				if (!isInChess(figureMovements->isWhiteFigure()))
				{
					figureMovements->setRow(figureRowPosition);
					figureMovements->setColumn(figureColumnPosition);
					startBox.setFigure(*figureMovements);
					endBox.destroyFigure();
					delete figureMovements;
					return true;
				}
				else
				{
					endBox.destroyFigure();
				}
			}
			row = row + rowChange[i];
			column = column + columnChange[i];
		}
	}
	figureMovements->setRow(figureRowPosition);
	figureMovements->setColumn(figureColumnPosition);
	startBox.setFigure(*figureMovements);
	delete figureMovements;
	return false;
}


const ChessBox & ChessBoard::getChessBoxByCoordinates(int row, int column) const
{
	if (!areValidChessBoxCoordinates(row, column))
	{
		throw std::logic_error("Invalid chessbox coordinates!\n");
	}
	return *chessBoard[row][column];
}

void ChessBoard::copyFrom(const ChessBoard & rhs)
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			if (rhs.chessBoard[i][j]->getFigure() == nullptr)
			{
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getColumn(), rhs.chessBoard[i][j]->getIsWhite());
			}
			else
			{
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getColumn(), rhs.chessBoard[i][j]->getIsWhite(),
					*rhs.chessBoard[i][j]->getFigure());
			}
		}
	}
}

void ChessBoard::clear()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			delete chessBoard[i][j];
		}
	}
}

void ChessBoard::moveKnightTo(Figure &knight, int row, int column)
{
	ChessBox &chessBoxEnd = *chessBoard[row][column];
	if (chessBoxEnd.isFigureOn())
	{
		if (chessBoxEnd.getFigure()->isWhiteFigure() == knight.isWhiteFigure())
		{
			throw std::logic_error("You cannot capture your own figure! Move again!\n");
		}
		else
		{ //destroy opponent's figure and replace it with the horse
			destroyOponentsFigure(knight, row, column);
		}
	}
	else
	{
		moveToEmptyBox(knight, row, column);
	}
}

void ChessBoard::movePawnTo(Figure &pawn, int row, int column)
{
	ChessBox &chessBoxStart = *chessBoard[pawn.getRow()][pawn.getColumn()];
	ChessBox &chessBoxEnd = *chessBoard[row][column];

	if (PathBetweenBoxesFree(chessBoxStart, chessBoxEnd))
	{
		if ((chessBoxStart.getColumn() - chessBoxEnd.getColumn() != 0))
		{//check if the pawn is trying to destroy a figure
			if (chessBoxEnd.isFigureOn())
			{
				if (chessBoxEnd.getFigure()->isWhiteFigure() != pawn.isWhiteFigure())
				{ //destroy opponent's figure and replace it with the pawn
					destroyOponentsFigure(pawn, row, column);
				}
				else
				{
					throw std::logic_error("You cannot capture your own figure! Move again!\n");
				}
			}
			else
			{
				throw std::logic_error("Invalid pawn coordinates! Cannot move there without capturing opponent's figure! Move again!\n");
			}

		}
		else
		{
			if (!chessBoxEnd.isFigureOn())
			{
				moveToEmptyBox(pawn, row, column);
			}
			else
			{
				throw std::logic_error("Pawn cannot capture figure on this coordiantes! Move again!\n");
			}
		}
	}
	else
	{
		throw std::logic_error("The path between the boxes is not free! Move again!\n");
	}

	if (pawn.isWhiteFigure() && pawn.getColumn() == COLUMN_SIZE - 1)
	{ // reborn Queen with white pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getColumn(), true));
	}
	else if (!pawn.isWhiteFigure() && pawn.getColumn() == 0)
	{ // reborn Queen with black pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getColumn(), false));
	}
}

void ChessBoard::moveOtherFigures(Figure & figure, int row, int column)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getColumn()];
	ChessBox &chessBoxEnd = *chessBoard[row][column];

	if (PathBetweenBoxesFree(chessBoxStart, chessBoxEnd))
	{
		if (chessBoxEnd.isFigureOn())
		{
			if (chessBoxStart.getFigure()->isWhiteFigure() == chessBoxEnd.getFigure()->isWhiteFigure())
			{
				throw std::logic_error("Invalid movement! You cannot attack your figure! Move again!\n");
			}
			else
			{ //destroy opponent's figure and replace it with the current
				destroyOponentsFigure(figure, row, column);
			}
		}
		else
		{
			moveToEmptyBox(figure, row, column);
		}
	}
	else
	{
		throw std::logic_error("The path between the boxes is not free! Move again!\n");
	}
}

void ChessBoard::destroyOponentsFigure(Figure & figure, int row, int column)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getColumn()];
	ChessBox &chessBoxEnd = *chessBoard[row][column];
	Figure *endBoxFigure = chessBoxEnd.getFigure()->clone();

	figure.moveTo(row, column);
	chessBoxEnd.setFigure(figure);
	chessBoxStart.destroyFigure();

	if (isInChess(figure.isWhiteFigure()))
	{
		//back to last position
		figure.setRow(chessBoxStart.getRow());
		figure.setColumn(chessBoxStart.getColumn());
		chessBoxStart.setFigure(figure);
		chessBoxEnd.setFigure(*endBoxFigure); //restore desotroyed figure

		delete endBoxFigure;
		throw std::logic_error("You are in chess! Protect your king! Move again!\n");
	}
	delete endBoxFigure;
}

void ChessBoard::moveToEmptyBox(Figure & figure, int row, int column)
{
	ChessBox &chessBoxStart = *chessBoard[figure.getRow()][figure.getColumn()];
	ChessBox &chessBoxEnd = *chessBoard[row][column];

	figure.moveTo(row, column);
	chessBoxEnd.setFigure(figure);
	chessBoxStart.destroyFigure();

	if (isInChess(figure.isWhiteFigure()))
	{ //back to last position
		figure.setRow(chessBoxStart.getRow());
		figure.setColumn(chessBoxStart.getColumn());

		chessBoxStart.setFigure(figure);
		chessBoxEnd.destroyFigure();
		throw std::logic_error("You are in chess! Protect your king! Move again!\n");
	}
}
