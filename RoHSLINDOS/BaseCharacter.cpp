#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(Vector2 pos, float s)
    : position(pos), speed(s) {
}

void BaseCharacter::updateAnimation(float deltaTime) {
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }
}

void BaseCharacter::draw() const {
    Rectangle source{ frame * (float)currentTexture.width / 6.f, 0.f,
                      facingDirection * (float)currentTexture.width / 6.f,
                      (float)currentTexture.height };
    Rectangle dest{ position.x, position.y,
                    4.0f * (float)currentTexture.width / 6.0f,
                    4.0f * (float)currentTexture.height };
    DrawTexturePro(currentTexture, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::tick(float deltaTime) {
    worldPosLastFrame = position;

    Vector2 moveDir = { moveX, moveY };
    if (Vector2Length(moveDir) > 0) moveDir = Vector2Normalize(moveDir);

    targetSpeedX = moveDir.x * speed;
    targetSpeedY = moveDir.y * speed;

    currentSpeedX = Lerp(currentSpeedX, targetSpeedX, 10.0f * deltaTime);
    currentSpeedY = Lerp(currentSpeedY, targetSpeedY, 10.0f * deltaTime);

    position.x += currentSpeedX * deltaTime;
    position.y += currentSpeedY * deltaTime;

    facingDirection = (moveX != 0) ? ((moveX > 0) ? 1.0f : -1.0f) : facingDirection;

    currentTexture = (moveX != 0 || moveY != 0) ? runTexture : idleTexture;

    updateAnimation(deltaTime);
}

Vector2 BaseCharacter::getPosition() const {
    return position;
}

Rectangle BaseCharacter::getCollisionRec() const {
    return Rectangle{
        position.x,
        position.y,
        (float)currentTexture.width / 6.0f * 4.0f,
        (float)currentTexture.height * 4.0f
    };
}

void BaseCharacter::undoMovement() {
    position = worldPosLastFrame;
}
