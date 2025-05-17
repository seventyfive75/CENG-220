#pragma once
#include "raylib.h"

class BaseCharacter {
public:
    BaseCharacter(Vector2 pos, float speed);
    virtual ~BaseCharacter() {}

    virtual void tick(float deltaTime); // override edilir
    virtual void draw() const;

    Vector2 getPosition() const;
    Rectangle getCollisionRec() const;
    void undoMovement();

protected:
    Texture2D idleTexture{};
    Texture2D runTexture{};
    Texture2D currentTexture{};

    Vector2 position{};
    Vector2 worldPosLastFrame{};

    float speed{};
    float moveX{}, moveY{};
    float currentSpeedX{}, currentSpeedY{};
    float targetSpeedX{}, targetSpeedY{};

    float facingDirection{ 1.0f };

    int frame{};
    float runningTime{};
    const int maxFrames{ 6 };
    const float updateTime{ 1.0f / 6.0f };

    void updateAnimation(float deltaTime);
};
