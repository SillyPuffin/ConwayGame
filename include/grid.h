#pragma once
#include <vector>
#include <iostream>

class Grid {
public:
	Grid(int width, int height, int cellsize) :
		rows(height / cellsize),
		columns(width / cellsize),
		cellsize(cellsize),
		cells(rows, std::vector<int>(columns,0))
	{};

	void Draw();
	bool ValidateCoords(int column, int row);
	void setValue(int column , int row, int value);
	int GetCellValue(int column, int row);
	void fillRandom();

	void Clear() { cells.assign(rows, std::vector<int>(columns, 0)); }
	int GetRows() { return rows;}
	int GetColumns() { return columns; }

private:
	int rows;
	int columns;
	int cellsize;
	std::vector<std::vector<int>> cells;

};