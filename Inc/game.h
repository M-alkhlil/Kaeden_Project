#ifndef GAME_H
#define GAME_H

#include "cprocessing.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FRAME_COUNT 8
#define FRAME_TIME 0.15f
#define PLAYER_SPEED 200.0f
#define JUMP_POWER -1000.0f
#define GRAVITY 5500.0f

typedef struct {
	CP_Image frames[FRAME_COUNT];
	float x, y;
	float frameTimer;
	int currentFrame;
	int isMovingRight;
	int facingRight;
	float velocityY;
	int isJumping;
} Player;

extern CP_Image background;
extern Player player;

void InitializeGame(void);
void UpdateGame(void);
void ExitGame(void);

#endif