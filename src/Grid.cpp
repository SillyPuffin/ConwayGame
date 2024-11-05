#include "grid.h"
#include <raylib.h>
#include <format>



void Grid::Draw(std::list<std::vector<int>> Drawlist)
{
	Color color = Color{ 0,255,0,255 };
	for (const auto& cell : Drawlist)
	{
		
		DrawRectangle((float)cell[0] * cellsize, (float)cell[1] * cellsize, (float)cellsize-1, (float)cellsize-1, color);
	}
}


bool Grid::ValidateCoords(int column, int row) {
	if (row >= 0 && row < rows && column >= 0 && column < columns) {
		return true;
	}
	return false;
}

void Grid::Clear()
{
	ActiveCells = {};
	cells.assign(rows, std::vector<int>(columns, 0));
	ShowActive();
}

void Grid::setValue(int column, int row, int value)
{
	if (ValidateCoords(column,row))
	{
		cells[row][column] = value;
		//keeping track of actives
		std::string coords = std::format("({},{})", column, row);
		if (value == 1)
		{
			ActiveCells[coords] = std::pair<int, int>{ column,row };
		}
		else if (value == 0)
		{
			ActiveCells.erase(coords);
		}
		
	}
}

int Grid::GetCellValue(int column, int row) {
	if (ValidateCoords(column, row)) {
		return cells[row][column];
	}
	return 0;
}

void Grid::fillRandom() {
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int randomValue = GetRandomValue(0, 4);
			int state = (randomValue == 4) ? 1 : 0;
			setValue(column, row, state);
		}
	}
	ShowActive();
}

int Grid::CountLiveNeighbours(int column, int row)
{
	int liveNeighbours = 0;
	std::vector<std::pair<int, int>> neighbourOffsets = {
		{0,-1}, //up
		{0,1}, //down
		{-1,0}, //left
		{1,0},  //right
		{-1,-1},//diagonal up left
		{1,-1}, //diagonal up right
		{-1,1}, //diagonal down left
		{1,1}  //diagonal down right
	};
	for (const auto& offset : neighbourOffsets) {
		int neighbourRow = (row + offset.second + rows) % rows;
		int neighbourColumn = (column + offset.first + columns) % columns;
		liveNeighbours += GetCellValue(neighbourColumn, neighbourRow);
	}

	return liveNeighbours;
}

std::vector<int> Grid::GetStateToChange(int column, int row) {
	int liveNeighbours = CountLiveNeighbours(column, row);
	int cellValue = GetCellValue(column, row);
	std::vector<int> stateChange = {};

	if (cellValue == 1)
	{
		if (liveNeighbours > 3 || liveNeighbours < 2)
		{
			stateChange = { column, row, 0 };
		}
		
	}
	else
	{
		if (liveNeighbours == 3)
		{
			stateChange = { column, row, 1 };
		}
	}
	return stateChange;
}

std::vector<std::pair<int, int>> Grid::GetNeighbourCoords(int column, int row)
{
	std::vector<std::pair<int, int>> neighbourPos = {};
	std::vector<std::pair<int, int>> neighbourOffsets = {
		{0,-1}, //up
		{0,1}, //down
		{-1,0}, //left
		{1,0},  //right
		{-1,-1},//diagonal up left
		{1,-1}, //diagonal up right
		{-1,1}, //diagonal down left
		{1,1}  //diagonal down right
	};

	for (const auto& offset : neighbourOffsets) {
		int neighbourRow = (row + offset.second + rows) % rows;
		int neighbourColumn = (column + offset.first + column) % columns;
		neighbourPos.push_back(std::pair<int, int>{neighbourColumn, neighbourRow});
	}
	return neighbourPos;
}

std::list<std::vector<int>> Grid::GetCellsToChange() {
	std::list<std::vector<int>> changeList = {};
	for (const auto& pair : ActiveCells)
	{
		//get x and y coords from key string
		std::pair<int, int>coords = pair.second;
		int column = coords.first;
		int row = coords.second;

		std::vector<std::pair<int, int>>cellsToUpdate = GetNeighbourCoords(column, row);
		cellsToUpdate.push_back(coords);

		for (const auto& pos : cellsToUpdate)
		{
			std::vector<int>cellAndState = GetStateToChange(pos.first, pos.second);
			if (!cellAndState.empty())
			{
				changeList.push_back(cellAndState);
			}
		}
	}
	return changeList;
}

std::list<std::vector<int>> Grid::ReturnActiveList()
{
	std::list<std::vector<int>> ListedActive;
	for (const auto& pair : ActiveCells)
	{
		ListedActive.push_back(std::vector<int>{pair.second.first, pair.second.second, 1});
	}
	return ListedActive;
}