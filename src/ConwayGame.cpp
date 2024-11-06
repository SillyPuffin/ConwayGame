#include <iostream>
#include <raylib.h>

//include my code
#include "grid.h"
#include "simulation.h"

int main()
{
    Color GREY = { 29, 29, 29, 255 };

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 1280;  
    const int CELLSIZE = 10;

    float FPS = 10.0;
    int fps = 0;
    float interval = 1.0f / FPS;
    float Timer = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "conway");
    
    Simulation sim{ WINDOW_WIDTH,WINDOW_HEIGHT,CELLSIZE };
    

    while (WindowShouldClose() == false) 
    {
        //delta time
        float dt = GetFrameTime();

        //event handling
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();
            int column = mousePos.x / CELLSIZE;
            int row = mousePos.y / CELLSIZE;
            sim.SetCellValue(column, row, 1);
        }

        if (IsKeyReleased(KEY_ENTER) && sim.isRunning() == false)
        {
            sim.Start();
            SetWindowTitle("Game of life is running");
        }
        else if (IsKeyReleased(KEY_ENTER) && sim.isRunning() == true)
        {
            sim.Stop();
            SetWindowTitle("Game of life is paused");
        }

        if (IsKeyPressed(KEY_R))
        {
            sim.Reset();
            SetWindowTitle("Game of life is paused");
        }
        if (IsKeyPressed(KEY_C))
        {
            sim.Clear();
            SetWindowTitle("Game of life is paused");
        }

        //framerate
        if (IsKeyPressed(KEY_W))
        {
            FPS += 8.0f;
            interval = 1.0f / FPS;
            std::cout << FPS << "\n";
        }
        if (IsKeyPressed(KEY_S))
        {
            if (FPS > 10.0f)
            {
                FPS -= 8.0f;
                interval = 1.0f / FPS;
                std::cout << FPS << "\n";
            }
        }


        //updating state
        sim.Update();
        if (Timer >= interval)
        {
            //sim.Update();
            fps = (int)1 / dt;
            Timer = 0;
        }
        else 
        {
            Timer += dt;
        }
        

        //drawing
        BeginDrawing();
        ClearBackground(GREY);
        sim.Draw();
        DrawText(TextFormat("%04i", fps), 10, 10, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();
}
