#include "Global.h"

bool isGameStart = false;
bool running = false;

std::unique_ptr<Atlas> AtlasPimonShadow(new Atlas(_T("img/shadow_player.png"), 1));
std::unique_ptr<Atlas> AtlasPimonLeft(new Atlas(_T("img/player_left_%d.png"), 6));
std::unique_ptr<Atlas> AtlasPimonRight(new Atlas(_T("img/player_right_%d.png"), 6));

std::unique_ptr<Atlas> AtlasEnemyShadow(new Atlas(_T("img/shadow_enemy.png"), 1));
std::unique_ptr<Atlas> AtlasEnemyLeft(new Atlas(_T("img/enemy_left_%d.png"), 6));
std::unique_ptr<Atlas> AtlasEnemyRight(new Atlas(_T("img/enemy_right_%d.png"), 6));