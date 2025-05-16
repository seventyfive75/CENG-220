#pragma once
#include "raylib.h"

class Prop {
public:
    Prop(); // Varsayýlan ctor
    Prop(Vector2 pos, Texture2D tex);

    void Render();
    Rectangle getCollisionRec() const;

private:
    Texture2D texture;
    Vector2 worldPos;
    float scale = 4.0f; // Haritada büyütme oraný
};