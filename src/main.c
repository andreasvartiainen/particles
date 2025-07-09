#include "grid.h"
#include <malloc.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define COMMENT

int screen_width = {800};
int screen_height = {500};
int fps = {60};
int grid_size = 5;

int main(void) {

#ifdef COMMENT
  InitWindow(screen_width, screen_height, "Falling Sand\n");
  SetTargetFPS(fps);

  Grid *grid =
      InitGrid(GetScreenWidth() / grid_size, GetScreenHeight() / grid_size,
               grid_size, (Color){255, 220, 200, 255});
  // Grid *grid = InitGridDyn(5, 3, grid_size,
  //                          (Color){255, 0, 0, 30});

  while (!WindowShouldClose()) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 pos = CheckMousePosition(grid);
      if (pos.x || pos.y != -1) {
        SetActiveTile(pos.x, pos.y, grid);
      }
    }
    // CheckMousePosition(grid);
    UpdateGrid(grid);
    BeginDrawing();
    ClearBackground(BLUE);
    MyDrawGrid(grid, false);
    EndDrawing();
  }
  DeleteGrid(grid);
#endif

  return 0;
}
