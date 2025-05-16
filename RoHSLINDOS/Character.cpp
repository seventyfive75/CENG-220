#include "Character.h"

Character::Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight) :
    position(pos), speed(s), screenW(screenWidth), screenH(screenHeight), mapW(mapWidth), mapH(mapHeight) 
{
    knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    currentTexture = knight_idle;
}

void Character::tick(float deltaTime, Camera2D& camera) 
{
    worldPosLastFrame = position;

    moveX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    moveY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    Vector2 moveDir = { moveX, moveY };
    if (Vector2Length(moveDir) > 0) moveDir = Vector2Normalize(moveDir);

    targetSpeedX = moveDir.x * speed;
    targetSpeedY = moveDir.y * speed;

    currentSpeedX = Lerp(currentSpeedX, targetSpeedX, 10.0f * deltaTime);
    currentSpeedY = Lerp(currentSpeedY, targetSpeedY, 10.0f * deltaTime);

    position.x += currentSpeedX * deltaTime;
    position.y += currentSpeedY * deltaTime;

    facingDirection = (moveX != 0) ? ((moveX > 0) ? 1.0f : -1.0f) : facingDirection;

    currentTexture = (moveX != 0 || moveY != 0) ? knight_run : knight_idle;

    const float margin = 80.f;
    position.x = Clamp(position.x, 0.0f, mapW - margin);
    position.y = Clamp(position.y, 0.0f, mapH - margin);

    // Kamera hedefini clamp ile sýnýrla
    camera.target.x = Clamp(position.x, screenW / 2.0f, mapW - screenW / 2.0f);
    camera.target.y = Clamp(position.y, screenH / 2.0f, mapH - screenH / 2.0f);


    updateAnimation(deltaTime); 
}

void Character::updateAnimation(float deltaTime) {
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }
}

void Character::draw() {
    Rectangle source{ frame * (float)currentTexture.width / 6.f, 0.f, facingDirection * (float)currentTexture.width / 6.f, (float)currentTexture.height };
    Rectangle dest{ position.x, position.y, 4.0f * (float)currentTexture.width / 6.0f, 4.0f * (float)currentTexture.height };
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);
}

Vector2 Character::getPosition() const {
    return position;
}

void Character::undoMovement()
{
    position = worldPosLastFrame;
}

Rectangle Character::getCollisionRec() const {
    return Rectangle{
        position.x,
        position.y,
        (float)currentTexture.width / 6.0f * 4.0f,
        (float)currentTexture.height * 4.0f
    };
}
