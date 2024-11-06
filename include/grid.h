#pragma once
#include <vector>
#include <list>
#include <string>
#include <unordered_set>
#include <functional>
#include <utility>
#include <iostream>

typedef std::pair<int, int> IntPair;
typedef std::vector<int> IntVec;
typedef std::list<IntPair> IntPairList;
typedef std::vector<IntPair> IntPairVec;
typedef std::list<std::vector<int>> IntVecList;

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
	}
};

typedef std::unordered_set < std::pair<int, int>, pair_hash > set;

class Grid {
public:
	Grid(int width, int height, int cellsize) :
		rows(height / cellsize),
		columns(width / cellsize),
		cellsize(cellsize),
		cells(rows, std::vector<int>(columns, 0)),
		tempcells(rows, std::vector<int>(columns, 0)),
		ActiveCells({})
	{};

	void Draw(set Drawlist);

	void setValue(int column , int row, int value);
	void fillRandom();
	void Clear();
	//void ShowActive() { std::cout << ActiveCells.size() << "\n"; }

	bool ValidateCoords(int column, int row);
	int GetCellValue(int column, int row);
	int CountLiveNeighbours(int column, int row);

	int GetCellSize() { return cellsize; }
	int GetRows() { return rows; }
	int GetColumns() { return columns; }

	std::unordered_set < std::pair<int, int>, pair_hash > ReturnActiveCells();
	IntPairVec GetNeighbourCoords(int column, int row);
	void GetStateToChange(int column, int row);
	void GetCellsToChange();

private:
	int rows;
	int columns;
	int cellsize;
	std::vector<IntVec> cells;
	std::vector<IntVec> tempcells;
	std::unordered_set < std::pair<int,int>, pair_hash > ActiveCells;
};