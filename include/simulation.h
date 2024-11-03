#pragma once
#include "grid.h"

class Simulation
{
public:
	Simulation(int width, int height, int cellsize)
		: grid(width, height, cellsize), tempGrid(width, height, cellsize), run(false)
	{};

	void Stop() { run = false; }
	void Start() { run = true; }
	int CountLiveNeighbours(int column, int row);
	void SetCellValue(int column, int row, int value);
	void Draw();
	void Update();
	bool isRunning() { return run; }
	void Reset() { run = false; grid.fillRandom(); }
	void Clear() { grid.Clear(); }


private:
	Grid grid;
	Grid tempGrid;
	bool run;
};
