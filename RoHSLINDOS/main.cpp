#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    const int mapWidth = 3060, mapHeight = 3060;
    const float playerSpeed = 500.0f;
    const int sizeOfProps{10};
    

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

    //prop
    Prop props[sizeOfProps];
    for (int i = 0; i < sizeOfProps; i++) {
        SetRandomSeed(1234);
        float randomPosX = GetRandomValue(500, 3060);
        float randomPosY = GetRandomValue(500, 3060);
        props[i] = Prop(Vector2{randomPosX,randomPosY}, LoadTexture("nature_tileset/Rock.png"));
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //INPUT ALIM KISMI

        //UPDATE KISMI
        float deltaTime = GetFrameTime();

        camera.target = knight.getPosition();

        knight.tick(deltaTime, camera);  

        for (auto& prop : props) {
            if (CheckCollisionRecs(prop.getCollisionRec(), knight.getCollisionRec())) {
                knight.undoMovement();
            }
        }

        //ÇÝZÝM KISMI
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        //bütün çizimler buraya

        //harita çizimi
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        for (auto& prop : props) {
            prop.Render();
        }

        knight.draw();
        EndMode2D();
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();

}

