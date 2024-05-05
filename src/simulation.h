#pragma once
#include <stdio.h>
#include <raylib.h>

#define SIM_GRID_LEN 500

typedef struct
{
    Rectangle *next, tile;
} Grid;

typedef struct
{
    Grid **head;
    int gridSize;
    int column, row;
} Simulation;

void AddTiles(Simulation *sim)
{
    if (sim->head == NULL)
    {
    }
}

Simulation *InitializeSimulation(int columns, int rows)
{
}
