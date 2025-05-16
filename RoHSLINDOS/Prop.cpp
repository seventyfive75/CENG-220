#include "Prop.h"
#include "raymath.h"

Prop::Prop() {
    worldPos = { 0.0f, 0.0f };
    texture = Texture2D{};
}

Prop::Prop(Vector2 pos, Texture2D tex) :
    worldPos(pos), texture(tex) 
{

}

void Prop::Render() {
    DrawTextureEx(texture, worldPos, 0.0f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 Character_Pos) const {
    return Rectangle{
        worldPos.x,
        worldPos.y,
        texture.width * scale,
        texture.height * scale
    };
}
