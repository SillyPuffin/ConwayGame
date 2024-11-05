#include "simulation.h"
#include <raylib.h>



void Simulation::FillBackground()
{
	ClearBackground(Color{ 29,29,29,255 });
}

void Simulation::DrawLines()
{
	Color color = { 0,0,0,255 };
	for (int column = 0; column < grid.GetColumns()+1; column++)
	{
			int x = (column + 1) * grid.GetCellSize();
			DrawLine(x, 0, x, grid.GetRows() * grid.GetCellSize(), color);
	}
	for (int row = 0; row < grid.GetRows(); row++)
	{
		int y = (row + 1) * grid.GetCellSize();
		DrawLine(0, y-1, grid.GetColumns()*grid.GetCellSize(), y-1, color);
	}
}

void Simulation::Draw() {
	if (!started)
	{
		DrawBacking();
		started = true;
	}

	grid.Draw(Drawlist);
	Drawlist = {};
}

void Simulation::SetCellValue(int column, int row, int value) {
	int state = grid.GetCellValue(column, row);
	grid.setValue(column, row, value);
	if (state != value)
	{
		Drawlist.push_back({ column,row,value });
	}
	//grid.ShowActive();
}

void Simulation::Clear()
{
	IntVecList oldActives = grid.ReturnActiveList(0);
	Drawlist.insert(Drawlist.end(), oldActives.begin(), oldActives.end());
	grid.Clear();
}

void Simulation::Reset()
{
	grid.fillRandom();
	IntVecList newActives = grid.ReturnActiveList(1);
	Drawlist.insert(Drawlist.end(), newActives.begin(), newActives.end());
	run = false;
	started = false;
}

void Simulation::Update() 
{
	if (isRunning())
	{
		ChangeList = grid.GetCellsToChange();
		Drawlist.insert(Drawlist.end(), ChangeList.begin(),ChangeList.end());
		
		for (const auto& cell : ChangeList)
		{
			grid.setValue(cell[0], cell[1], cell[2]);
		}
		//grid.ShowActive();

	}
}