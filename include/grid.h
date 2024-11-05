#pragma once
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>

class Grid {
public:
	Grid(int width, int height, int cellsize) :
		rows(height / cellsize),
		columns(width / cellsize),
		cellsize(cellsize),
		cells(rows, std::vector<int>(columns,0))
	{};

	void Draw(std::list<std::vector<int>>Drawlist);

	void setValue(int column , int row, int value);
	void fillRandom();
	void Clear();
	void ShowActive() { std::cout << ActiveCells.size() << "\n"; }

	bool ValidateCoords(int column, int row);

	int GetCellValue(int column, int row);
	int CountLiveNeighbours(int column, int row);

	int GetCellSize() { return cellsize; }
	int GetRows() { return rows; }
	int GetColumns() { return columns; }

	std::list<std::vector<int>> ReturnActiveList();
	std::vector<std::pair<int, int>> GetNeighbourCoords(int column, int row);
	std::vector<int> GetStateToChange(int column, int row);
	std::list<std::vector<int>> GetCellsToChange();

private:
	int rows;
	int columns;
	int cellsize;
	std::vector<std::vector<int>> cells;
	std::unordered_map<std::string, std::pair<int,int>> ActiveCells;
};