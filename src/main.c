#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <malloc.h>
#include "grid.h"

#define COMMENT

int screen_width = {1000};
int screen_height = {1000};
int fps = {60};
int grid_size = 20;

int main(void)
{

#ifdef COMMENT
    InitWindow(screen_width, screen_height, "Visualizationss\n");
    SetTargetFPS(60);

    Grid *grid = InitGridDyn(GetScreenWidth() / grid_size, GetScreenHeight() / grid_size, grid_size,
                             (Color){255, 0, 0, 30});
    // Grid *grid = InitGridDyn(5, 3, grid_size,
    //                          (Color){255, 0, 0, 30});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        MyDrawGridDyn(grid);
        EndDrawing();
    }
#endif

    DeleteGrid(grid);
    return 0;
}
