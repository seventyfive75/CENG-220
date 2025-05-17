#include "Character.h"

Character::Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight) :
    BaseCharacter(pos, s), screenW(screenWidth), screenH(screenHeight), mapW(mapWidth), mapH(mapHeight)
{
    idleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    runTexture = LoadTexture("characters/knight_run_spritesheet.png");
    currentTexture = idleTexture;
}

void Character::tick(float deltaTime, Camera2D& camera) 
{

    moveX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    moveY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    BaseCharacter::tick(deltaTime);

    const float margin = 80.f;
    position.x = Clamp(position.x, 0.0f, mapW - margin);
    position.y = Clamp(position.y, 0.0f, mapH - margin);

    // Kamera hedefini clamp ile sýnýrla
    camera.target.x = Clamp(position.x, screenW / 2.0f, mapW - screenW / 2.0f);
    camera.target.y = Clamp(position.y, screenH / 2.0f, mapH - screenH / 2.0f);


    updateAnimation(deltaTime); 
}

