#include "Character.h"

Character::Character(Vector2 pos, float s, int screenWidth, int screenHeight, int mapWidth, int mapHeight) :
    BaseCharacter(pos, s), screenW(screenWidth), screenH(screenHeight), mapW(mapWidth), mapH(mapHeight)
{
    idleTexture = LoadTexture("characters/knight_idle_spritesheet.png");
    runTexture = LoadTexture("characters/knight_run_spritesheet.png");
    currentTexture = idleTexture;

    health = 100.f;
}

void Character::tick(float deltaTime, Camera2D& camera) 
{
    // Kamera hedefini clamp ile sýnýrla
    camera.target.x = Clamp(position.x, screenW / 2.0f, mapW - screenW / 2.0f);
    camera.target.y = Clamp(position.y, screenH / 2.0f, mapH - screenH / 2.0f);

    if (!getAlive()) return;

    moveX = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    moveY = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    BaseCharacter::tick(deltaTime);

    const float margin = 80.f;
    position.x = Clamp(position.x, 0.0f, mapW - margin);
    position.y = Clamp(position.y, 0.0f, mapH - margin);



    

    updateAnimation(deltaTime); 

    if (facingDirection > 0.f)
    {
        origin = { 0.f, weapon.width * 4.0f };
        offset = { 45.f, 55.f };
        //hitbox deðerleri
        weaponCollisionRec = {
            getPosition().x + offset.x + 10,
            getPosition().y + offset.y - weapon.height * scale + 10,
            weapon.width * scale - 20,
            weapon.height * scale - 20
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
    }
    else
    {
        origin = { weapon.width * scale, weapon.height * scale };
        offset = { 20.f, 55.f };
        weaponCollisionRec = {
            getPosition().x + offset.x - weapon.width * scale + 10,
            getPosition().y + offset.y - weapon.height * scale + 10,
            weapon.width * scale - 20,
            weapon.height * scale - 20
        };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
    }



}

void Character::draw() {
    if (!getAlive()) return;
    BaseCharacter::draw();

    //drawin the sword
    Rectangle source{ 0.0f,0.0f,static_cast<float>(weapon.width) * facingDirection,static_cast<float>(weapon.height) };
    Rectangle dest{ getPosition().x + offset.x, getPosition().y + offset.y, weapon.width * scale, weapon.height * scale };
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);


}

