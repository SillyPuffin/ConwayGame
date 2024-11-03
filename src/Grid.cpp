#include "grid.h"
#include <raylib.h>

void Grid::Draw()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			Color color = cells[row][column] ? Color{ 0,255,0,255 } : Color{ 55,55,55,255 };
			DrawRectangle((float)column * cellsize, (float)row * cellsize, (float)cellsize-1, (float)cellsize-1, color);

		}
	}
}


bool Grid::ValidateCoords(int column, int row) {
	if (row >= 0 && row < rows && column >= 0 && column < columns) {
		return true;
	}
	return false;
}

void Grid::setValue(int column, int row, int value)
{
	if (ValidateCoords(column,row))
	{
		cells[row][column] = value;
	}
}

int Grid::GetCellValue(int column, int row) {
	if (ValidateCoords(column, row)) {
		return cells[row][column];
	}
}

void Grid::fillRandom() {
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int randomValue = GetRandomValue(0, 4);
			cells[row][column] = (randomValue == 4) ? 1 : 0;
		}
	}
}