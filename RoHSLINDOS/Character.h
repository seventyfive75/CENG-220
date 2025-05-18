#pragma once
#include "raylib.h"
#include "raymath.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter {
public:
    Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight);
    void tick(float deltaTime, Camera2D& camera);
    virtual void draw() override;

private:
    int screenW, screenH;
    int mapW, mapH;

    float scale = 4.0f; // Haritada büyütme oraný

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

};