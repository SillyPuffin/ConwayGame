#include "grid.h"
#include <raylib.h>

void Grid::Draw()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			Color color = cells[row][column] ? Color{ 0,255,0,255 } : Color{ 55,55,55,255 };
			DrawRectangle((float)row * cellsize, (float)column * cellsize, (float)cellsize-1, (float)cellsize-1, color);

		}
	}
}

void Grid::setValue(int row, int column, int value)
{
	if (row >= 0 && row < rows && column >= 0 && column < columns)
	{
		cells[row][column] = value;
	}
}