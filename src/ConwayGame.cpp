#include <iostream>
#include <raylib.h>

//include my code
#include "grid.h"

int main()
{
    Color GREY = { 29, 29, 29, 255 };

    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;  
    const int CELLSIZE = 25;

    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "conway");
    SetTargetFPS(FPS);

    Grid grid = Grid(WINDOW_WIDTH, WINDOW_HEIGHT, CELLSIZE);
    grid.setValue(2, 1, 1);

    while (WindowShouldClose() == false) {
        //event handling
        //updating state
        BeginDrawing();
        ClearBackground(GREY);
        //drawing
        grid.Draw();
        EndDrawing();
    }

    CloseWindow();
}
