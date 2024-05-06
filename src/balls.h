#pragma once
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_OBJECTS 100
#define GRID_SIZE 50

typedef struct
{
    float radius;
    Vector2 pos;
    Vector2 speed;
    bool collided;
    Rectangle currentTile;
} Object;

typedef struct
{
    Object *objects[MAX_OBJECTS];
} ObjectList;

float MeasureDistanceBetween(Object *first, Object *second)
{
    // a^2+b^2=c^2
    if (first == NULL || second == NULL)
        return 0.0;
    float x = abs(first->pos.x - second->pos.x);
    float y = abs(first->pos.y - second->pos.y);
    return sqrt(x + y);
}

void DrawObject(Object *object)
{
    if (object == NULL)
        return;
    DrawCircleV(object->pos, object->radius, RED);
}

void UpdateObject(Object *object)
{
    if (object == NULL)
        return;
    if (object->pos.x < 0 + object->radius ||
        object->pos.x > GetScreenWidth() - object->radius /*|| object->collided == true*/)
    {
        object->speed.x *= -1;
        // object->collided = false;
    }
    if (object->pos.y < 0 + object->radius ||
        object->pos.y > GetScreenHeight() - object->radius /*|| object->collided == true*/)
    {
        object->speed.y *= -1;
        // object->collided = false;
    }
    Vector2 movement = Vector2Scale(object->speed, GetFrameTime());
    object->pos = Vector2Add(object->pos, movement);
}

void AddObject(ObjectList *list, float size, Vector2 position, Vector2 speed)
{
    printf("Adding Object\n");
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (list->objects[i] == NULL)
        {
            Object *object = malloc(sizeof(Object));
            if (object == NULL)
            {
                free(object);
                return;
            }
            *object = (Object){
                size,
                position,
                speed,
                false,
                0,
            };
            list->objects[i] = object;
            return;
        }
    }
    printf("List is already full\n");
}

void TraverseList(ObjectList *list, void (*fn)(Object *))
{
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (list->objects[i] == NULL)
        {
            return;
        }
        (*fn)(list->objects[i]);
        // UpdateObject(list->objects[i]);
    }
}