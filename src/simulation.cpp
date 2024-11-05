#include "simulation.h"
#include <raylib.h>



void Simulation::FillBackground()
{
	ClearBackground(Color{ 29,29,29,255 });
}

void Simulation::DrawLines()
{
	Color color = { 0,0,0,255 };
	for (unsigned int column = 0; column < grid.GetColumns(); column++)
	{
			int x = (column + 1) * grid.GetCellSize();
			DrawLine(x, 0, x, grid.GetRows() * grid.GetCellSize(), color);
	}
	for (unsigned int row = 0; row < grid.GetRows(); row++)
	{
		int y = (row + 1) * grid.GetCellSize();
		DrawLine(0, y, grid.GetColumns()*grid.GetCellSize(), y, color);
	}
}

void Simulation::Draw() {
	DrawBacking();

	std::list<std::vector<int>>ListedActive = grid.ReturnActiveList();
	Drawlist.insert(Drawlist.end(), ListedActive.begin(), ListedActive.end());

	DrawRectangle(0, 0, 25, 25, Color{ 255,255,255,255 });
	grid.Draw(Drawlist);
	Drawlist = {};
}

void Simulation::SetCellValue(int column, int row, int value) {
	int state = grid.GetCellValue(column, row);
	if (state != value)
	{
		grid.setValue(column, row, value);
		Drawlist.push_back(std::vector<int>{column, row, value});
	}
	grid.ShowActive();
}

void Simulation::Update() 
{
	if (isRunning())
	{
		ChangeList = grid.GetCellsToChange();
		
		for (const auto& cell : ChangeList)
		{
			grid.setValue(cell[0], cell[1], cell[2]);
		}
		//grid.ShowActive();

	}
}