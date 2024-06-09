#pragma once

#include <memory>

#include "Atlas.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BUTTON_WIDTH 192
#define BUTTON_HEIGHT 75

extern bool isGameStart;
extern bool running;

extern std::unique_ptr<Atlas> AtlasPimonShadow;
extern std::unique_ptr<Atlas> AtlasPimonLeft;
extern std::unique_ptr<Atlas> AtlasPimonRight;

extern std::unique_ptr<Atlas> AtlasEnemyShadow;
extern std::unique_ptr<Atlas> AtlasEnemyLeft;
extern std::unique_ptr<Atlas> AtlasEnemyRight;