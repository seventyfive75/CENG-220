#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

    //enemy
    Texture2D goblinIdle = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D goblinRun = LoadTexture("characters/goblin_run_spritesheet.png");

    Texture2D slimeIdle = LoadTexture("characters/slime_idle_spritesheet.png");
    Texture2D slimeRun = LoadTexture("characters/slime_run_spritesheet.png");

    Enemy goblin(Vector2{ 500.f, 600.f }, 300.f, 50.f, 80.0f, goblinIdle, goblinRun);
    Enemy slime(Vector2{ 500.f, 600.f }, 500.f, 25.f, 50.0f, slimeIdle, slimeRun);
    goblin.setTarget(&knight);  // knight karakteri hedef olarak atanýyor
    slime.setTarget(&knight);  // knight karakteri hedef olarak atanýyor

    
    Camera2D camera{
        {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f} ,
         knight.getPosition(),
         0.0f,
         1.0f
    };

    //prop
    Prop props[sizeOfProps];
    for (int i = 0; i < sizeOfProps; i += 2) {
        //getRandomValue almak için fonksiyon yazýlabilir. gereksiz kod yýðýný??? 
        SetRandomSeed(i);
        float randomPosX = GetRandomValue(500, 3060);
        float randomPosY = GetRandomValue(500, 3060);
        props[i] = Prop(Vector2{randomPosX,randomPosY}, LoadTexture("nature_tileset/Rock.png"));
        SetRandomSeed(i + 1);
        randomPosX = GetRandomValue(500, 3060);
        randomPosY = GetRandomValue(500, 3060);
        props[i + 1] = Prop(Vector2{ randomPosX,randomPosY }, LoadTexture("nature_tileset/Log.png"));
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

        goblin.tick(deltaTime);
        slime.tick(deltaTime);

        for (auto& prop : props) {
            if (CheckCollisionRecs(prop.getCollisionRec(), goblin.getCollisionRec())) {
                goblin.undoMovement();
            }
        }

        //ÇÝZÝM KISMI
        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode2D(camera);
        //bütün çizimler buraya

        //harita çizimi
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        

        goblin.draw();
        slime.draw();

        for (auto& prop : props) {
            prop.Render();
        }


        knight.draw();
        EndMode2D();

        if (!knight.getAlive()) //not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 50, RED);
            EndDrawing();
            continue;
        }
        else //alive
        {
            std::string knights_health = "Health: ";
            knights_health.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knights_health.c_str(), 20, 20, 40, RED);
        }

        EndDrawing();
    }
    UnloadTexture(goblinIdle);
    UnloadTexture(goblinRun);
    UnloadTexture(map);
    CloseWindow();

}

