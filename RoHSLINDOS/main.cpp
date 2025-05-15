#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    const int mapWidth = 3060, mapHeight = 3060;
    const float playerSpeed = 5000.0f;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{ 0.0, 0.0 };

    Character knight({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }, playerSpeed,
                 SCREEN_WIDTH, SCREEN_HEIGHT, mapWidth, mapHeight);

    Camera2D camera{
        {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f} ,
         knight.getPosition(),
         0.0f,
         1.0f
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //INPUT ALIM KISMI

        //UPDATE KISMI
        float deltaTime = GetFrameTime();

        camera.target = knight.getPosition();

        knight.tick(deltaTime, camera);

        //kamera update
        

        

        //ÇÝZÝM KISMI
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        //bütün çizimler buraya

        //harita çizimi
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.draw();

        EndMode2D();
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();

}

