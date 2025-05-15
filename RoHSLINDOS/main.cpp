#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
    const int mapWidth = 3050, mapHeight = 4050;
    const float playerSpeed = 500.0f;
    float targetSpeedX{};
    float targetSpeedY{};
    float currentSpeedX = 0.0f;
    float currentSpeedY = 0.0f;
    float deltaTime{};
    float moveX{};
    float moveY{};
    float runningTime{};
    int frame{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.f / 12.f };
    float facingDirection{ 1.0f }; //default sað


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Game");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{ 0.0, 0.0 };

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png"); //durma
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png"); //koþma
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png"); //ana tex
    Vector2 knightPos{
        (float)SCREEN_WIDTH / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)SCREEN_HEIGHT / 2.0f - 4.0f * (0.5f * (float)knight.height)
    };

    Camera2D camera{
        {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f} ,
         knightPos,
         0.0f,
         1.0f
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //INPUT ALIM KISMI
        moveX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A); // -1, 0 veya 1
        moveY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W); // -1, 0 veya 1

        //UPDATE KISMI
        deltaTime = GetFrameTime();

        //Çapraz daha hýzlý gitmeyi önleme
        Vector2 moveDir = { moveX, moveY };
        if (Vector2Length(moveDir) > 0) {
            moveDir = Vector2Normalize(moveDir);
        }

        //hareket için targetSpeed belirleme
        targetSpeedX = moveDir.x * playerSpeed;
        targetSpeedY = moveDir.y * playerSpeed;

        //ivmeli hareket için lerp
        currentSpeedX = Lerp(currentSpeedX, targetSpeedX, 10.0f * deltaTime);
        currentSpeedY = Lerp(currentSpeedY, targetSpeedY, 10.0f * deltaTime);

        //hareket update i 
        knightPos.x += currentSpeedX * deltaTime;
        knightPos.y += currentSpeedY * deltaTime;

        //kamera update
        camera.target = knightPos;

        //sýnýrlar içerisinde ise clample
        if (mapWidth > SCREEN_WIDTH)
        {
            camera.target.x = Clamp(knightPos.x, SCREEN_WIDTH / 2.0f, mapWidth - SCREEN_WIDTH / 2.0f);
        }
        if (mapHeight > SCREEN_HEIGHT)
        {
            camera.target.y = Clamp(knightPos.y, SCREEN_HEIGHT / 2.0f, mapWidth - SCREEN_HEIGHT / 2.0f);

        }

        //belki kamera için de ileride lerp???

        //karakter duruyor mu koþuyor mu
        knight = (moveX != 0.0f || moveY != 0.0f) ? knight_run : knight_idle;

        //facing direction update
        if (moveX != 0) facingDirection = (moveX > 0) ? 1.0f : -1.0f;

        // sprite sheet i güncelleme
        runningTime += deltaTime;
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }

        //ÇÝZÝM KISMI
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        //bütün çizimler buraya

        //harita çizimi
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //karakter çizimi
        Rectangle source{ frame * (float)knight.width / 6.f, 0.f, facingDirection * (float)knight.width / 6.f, (float)knight.height };
        Rectangle dest{ knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height };
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(knight);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);
    UnloadTexture(map);
    CloseWindow();

}

