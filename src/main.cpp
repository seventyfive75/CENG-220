#include "raylib.h"
#include "config.h" // Ekran boyutlarýný buradan çekiyoruz

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RoHSLINDOS");

    SetTargetFPS(165);
    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);




        EndDrawing();
    }

    CloseWindow();

    return 0;
}
