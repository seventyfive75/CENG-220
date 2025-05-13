#include "raylib.h"
#include "raymath.h"

int main()
{
    const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    const int mapWidth = 3050, mapHeight = 4050;
    const float playerSpeed = 2000.0f;
    float deltaTime{};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{ 0.0, 0.0 };
    Vector2 playerPos{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

    Camera2D camera{ 
        {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f} ,
         playerPos,
         0.0f,
         1.0f
    };


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_A))
        {
            playerPos.x -= playerSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_D))
        {
            playerPos.x += playerSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_W))
        {
            playerPos.y -= playerSpeed * deltaTime;
        }
        if (IsKeyDown(KEY_S))
        {
            playerPos.y += playerSpeed * deltaTime;
        }
        camera.target = playerPos;

        camera.target.x = Clamp(camera.target.x, SCREEN_WIDTH / 2.0f, mapWidth - SCREEN_WIDTH / 2.0f);
        camera.target.y = Clamp(camera.target.y, SCREEN_HEIGHT / 2.0f, mapWidth - SCREEN_HEIGHT / 2.0f);

        mapPos.x = Clamp(mapPos.x, SCREEN_WIDTH, 0);

        BeginDrawing();
            ClearBackground(WHITE);
                BeginMode2D(camera);

                    DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
                    DrawCircleV(playerPos, 20, MAROON);

            EndMode2D();
 

        EndDrawing();
    }
    CloseWindow();
}

