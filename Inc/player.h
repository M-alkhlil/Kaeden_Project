#ifndef PLAYER_H
#define PLAYER_H

#include "cprocessing.h"
#include "level.h"

#define PLAYER_SPEED 300.0f
#define JUMP_POWER -600.0f
#define GRAVITY 1200.0f  // Increased for faster fall
#define FRAME_TIME 0.1f
#define FRAME_COUNT 8
#define PLAYER_WIDTH 200.0f  // Kept at 200
#define PLAYER_HEIGHT 200.0f // Kept at 200

typedef struct {
    CP_Image frames[FRAME_COUNT];
    float x, y;
    float frameTimer;
    int currentFrame;
    int isMoving;
    int facingRight;
    float velocityY;
    int isJumping;
} Player;

void Player_Init(Player* player);
void Player_Update(Player* player, float deltaTime);
void Player_Draw(Player* player);
void Player_Free(Player* player);

#endif