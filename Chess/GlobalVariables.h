#pragma once
namespace GlobalVaribles {
	const int ROW_SIZE = 8;
	const int COLUMN_SIZE = 8;

	const int rowRookChange[] = { -1, 1, 0, 0 };
	const int columnRookChange[] = { 0, 0, 1, -1 };

	const int rowKnightChange[] = { 1, 1, -1, -1, 2, -2, 2, -2 };
	const int columnKnightChange[] = { 2, -2, 2, -2, 1, 1, -1, -1 };

	const int rowBishopChange[] = { 1, 1, -1, -1 };
	const int columnBishopChange[] = { -1, 1, -1, 1 };

	const int pawnColumnChange[] = { -1, 1 };

	const int rowKingChange[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
	const int columnKingChange[] = { 1, 0, -1, 1, -1, -1, 0, 1 };
};