#include "grid.h"
#include <raylib.h>


void Grid::Draw(IntVecList Drawlist)
{
	
	for ( auto& cell : Drawlist)
	{
		unsigned int r = (float)cell[0] / columns * 255;
		unsigned int g = (float)cell[1] / rows * 255;
		unsigned int b = (float)(r * g) / 65025 * 225;
		Color color = cell[2] ? Color{ (unsigned char)r,(unsigned char)g,(unsigned char)b,255} : Color{29,29,29,255};
		DrawRectangle((float)cell[0] * cellsize, (float)cell[1] * cellsize, (float)cellsize - 1, (float)cellsize - 1, color);
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
	//ShowActive();
}

void Grid::setValue(int column, int row, int value)
{
	if (ValidateCoords(column,row))
	{
		int oldValue = GetCellValue(column, row);
		cells[row][column] = value;
		//keeping track of actives
		if (oldValue == 0 && value == 1)
		{
			ActiveCells.insert({ column, row });
		}
		else if (oldValue == 1 && value == 0)
		{
			ActiveCells.erase({ column,row });
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
	ActiveCells = {};
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int randomValue = GetRandomValue(0, 4);
			int state = (randomValue == 4) ? 1 : 0;
			setValue(column, row, state);
		}
	}
	//ShowActive();
}

int Grid::CountLiveNeighbours(int column, int row)
{
	int liveNeighbours = 0;
	IntPairVec neighbourOffsets = {
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

IntVec Grid::GetStateToChange(int column, int row) {
	int liveNeighbours = CountLiveNeighbours(column, row);
	int cellValue = GetCellValue(column, row);
	IntVec stateChange = {};

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

IntPairVec Grid::GetNeighbourCoords(int column, int row)
{
	IntPairVec neighbourPos = {};
	IntPairVec neighbourOffsets = {
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
		neighbourPos.push_back({neighbourColumn, neighbourRow});
		//std::cout << neighbourColumn << ' ' << neighbourRow << column <<  offset.first << columns <<"\n";
	}
	return neighbourPos;
}

IntVecList Grid::GetCellsToChange() {
	IntVecList changeList = {};
	for (const auto& pair : ActiveCells)
	{
		//get x and y coords from key string
		//IntPair coords = pair;
		int column = pair.first;
		int row = pair.second;

		IntPairVec cellsToUpdate = GetNeighbourCoords(column, row);
		cellsToUpdate.push_back(pair);
		

		for (const auto& pos : cellsToUpdate)
		{
			IntVec cellAndState = GetStateToChange(pos.first, pos.second);
			if (!cellAndState.empty())
			{
				changeList.push_back(cellAndState);
			}
		}
	
	}
	return changeList;
}

set Grid::ReturnActiveCells()
{
	return ActiveCells; 
}