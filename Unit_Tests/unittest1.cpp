#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Chess/Bishop.h"
#include "../Chess/ChessBox.h"
#include "../Chess/Figure.h"
#include "../Chess/GlobalVariables.h"
#include "../Chess/King.h"
#include "../Chess/Knight.h"
#include "../Chess/Pawn.h"
#include "../Chess/Queen.h"
#include "../Chess/Rook.h"
#include "../Chess/ChessGame.h"
#include "../Chess/ChessBoard.h"

#include "../Chess/Bishop.cpp"
#include "../Chess/ChessBox.cpp"
#include "../Chess/Figure.cpp"
#include "../Chess/King.cpp"
#include "../Chess/Knight.cpp"
#include "../Chess/Pawn.cpp"
#include "../Chess/Queen.cpp"
#include "../Chess/Rook.cpp"
#include "../Chess/ChessGame.cpp"
#include "../Chess/ChessBoard.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unit_Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CheckMate)
		{
			ChessGame chess;
			chess.startGame();
			chess.moveFigure(2, 'e', 4, 'e');
			chess.moveFigure(7, 'e', 5, 'e');
			chess.moveFigure(1, 'f', 4, 'c');
			chess.moveFigure(8, 'f', 5, 'c');
			chess.moveFigure(1, 'd', 3, 'f');
			chess.moveFigure(7, 'a', 6, 'a');
			chess.moveFigure(3, 'f', 7, 'f');
			Assert::IsTrue(chess.gameOver());
		}
		TEST_METHOD(NonFigure)
		{
			ChessBoard board;
			board.placeFigures();
			Assert::IsNull(board.getChessBoxByCoordinates(4, 4).getFigure());
		}
		TEST_METHOD(EmptyBox)
		{
			ChessBoard board;
			board.placeFigures();
			const ChessBox &box = board.getChessBoxByCoordinates(3, 4);
			Assert::IsFalse(ChessBox(box).isFigureOn());
		}
		TEST_METHOD(Figure)
		{
			ChessBoard board;
			board.placeFigures();
			std::string knight = "Knight";
			Assert::AreEqual(board.getChessBoxByCoordinates(0, 1).getFigure()->getFigureType(), knight);
		}
		TEST_METHOD(Move)
		{
			ChessBoard board;
			board.placeFigures();

			const ChessBox &startPawnPosition = board.getChessBoxByCoordinates(1, 4);
			const ChessBox &endPawnPosition = board.getChessBoxByCoordinates(2, 4);
			board.moveFigureTo(ChessBox(startPawnPosition), ChessBox(endPawnPosition));
			
			const ChessBox &startDarkPawn = board.getChessBoxByCoordinates(6, 1);
			const ChessBox &endDarkPawn = board.getChessBoxByCoordinates(4, 1);
			board.moveFigureTo(ChessBox(startDarkPawn), ChessBox(endDarkPawn));

			const ChessBox &startBishop = board.getChessBoxByCoordinates(0, 5);
			const ChessBox &endBishop = board.getChessBoxByCoordinates(4, 1);
			board.moveFigureTo(ChessBox(startBishop), ChessBox(endBishop));
			Assert::IsNotNull(board.getChessBoxByCoordinates(4, 1).getFigure());
		}
	};
}