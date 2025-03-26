#ifndef GAME_H
#define GAME_H

#include "cprocessing.h"
#include "player.h"
#include "level.h"

#define SCREEN_WIDTH 1600   
#define SCREEN_HEIGHT 900  

void StartGame(void);
void InitializeGame(void);
void UpdateGame(void);
void ExitGame(void);

#endif