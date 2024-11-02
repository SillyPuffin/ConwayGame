#pragma once
#include <vector>


class Grid {
public:
	Grid(int width, int height, int cellsize) :
		rows(height / cellsize),
		columns(width / cellsize),
		cellsize(cellsize),
		cells(rows, std::vector<int>(columns,0))
	{};

	void Draw();
	void setValue(int row, int column, int value);

private:
	int rows;
	int columns;
	int cellsize;
	std::vector<std::vector<int>> cells;

};