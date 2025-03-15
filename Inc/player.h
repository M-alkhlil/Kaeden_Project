#ifndef PLAYER_H
#define PLAYER_H
#define groundLevel 830.0f


#include "game.h"

void Player_Init(Player* player,float startX,float startY);
void Player_Update(Player* player, float deltaTime);
void Player_Draw(Player* player);

#endif
