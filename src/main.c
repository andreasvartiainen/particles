#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <malloc.h>
#define MAX_OBJECTS 100
#define GRID_SIZE 15

int screen_width = {800};
int screen_height = {400};
int fps = {60};

typedef struct
{
    float radius;
    Vector2 pos;
    Vector2 speed;
    bool collided;
} Object;

typedef struct
{
    Object *objects[MAX_OBJECTS];
} ObjectList;

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
            *object = (Object){
                size,
                position,
                speed,
                false,
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

void MyDrawGrid(ObjectList *list)
{
    int collision_amount = {0};
    for (int column = 0; column * GRID_SIZE < GetScreenWidth(); column++)
        for (int row = 0; row * GRID_SIZE < GetScreenWidth(); row++)
        {
            {
                Rectangle currentRectangle = {column * GRID_SIZE,
                                              row * GRID_SIZE, GRID_SIZE, GRID_SIZE};
                for (int i = 0; i < MAX_OBJECTS; i++)
                {
                    if (list->objects[i] != NULL)
                    {

                        if (CheckCollisionPointRec(list->objects[i]->pos, currentRectangle))
                        {
                            collision_amount += 1;
                            if (collision_amount > 1)
                            {
                                list->objects[i]->collided = true;
                            }
                        }
                    }
                }
                if (collision_amount >= 2)
                    DrawRectangleRec(currentRectangle, (Color){0, 0, 255, 50});
                else if (collision_amount > 0)
                    DrawRectangleRec(currentRectangle, (Color){255, 0, 0, 50});
                else
                    DrawRectangleLinesEx(currentRectangle, 1, (Color){0, 0, 0, 50});
                collision_amount = 0;
            }
        }
}

int main(void)
{
    InitWindow(screen_width, screen_height, "Visualizationss\n");
    SetTargetFPS(60);

    ObjectList list = {NULL};

    for (int i = 0; i < 10; i++)
    {
        AddObject(&list, 5, (Vector2){screen_width / 2, screen_height / 2},
                  (Vector2){GetRandomValue(-200, 200), GetRandomValue(-200, 200)});
    }

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            AddObject(&list, 5, GetMousePosition(), (Vector2){GetRandomValue(-200, 200), GetRandomValue(-200, 200)});
        TraverseList(&list, &UpdateObject);
        BeginDrawing();
        ClearBackground(WHITE);
        MyDrawGrid(&list);
        TraverseList(&list, &DrawObject);
        EndDrawing();
        printf("%f\n", GetFrameTime());
    }

    for (int i = 0; i < MAX_OBJECTS; i++)
    {
        if (list.objects[i] == NULL)
            break;
        free(list.objects[i]);
        list.objects[i] = NULL;
        printf("Removing objects from memory!\n");
    }

    return 0;
}
