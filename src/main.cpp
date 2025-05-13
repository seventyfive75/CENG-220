#include "raylib.h"

int main()
{
    const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib Game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    Vector2 mapPos{ 0.0, 0.0 };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);


        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}

