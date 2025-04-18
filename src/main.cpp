#include "raylib.h"
#include "config.h" // Ekran boyutlarýný buradan çekiyoruz

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib 2D Game Template");

    Texture2D sprite = LoadTexture("assets/character.png");

    int frameWidth = sprite.width / 6;
    int frameHeight = sprite.height;
    int currentFrame = 0;
    float frameTime = 0.0f;
    float updateTime = 0.1f;

    Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Vector2 position = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };

    SetTargetFPS(165);
    while (!WindowShouldClose()) {
        frameTime += GetFrameTime();

        if (frameTime >= updateTime) {
            currentFrame++;
            if (currentFrame > 5) currentFrame = 0;
            frameRec.x = (float)currentFrame * frameWidth;
            frameTime = 0.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("raylib animasyon sablonu!", 10, 10, 20, DARKGRAY);
        DrawTextureRec(sprite, frameRec, position, WHITE);
        DrawFPS(700, 10);

        EndDrawing();
    }

    UnloadTexture(sprite);
    CloseWindow();

    return 0;
}
