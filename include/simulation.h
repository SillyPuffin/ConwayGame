#pragma once
#include "grid.h"

class Simulation
{
public:
	Simulation(int width, int height, int cellsize)
		: grid(width, height, cellsize), run(false), Drawlist({})
	{};

	void Stop() { run = false; }
	void Start() { run = true; }
	void SetCellValue(int column, int row, int value);

	void Draw();
	void DrawBacking() { FillBackground(); DrawLines(); }
	void DrawLines();
	void FillBackground();

	void Update();
	bool isRunning() { return run; }
	void Reset();
	void Clear();


private:
	Grid grid;
	IntPairList Drawlist;
	bool run;
};
