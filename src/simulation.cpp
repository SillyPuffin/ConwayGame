#include "simulation.h"
#include <vector>
#include <utility>

void Simulation::Draw() {
	grid.Draw();
}

void Simulation::SetCellValue(int column, int row, int value) {
	grid.setValue(column,row, value);
}

int Simulation::CountLiveNeighbours(int column, int row) {
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
		int neighbourRow = (row + offset.second + grid.GetRows()) % grid.GetRows();
		int neighbourColumn = (column + offset.first + grid.GetColumns()) % grid.GetColumns();
		liveNeighbours += grid.GetCellValue(neighbourColumn, neighbourRow);
	}

	return liveNeighbours;
}

void Simulation::Update() 
{
	if (isRunning())
	{
		for (int row = 0; row < grid.GetRows(); row++)
		{
			for (int column = 0; column < grid.GetColumns(); column++)
			{
				int liveNeighbours = CountLiveNeighbours(column, row);
				int cellValue = grid.GetCellValue(column, row);

				if (cellValue == 1)
				{
					if (liveNeighbours > 3 || liveNeighbours < 2)
					{
						tempGrid.setValue(column, row, 0);
					}
					else
					{
						tempGrid.setValue(column, row, 1);
					}
				}
				else
				{
					if (liveNeighbours == 3)
					{
						tempGrid.setValue(column, row, 1);
					}
					else
					{
						tempGrid.setValue(column, row, 0);
					}
				}
			}
		}
		grid = tempGrid;
	}
}