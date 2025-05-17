#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter {
public:
    Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight);

    void tick(float deltaTime, Camera2D& camera);

private:
    int screenW, screenH;
    int mapW, mapH;
};