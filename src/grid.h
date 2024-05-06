#pragma once
#include <raylib.h>
#include <malloc.h>
#include <stdio.h>

typedef struct
{
    // color of the individual grid tile
    // should this include list of items in tile? could
    // make it easier to calculate collisions
    Rectangle tile;
    Color color;
    bool active;
} Tile;

typedef struct
{
    // how many nodes in the grid
    Tile **tiles2d;
    // what size to render the tiles in
    int columns, rows;
    int tile_size;
} Grid;

Grid *InitGrid(int colums, int rows, int tile_size, Color color)
{
    // create pointer to grid
    Grid *new_grid = (Grid *)malloc(sizeof(Grid));
    if (new_grid == NULL)
    {
        // handle memory allocation failure
        free(new_grid);
        return NULL;
    }

    // allocate tile2d with the 2d array
    new_grid->tiles2d = (Tile **)malloc(sizeof(*new_grid->tiles2d) * rows);
    if (new_grid->tiles2d == NULL)
    {
        // handle memory allocation failure
        free(new_grid->tiles2d); // free previously allocated memory
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        // allocate all the rows with arrays of length column
        new_grid->tiles2d[i] = (Tile *)malloc(sizeof(*new_grid->tiles2d[0]) * colums);
        if (new_grid->tiles2d[i] == NULL)
        {
            for (int ii = 0; ii < i; ii++)
            {
                free(new_grid->tiles2d[ii]);
                free(new_grid->tiles2d);
                free(new_grid);
                return NULL;
            }
        }
    }

    // initialize tiles
    for (int i = 0; i < rows; i++)
    {
        for (int ii = 0; ii < colums; ii++)
        {
            Rectangle new_rect = {ii * tile_size, i * tile_size, tile_size, tile_size};
            new_grid->tiles2d[i][ii].tile = new_rect;
            new_grid->tiles2d[i][ii].color = color;
            new_grid->tiles2d[i][ii].active = false;
        }
    }

    // initialize rest of the items in struct
    new_grid->tile_size = tile_size;
    new_grid->columns = colums;
    new_grid->rows = rows;
    return new_grid;
}

void DeleteGrid(Grid *grid)
{
    if (grid == NULL)
        return;
    for (int i = 0; i < grid->rows; i++)
    {
        free(grid->tiles2d[i]);
    }
    free(grid->tiles2d);
    free(grid);
    printf("Grid Unallocated!\n");
}

Vector2 CheckMousePosition(Grid *grid)
{
    // if grid is not valid return 0 vector
    if (grid == NULL || grid->columns <= 0 || grid->rows <= 0)
    {
        return (Vector2){-1};
    }
    // check all the tiles
    for (int i = 0; i < grid->rows; i++)
    {
        for (int ii = 0; ii < grid->columns; ii++)
        {
            Tile *current = &grid->tiles2d[i][ii];
            // tile match with the mouse position, return the tile position
            // maybe could be possible or better to return a tile address?
            if (CheckCollisionPointRec(GetMousePosition(), current->tile))
            {
                return (Vector2){i, ii};
            }
            // if (CheckCollisionPointRec(GetMousePosition(), current->tile))
            // {
            //     current->color = (Color){0, 0, 255, 20};
            //     current->active = true;
            // }
            // else
            // {
            //     current->color = (Color){255, 0, 0, 20};
            //     current->active = false;
            // }
        }
    }
    return (Vector2){-1};
}

void SetActiveTile(int row, int column, Grid *grid)
{
    // TODO: Ability to create 5 x 5 etc. pixel blocks
    if (row >= grid->rows || column >= grid->columns)
        return;
    if (grid == NULL || column < 0 || row < 0)
        return;
    Tile *current = &grid->tiles2d[row][column];
    if (current->active == false)
    {
        grid->tiles2d[row][column].active = true;
        grid->tiles2d[row][column].color.r += GetRandomValue(-5, 0);
        grid->tiles2d[row][column].color.g += GetRandomValue(-5, 5);
        grid->tiles2d[row][column].color.b += GetRandomValue(-5, 5);
    }
}

void SwapTiles(Tile *first, Tile *second)
{
    if (first == NULL || second == NULL)
        return;
    Tile temp = *first;
    first->color = second->color;
    first->active = second->active;
    second->color = temp.color;
    second->active = temp.active;
}

void UpdateGrid(Grid *grid)
{
    // update all tile positions and make the sand fall
    for (int r = grid->rows - 1; r > 0; r--)
    {
        for (int c = grid->columns - 1; c >= 0; c--)
        {
            // get pointerst to current tiles, just to make things clearer
            Tile *bottom_tile = &grid->tiles2d[r][c];
            Tile *top_tile = &grid->tiles2d[r - 1][c];
            Tile *left_tile = &grid->tiles2d[r][c - 1];
            Tile *right_tile = &grid->tiles2d[r][c + 1];
            // falling straight down
            if (bottom_tile->active == false && top_tile->active == true)
            {
                SwapTiles(bottom_tile, top_tile);
                // printf("Swap!\n");
            }
            if (right_tile->active == false && top_tile->active == true && c < grid->columns - 1)
            {
                SwapTiles(right_tile, top_tile);
                // printf("Swap!\n");
            }
            if (left_tile->active == false && top_tile->active == true && c > 0)
            {
                SwapTiles(left_tile, top_tile);
                // printf("Swap!\n");
            }
        }
    }
}

void MyDrawGrid(const Grid *grid, bool draw_grid)
{
    if (grid == NULL || grid->columns <= 0 || grid->rows <= 0)
    {
        return;
    }
    for (int i = 0; i < grid->rows; i++)
    {
        for (int ii = 0; ii < grid->columns; ii++)
        {
            const Tile *current = &grid->tiles2d[i][ii];
            if (current->active)
                DrawRectangleRec(current->tile, current->color);
            else if (draw_grid)
                DrawRectangleLinesEx(current->tile, 0.8, current->color);
        }
    }
}