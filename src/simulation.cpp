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
	DrawBacking();
	set oldActives = grid.ReturnActiveCells();
	grid.Draw(oldActives);
	Drawlist = {};
}

void Simulation::SetCellValue(int column, int row, int value) {
	grid.setValue(column, row, value);
	//grid.ShowActive();
}

void Simulation::Clear()
{
	set oldActives = grid.ReturnActiveCells();
	Drawlist.insert(Drawlist.end(), oldActives.begin(), oldActives.end());
	grid.Clear();
}

void Simulation::Reset()
{
	grid.fillRandom();
	set newActives = grid.ReturnActiveCells();
	Drawlist.insert(Drawlist.end(), newActives.begin(), newActives.end());
	run = false;
}

void Simulation::Update() 
{
	if (isRunning())
	{
		grid.GetCellsToChange();
		
		
		//grid.ShowActive();

	}
}