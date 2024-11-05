#pragma once
#include "grid.h"

class Simulation
{
public:
	Simulation(int width, int height, int cellsize)
		: grid(width, height, cellsize), run(false), ChangeList({}), started(false), Drawlist({})
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
	void Reset() { Stop(); ChangeList = {}; grid.fillRandom(); }
	void Clear() { ChangeList = {}; grid.Clear(); Stop(); }


private:
	Grid grid;
	std::list<std::vector<int>> ChangeList;
	std::list<std::vector<int>> Drawlist;
	bool started;
	bool run;
};
