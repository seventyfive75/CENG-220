#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, float speed, float hlth, float dps, Texture2D idle, Texture2D run)
    : BaseCharacter(pos, speed), target(nullptr) {
    enemyDamage = dps;
    health = hlth;
    idleTexture = idle; 
    runTexture = run;
    currentTexture = idleTexture;
}



void Enemy::tick(float deltaTime) {

    if (!target->getAlive()) return;
    if (!getAlive()) return;

    if (target) {
        Vector2 direction = Vector2Subtract(target->getPosition(), position);
        if (Vector2Length(direction) > 50.f && Vector2Length(direction) < 445) {
            direction = Vector2Normalize(direction);
            moveX = direction.x;
            moveY = direction.y;
        }
        else {
            moveX = 0.0f;
            moveY = 0.0f;
        }
    }

    const float margin = 250.f;
    position.x = Clamp(position.x, 180.0f, 3060 - margin);
    position.y = Clamp(position.y, 180.0f, 3060 - margin);

    BaseCharacter::tick(deltaTime);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionRecs(getCollisionRec(), target->getWeaponCollisionRec()))
        {
            takeDamage(knightDamage * deltaTime);
        }
    }

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(enemyDamage * deltaTime);
    }

}

void Enemy::setTarget(BaseCharacter* t) {
    target = t;
}

