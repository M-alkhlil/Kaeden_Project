#ifndef LEVEL_H
#define LEVEL_H

#include "cprocessing.h"

#define BOX_SIZE 75 
#define NUM_BLOCKS 100

typedef struct {
    float x;
    float y;
} Block;

typedef struct {
    float x;
    float y;
} Box;

typedef struct {
    float x;
    float y;
} Ladder;

typedef struct {
    float x;
    float y;
} Fence;

extern Block blocks[NUM_BLOCKS];
extern Box box;
extern Ladder ladder;
extern Fence fence[5];

void InitializeLevel(void);
void DrawLevel(void);
void Level_Exit(void);

#endif
