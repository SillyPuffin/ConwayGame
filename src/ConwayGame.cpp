#include <iostream>
#include <raylib.h>

//include my code
#include "grid.h"
#include "simulation.h"

int main()
{
    Color GREY = { 29, 29, 29, 255 };

    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;  
    const int CELLSIZE = 15;

    float FPS = 10.0;
    float interval = 1.0f / FPS;
    float Timer = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "conway");
    
    Simulation sim{ WINDOW_WIDTH,WINDOW_HEIGHT,CELLSIZE };
    

    while (WindowShouldClose() == false) 
    {
        //delta time
        float dt = GetFrameTime();

        //event handling
        if (IsKeyReleased(KEY_ENTER) && sim.isRunning() == false)
        {
            sim.Start();
        }
        else if (IsKeyReleased(KEY_ENTER) && sim.isRunning() == true)
        {
            sim.Stop();
        }

        if (IsKeyPressed(KEY_R))
        {
            sim.Reset();
        }
        if (IsKeyPressed(KEY_C))
        {
            sim.Clear();
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
        if (Timer >= interval)
        {
            sim.Update();
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

        EndDrawing();
    }

    CloseWindow();
}
