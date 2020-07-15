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

bool ChessBoard::isInChess(Color colorKing) const
{
	const ChessBox &kingSBox = getKingsBox(colorKing);

	// check rook and queen
	for (int i = 0; i < SIZE_ROOK_CHANGER; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getColumn();
		row = row + rowRookChange[i];
		column = column + columnRookChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != colorKing)
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
			row = row + rowRookChange[i];
			column = column + columnRookChange[i];
		}
	}
	//check knight 
	for (int i = 0; i < SIZE_KNIGHT_CHANGER; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getColumn();
		row = row + rowKnightChange[i];
		column = column + columnKnightChange[i];

		if (areValidChessBoxCoordinates(row, column))
		{
			if ((chessBoard[row][column]->isFigureOn()) && (chessBoard[row][column]->getFigure()->colorFigure() != colorKing))
			{
				if (chessBoard[row][column]->getFigure()->getFigureType() == "Knight")
				{
					return true;
				}
			}
		}
	}
	//check Bishop and Queen
	for (int i = 0; i < SIZE_BISHOP_CHANGER; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getColumn();
		row = row + rowBishopChange[i];
		column = column + columnBishopChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != colorKing)
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
	int pawnRowChange = 1; //if the king si white - the pawn is one row up

	if (colorKing == dark)
	{
		pawnRowChange = -1; // if the king is black - the pawn is one row down
	}

	for (int i = 0; i < SIZE_PAWN_CHANGER; i++)
	{
		int row = kingSBox.getRow();
		int column = kingSBox.getColumn();
		row = row + pawnRowChange;
		column = column + pawnColumnChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			const Figure &figure = *chessBoard[row][column]->getFigure();
			if ((chessBoard[row][column]->isFigureOn()) && ((figure.colorFigure() != colorKing) && (figure.getFigureType() == "Pawn")))
			{
				return true;
			}
		}

		//check King
		for (int i = 0; i < SIZE_KING_CHANGER; i++)
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
					if ((figure.colorFigure() != colorKing) && (figure.getFigureType() == "King"))
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

const ChessBox & ChessBoard::getKingsBox(Color colorKing) const
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			const Figure &figure = *chessBoard[i][j]->getFigure();
			if ((chessBoard[i][j]->isFigureOn()) && (figure.getFigureType() == "King" && (figure.colorFigure() == colorKing)))
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
	Color colorBox = white;
	for (int i = 0; i < COLUMN_SIZE; i++)
	{
		chessBoard[1][i] = new ChessBox(1, i, colorBox, Pawn(1, i, white)); // place white pawns
		chessBoard[6][i] = new ChessBox(6, i, colorBox == white? dark : white, Pawn(6, i, dark)); //place black pawns
		colorBox = colorBox == white ? dark : white;
	}

	colorBox = dark;
	for (int i = 0; i < COLUMN_SIZE; i++)
	{
		if (i == 0 || i == 7)
		{
			chessBoard[0][i] = new ChessBox(0, i, colorBox, Rook(0, i, white)); //place white Rook
			chessBoard[7][i] = new ChessBox(7, i, colorBox == white ? dark : white, Rook(7, i, dark)); //place black Rook
		}
		else if (i == 1 || i == 6)
		{
			chessBoard[0][i] = new ChessBox(0, i, colorBox, Knight(0, i, white)); //place white Knight
			chessBoard[7][i] = new ChessBox(7, i, colorBox == white ? dark : white, Knight(7, i, dark)); //place black Knight
		}
		else if (i == 2 || i == 5)
		{
			chessBoard[0][i] = new ChessBox(0, i, colorBox, Bishop(0, i, white)); //place white Bishop
			chessBoard[7][i] = new ChessBox(7, i, colorBox == white ? dark : white, Bishop(7, i, dark)); //place black Bishop
		}
		else if (i == 3)
		{
			chessBoard[0][i] = new ChessBox(0, i, colorBox, Queen(0, i, white)); //place white Queen
			chessBoard[7][i] = new ChessBox(7, i, colorBox == white ? dark : white, Queen(7, i, dark)); //place black Queen
		}
		else
		{
			chessBoard[0][i] = new ChessBox(0, i, colorBox, King(0, i, white)); //place white King
			chessBoard[7][i] = new ChessBox(7, i, colorBox == white ? dark : white, King(7, i, dark)); //place black King
		}
		colorBox = colorBox == white ? dark : white;
	}
	colorBox = white;
	for (int i = 2; i < ROW_SIZE - 2; i++)
	{
		for (int j = 0; j < COLUMN_SIZE; j++)
		{
			chessBoard[i][j] = new ChessBox(i, j, colorBox); // place empty boxes
			colorBox = colorBox == white ? dark : white;
		}
	}
}

bool ChessBoard::isCheckmate(Color color)
{
	if (!isInChess(color))
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
				if (currentFigure->colorFigure() == color)
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
		return protectKingWithBishop(row, column);
	}
	else if (figure.getFigureType() == "Rook")
	{
		return protectKingWithBishop(row, column);
	}
	else if (figure.getFigureType() == "Queen")
	{ // move Queen like rook or bishop
		return protectKingWithBishop(row, column) ||
			   protectKingWithRook(row, column);
	}
	else
	{
		return canMoveKing(row, column);
	}
}

bool ChessBoard::protectKingWithKnight(int knightRowPosition, int knightColumnPosition)
{
	ChessBox &startBox = *chessBoard[knightRowPosition][knightColumnPosition];
	Figure *knightMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < SIZE_KNIGHT_CHANGER; i++)
	{
		int row = knightRowPosition;
		int column = knightColumnPosition;
		row = row + rowKnightChange[i];
		column = column + columnKnightChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != knightMovements->colorFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					knightMovements->setRow(row);
					knightMovements->setColumn(column);
					endBox.setFigure(*knightMovements);
					if (!isInChess(knightMovements->colorFigure()))
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
				if (!isInChess(knightMovements->colorFigure()))
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
	if (!pawnMovements->colorFigure())
	{
		pawnRowChange = -1;
	}

	if (!chessBoard[row + pawnRowChange][column]->isFigureOn())
	{
		ChessBox &endBox = *chessBoard[row + pawnRowChange][column];
		pawnMovements->setRow(row + pawnRowChange);
		pawnMovements->setColumn(column);
		endBox.setFigure(*pawnMovements);
		if (!isInChess(pawnMovements->colorFigure()))
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
	for (int i = 0; i < SIZE_PAWN_CHANGER; i++)
	{
		if (areValidChessBoxCoordinates(row + pawnRowChange, column + pawnColumnChange[i]))
		{
			if (chessBoard[row + pawnRowChange][column + pawnColumnChange[i]]->isFigureOn())
			{
				if (chessBoard[row + pawnRowChange][column + pawnColumnChange[i]]->getFigure()->colorFigure() != pawnMovements->colorFigure())
				{
					ChessBox &endBox = *chessBoard[row + pawnRowChange][column + pawnColumnChange[i]];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					pawnMovements->setRow(row + pawnRowChange);
					pawnMovements->setColumn(column + pawnColumnChange[i]);
					endBox.setFigure(*pawnMovements);
					if (!isInChess(pawnMovements->colorFigure()))
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
	ChessBox &startBox = *chessBoard[kingRowPosition][kingColumnPosition];
	Figure *kingMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < SIZE_KING_CHANGER; i++)
	{
		int row = kingRowPosition;
		int column = kingColumnPosition;
		row = row + rowKingChange[i];
		column = column + columnKingChange[i];
		if (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != kingMovements->colorFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					kingMovements->setRow(row);
					kingMovements->setColumn(column);
					endBox.setFigure(*kingMovements);
					if (!isInChess(kingMovements->colorFigure()))
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
				if (!isInChess(kingMovements->colorFigure()))
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

bool ChessBoard::protectKingWithBishop(int bishopRowPosition, int bishopColumnPosition)
{
	ChessBox &startBox = *chessBoard[bishopRowPosition][bishopColumnPosition];
	Figure *bishopMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < SIZE_BISHOP_CHANGER; i++)
	{
		int row = bishopRowPosition;
		int column = bishopColumnPosition;
		row = row + rowBishopChange[i];
		column = column + columnBishopChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != bishopMovements->colorFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					bishopMovements->setRow(row);
					bishopMovements->setColumn(column);
					endBox.setFigure(*bishopMovements);
					if (!isInChess(bishopMovements->colorFigure()))
					{
						bishopMovements->setRow(bishopRowPosition);
						bishopMovements->setColumn(bishopColumnPosition);
						startBox.setFigure(*bishopMovements);
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						delete bishopMovements;
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
				bishopMovements->setRow(row);
				bishopMovements->setColumn(column);
				endBox.setFigure(*bishopMovements);
				if (!isInChess(bishopMovements->colorFigure()))
				{
					bishopMovements->setRow(bishopRowPosition);
					bishopMovements->setColumn(bishopColumnPosition);
					startBox.setFigure(*bishopMovements);
					endBox.destroyFigure();
					delete bishopMovements;
					return true;
				}
				else
				{
					endBox.destroyFigure();
				}
			}
			row = row + rowBishopChange[i];
			column = column + columnBishopChange[i];
		}
	}
	bishopMovements->setRow(bishopRowPosition);
	bishopMovements->setColumn(bishopColumnPosition);
	startBox.setFigure(*bishopMovements);
	delete bishopMovements;
	return false;
}

bool ChessBoard::protectKingWithRook(int rookRowPosition, int figureColumnPosition)
{
	ChessBox &startBox = *chessBoard[rookRowPosition][figureColumnPosition];
	Figure *rookMovements = startBox.getFigure()->clone();
	startBox.destroyFigure();

	for (int i = 0; i < SIZE_ROOK_CHANGER; i++)
	{
		int row = rookRowPosition;
		int column = figureColumnPosition;
		row = row + rowRookChange[i];
		column = column + columnRookChange[i];
		while (areValidChessBoxCoordinates(row, column))
		{
			if (chessBoard[row][column]->isFigureOn())
			{
				if (chessBoard[row][column]->getFigure()->colorFigure() != rookMovements->colorFigure())
				{
					ChessBox &endBox = *chessBoard[row][column];
					Figure *endBoxFigure = endBox.getFigure()->clone();
					rookMovements->setRow(row);
					rookMovements->setColumn(column);
					endBox.setFigure(*rookMovements);
					if (!isInChess(rookMovements->colorFigure()))
					{
						rookMovements->setRow(rookRowPosition);
						rookMovements->setColumn(figureColumnPosition);
						startBox.setFigure(*rookMovements);
						endBox.setFigure(*endBoxFigure);
						delete endBoxFigure;
						delete rookMovements;
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
				rookMovements->setRow(row);
				rookMovements->setColumn(column);
				endBox.setFigure(*rookMovements);
				if (!isInChess(rookMovements->colorFigure()))
				{
					rookMovements->setRow(rookRowPosition);
					rookMovements->setColumn(figureColumnPosition);
					startBox.setFigure(*rookMovements);
					endBox.destroyFigure();
					delete rookMovements;
					return true;
				}
				else
				{
					endBox.destroyFigure();
				}
			}
			row = row + rowRookChange[i];
			column = column + columnRookChange[i];
		}
	}
	rookMovements->setRow(rookRowPosition);
	rookMovements->setColumn(figureColumnPosition);
	startBox.setFigure(*rookMovements);
	delete rookMovements;
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
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getColumn(), rhs.chessBoard[i][j]->colorFigure());
			}
			else
			{
				chessBoard[i][j] = new ChessBox(rhs.chessBoard[i][j]->getRow(), rhs.chessBoard[i][j]->getColumn(), rhs.chessBoard[i][j]->colorFigure(),
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
		if (chessBoxEnd.getFigure()->colorFigure() == knight.colorFigure())
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
				if (chessBoxEnd.getFigure()->colorFigure() != pawn.colorFigure())
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

	if (pawn.colorFigure() == white && pawn.getColumn() == COLUMN_SIZE - 1)
	{ // reborn Queen with white pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getColumn(), white));
	}
	else if (pawn.colorFigure() == dark && pawn.getColumn() == 0)
	{ // reborn Queen with black pawn
		chessBoxEnd.setFigure(Queen(chessBoxEnd.getRow(), chessBoxEnd.getColumn(), dark));
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
			if (chessBoxStart.getFigure()->colorFigure() == chessBoxEnd.getFigure()->colorFigure())
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

	if (isInChess(figure.colorFigure()))
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

	if (isInChess(figure.colorFigure()))
	{ //back to last position
		figure.setRow(chessBoxStart.getRow());
		figure.setColumn(chessBoxStart.getColumn());

		chessBoxStart.setFigure(figure);
		chessBoxEnd.destroyFigure();
		throw std::logic_error("You are in chess! Protect your king! Move again!\n");
	}
}
