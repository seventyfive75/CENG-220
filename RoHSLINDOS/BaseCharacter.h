#pragma once
#include "raylib.h"

class BaseCharacter {
public:
    BaseCharacter(Vector2 pos, float speed);
    virtual ~BaseCharacter() {}

    virtual void tick(float deltaTime); // override edilir
    virtual void draw();
    bool getAlive() const;
    void setAlive(bool alive);
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() { return health; }
    void takeDamage(float damage);

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

    float health{};
    float enemyDamage{};
    float knightDamage{10000};

    Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
    Rectangle weaponCollisionRec{};

    void updateAnimation(float deltaTime);


private:
    bool alive{ true };

};
