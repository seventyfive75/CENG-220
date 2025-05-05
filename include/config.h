// config.h içeriði
#ifndef CONFIG_H
#define CONFIG_H

// Ayarlar buraya (örnek:)
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const int sizeOfNebulae{ 2 };
const int gravity{ 10000 }; //((pixels / seconds) / seconds)
int jumpVel{ -2000 }; //(pixels / seconds)
int nebVel{ -500 }; //(pixels / seconds)
int velocity{ 0 }; //(pixels / seconds)
float deltaTime{};
float finishline{};
bool IsInTheAir{};
bool collision{};
bool IsGameContinues;

float bgPosX;
float mgPosX;
float fgPosX;

#endif