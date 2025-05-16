#pragma once
#include "raylib.h"
#include "raymath.h"

class Character {
public:
    Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight);

    void tick(float deltaTime, Camera2D& camera);
    void draw();
    void undoMovement();

    Vector2 getPosition() const;
    Rectangle getCollisionRec() const;

private:
    Texture2D knight_idle;
    Texture2D knight_run;
    Texture2D currentTexture;

    Vector2 position{};
    Vector2 worldPosLastFrame{};
    float moveX{}, moveY{};
    float speed;

    float currentSpeedX{}, currentSpeedY{};
    float targetSpeedX{}, targetSpeedY{};

    float facingDirection{ 1.0f };

    int frame{};
    float runningTime{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.f / 12.f };

    int screenW, screenH;
    int mapW, mapH;

    void updateMovement(float deltaTime);
    void updateAnimation(float deltaTime);
};