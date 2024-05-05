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
} Tile;

typedef struct
{
    // how many nodes in the grid
    Tile **tiles2d;
    // what size to render the tiles in
    int columns, rows;
    int tile_size;
} Grid;

Grid *InitGridDyn(int colums, int rows, int tile_size, Color color)
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

void MyDrawGridDyn(const Grid *grid)
{
    if (grid == NULL)
    {
        return;
    }
    for (int i = 0; i < grid->rows; i++)
    {
        for (int ii = 0; ii < grid->columns; ii++)
        {
            const Tile *current = &grid->tiles2d[i][ii];
            DrawRectangleLinesEx(current->tile, 0.8, current->color);
        }
    }
}