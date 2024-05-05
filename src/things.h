#pragma once
#include <malloc.h>
#include <stdio.h>

void random()
{
    int rows = 5;
    int columns = 6;
    int **array2d = malloc(sizeof(*array2d) * rows);
    for (int i = 0; i < rows; i++)
    {
        array2d[i] = malloc(sizeof(array2d[0]) * columns);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int ii = 0; ii < columns; ii++)
        {
            array2d[i][ii] = i;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int ii = 0; ii < columns; ii++)
        {
            printf("%d", array2d[i][ii]);
        }
        printf("\n");
    }
}