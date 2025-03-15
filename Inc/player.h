#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

void Player_Init(Player* player);
void Player_Update(Player* player, float deltaTime);
void Player_Draw(Player* player);

#endif
