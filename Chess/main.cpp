#include <iostream>
#include "ChessGame.h"
using namespace std;

int main()
{
	ChessGame chess;
	try
	{
		chess.startGame();
		cout << "Game started\n";
	}
	catch (const std::bad_alloc &b)
	{
		cerr << "Can't place the figures\n" << b.what();
		return -1;
	}

	while (true)
	{
		int fromRow;
		char fromColumn;
		cout << "Enter (row, column) for start box destination: ";
		cin >> fromRow >> fromColumn;

		int toRow;
		char toColumn;
		cout << "Enter (row, column) for end box destination: ";
		cin >> toRow >> toColumn;

		chess.moveFigure(fromRow, fromColumn, toRow, toColumn);
	}
	
	system("pause");
	return 0;
}