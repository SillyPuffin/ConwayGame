#include <iostream>
#include <raylib.h>

//include my code
#include "grid.h"
#include "simulation.h"

int main()
{
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;  
    const int CELLSIZE = 25;

    float FPS = 5.0;
    float interval = 1.0f / FPS;
    float Timer = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "conway");
    ClearWindowState(FLAG_VSYNC_HINT);
    
    Simulation sim{ WINDOW_WIDTH,WINDOW_HEIGHT,CELLSIZE };
    RenderTexture2D RenTex = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    
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
            row = WINDOW_HEIGHT / CELLSIZE - row -1;
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
        BeginTextureMode(RenTex);
        sim.Draw();
        EndTextureMode();

        BeginDrawing();
        DrawTexture(RenTex.texture, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadRenderTexture(RenTex);
    CloseWindow();
}
