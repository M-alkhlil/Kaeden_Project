#ifndef LEVEL_H
#define LEVEL_H

#include "cprocessing.h"
#include "player.h"

#define SCREEN_WIDTH 1600  // 50 tiles * 32px
#define SCREEN_HEIGHT 928  // 29 tiles * 32px
#define TILE_SIZE 32
#define GRID_COLS 50
#define GRID_ROWS 29

extern CP_Image tile_01, tile_02, tile_03, tile_13, tile_14;
extern CP_Image fountainFrames[4], bush1, bush2, bush3, bush4, bench1, bench2, tree4, tree3, Tree2, stone6, grass1, grass2, grass3, grass4, grass5;
extern int fountainFrameIndex;
extern float fountainAnimationTime;
extern const float fountainFrameDuration;





void InitializeLevel(void);
void MainGameLoop(void);
void Level_Exit(void);

#endif