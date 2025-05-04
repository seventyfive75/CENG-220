#include "raylib.h"
#include "config.h" // Ekran boyutlarýný buradan çekiyoruz

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frameX;
    int frameY;
    float runningTime;
    float updateTime;
};

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RoHSLINDOS");

    //Main character animation settings
    Texture2D scarfy = LoadTexture("assets/scarfy.png");
    AnimData scarfyData{
        {0.0, 0.0, scarfy.width / 6, scarfy.height},
        {SCREEN_WIDTH / 2 - scarfy.width / 12, SCREEN_HEIGHT - scarfy.height},
        0,
        0,
        0.0,
        1.0 / 12.0
    };
    
    //obstacle animation settings
    Texture2D nebula = LoadTexture("assets/12_nebula_spritesheet.png");
    AnimData nebulae[sizeOfNebulae];

    //creating obstacles with a for loop
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = SCREEN_WIDTH - i * 300;
        nebulae[i].pos.y = SCREEN_HEIGHT - nebula.height / 8;
        nebulae[i].frameX = 0;
        nebulae[i].frameY = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
    }

    SetTargetFPS(165);
    while (!WindowShouldClose()) {

        deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);



        //scarfy animation frame update
        scarfyData.runningTime += deltaTime;
        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0;
            scarfyData.rec.x = scarfyData.frameX * scarfyData.rec.width;
            scarfyData.frameX++;
            if (scarfyData.frameX > 5)
            {
                scarfyData.frameX = 0;
            }
        }

        //obstacles animation frame update
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].runningTime += deltaTime;
            if (nebulae[i].runningTime > nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0;
                nebulae[i].rec.x = nebulae[i].frameX * nebulae[i].rec.width;
                nebulae[i].rec.y = nebulae[i].frameY * nebulae[i].rec.height;
                nebulae[i].frameX++;
                if (nebulae[i].frameX > 7)
                {
                    nebulae[i].frameX = 0;
                    nebulae[i].frameY++;
                }
                if (nebulae[i].frameY > 7)
                {
                    nebulae[i].frameY = 0;
                }
            }
        }

        //karakteri ve engelleri çizim
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
