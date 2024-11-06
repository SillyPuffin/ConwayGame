#include "grid.h"
#include <raylib.h>


void Grid::Draw(set Drawlist)
{
	Color color =  Color{ 0,255,0,255 };
	for (const auto& cell : Drawlist)
	{
		DrawRectangle((float)cell.first * cellsize, (float)cell.second * cellsize, (float)cellsize - 1, (float)cellsize - 1, color);
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

void Grid::GetStateToChange(int column, int row) {
	int liveNeighbours = CountLiveNeighbours(column, row);
	int cellValue = GetCellValue(column, row);

	if (cellValue == 1)
	{
		if (liveNeighbours > 3 || liveNeighbours < 2)
		{
			tempcells[row][column] = 0;
			ActiveCells.erase({ column,row });
		
		}
		
	}
	else
	{
		if (liveNeighbours == 3)
		{
			tempcells[row][column] = 1;
			ActiveCells.insert({ column, row });
			
		}
	}
	std::cout << liveNeighbours << ' ' << tempcells[row][column] << '\n';
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

void Grid::GetCellsToChange() {
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
			GetStateToChange(pos.first, pos.second);
		}
	
	}
	cells = tempcells;

}

std::unordered_set<IntPair, pair_hash> Grid::ReturnActiveCells()
{
	return ActiveCells;
}