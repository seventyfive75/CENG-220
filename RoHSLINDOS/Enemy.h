#pragma once
#include "BaseCharacter.h"

class Enemy : public BaseCharacter {
public:

    Enemy(Vector2 pos, float speed, float hlth, float dps, Texture2D idle, Texture2D run);
    void tick(float deltaTime) override;
    void setTarget(BaseCharacter* target);

private:
    BaseCharacter* target; //pointer

};
