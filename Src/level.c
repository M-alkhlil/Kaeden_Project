#include "level.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define TILE_SIZE 50
#define GRID_COLS 40
#define GRID_ROWS 23

CP_Image tileImage, boxImage, ladderImage, fenceImage, groundTile, brickTile, slopeTile, slopeTile2, fountainFrames[4], ramp1, ramp2, bush1, bush2, bush3, bush4, bench1, bench2, tree4, tree3;
CP_Image Tree2, stone6, grass1, grass2, grass3, grass4, grass5;
int fountainFrameIndex = 0;
float fountainAnimationTime = 0.0f;
const float fountainFrameDuration = 0.2f;


int levelMap[GRID_ROWS][GRID_COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 8, 22, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 4, 0, 16, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 12, 18, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {22, 24, 23, 22, 6, 2, 2, 2, 2, 2, 8, 0, 17, 0, 0, 10, 0, 0, 0, 0, 0, 11, 0, 0, 3, 23, 24, 22, 15, 25, 22, 0, 0, 9, 0, 0, 23, 22, 24, 23},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void InitializeLevel(void) {
    tileImage = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_01.png");
    groundTile = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_04.png");
    boxImage = CP_Image_Load("Assets/Tiles/3 Objects/Other/Box.png");
    ladderImage = CP_Image_Load("Assets/Tiles/3 Objects/Other/Ladder1.png");
    fenceImage = CP_Image_Load("Assets/Tiles/3 Objects/Fence/6.png");
    brickTile = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_64.png");
    slopeTile = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_43.png");
    slopeTile2 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_42.png");
    ramp1 = CP_Image_Load("Assets/Tiles/3 Objects/Other/Ramp1.png");
    ramp2 = CP_Image_Load("Assets/Tiles/3 Objects/Other/Ramp2.png");

    fountainFrames[0] = CP_Image_Load("Assets/Tiles/4 Animated objects/00_Fountain.png");
    fountainFrames[1] = CP_Image_Load("Assets/Tiles/4 Animated objects/01_Fountain.png");
    fountainFrames[2] = CP_Image_Load("Assets/Tiles/4 Animated objects/02_Fountain.png");
    fountainFrames[3] = CP_Image_Load("Assets/Tiles/4 Animated objects/03_Fountain.png");

    bush1 = CP_Image_Load("Assets/Tiles/3 Objects/Bushes/17.png");
    bush2 = CP_Image_Load("Assets/Tiles/3 Objects/Bushes/18.png");
    bush3 = CP_Image_Load("Assets/Tiles/3 Objects/Bushes/19.png");
    bush4 = CP_Image_Load("Assets/Tiles/3 Objects/Bushes/20.png");
    bench1 = CP_Image_Load("Assets/Tiles/3 Objects/Benches/1.png");
    bench2 = CP_Image_Load("Assets/Tiles/3 Objects/Benches/4.png");
    tree3 = CP_Image_Load("Assets/Tiles/3 Objects/Other/Tree3.png");
    tree4 = CP_Image_Load("Assets/Tiles/3 Objects/Other/Tree4.png");
    Tree2 = CP_Image_Load("Assets/Tiles/3 Objects/Other/Tree2.png");
    stone6 = CP_Image_Load("Assets/Tiles/3 Objects/Stones/6.png");
    grass1 = CP_Image_Load("Assets/Tiles/3 Objects/Grass/1.png");
    grass2 = CP_Image_Load("Assets/Tiles/3 Objects/Grass/2.png");
    grass3 = CP_Image_Load("Assets/Tiles/3 Objects/Grass/3.png");
    grass4 = CP_Image_Load("Assets/Tiles/3 Objects/Grass/4.png");
    grass5 = CP_Image_Load("Assets/Tiles/3 Objects/Grass/5.png");
}

void UpdateFountainAnimation(void) {
    fountainAnimationTime += CP_System_GetDt(); 

    if (fountainAnimationTime >= fountainFrameDuration) {
        fountainAnimationTime = 0; 
        fountainFrameIndex = (fountainFrameIndex + 1) % 4; 
    }
}

void DrawLevel(void) {
    // First pass: Draw background elements (ground, tiles, fences, etc.)
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;

            switch (levelMap[row][col]) {
            case 1: CP_Image_Draw(groundTile, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 2: CP_Image_Draw(tileImage, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 3: CP_Image_Draw(ladderImage, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 4: CP_Image_Draw(fenceImage, x, y, TILE_SIZE * 3, TILE_SIZE * 3, 255); break; // Draw fences first
            case 5: CP_Image_Draw(boxImage, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 6: CP_Image_Draw(slopeTile, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 7: CP_Image_Draw(brickTile, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 8: CP_Image_Draw(slopeTile2, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            }
        }
    }

    // Second pass: Draw foreground objects (fountain, trees, bushes, benches)
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;

            switch (levelMap[row][col]) {
            case 9:
                CP_Image_Draw(fountainFrames[fountainFrameIndex], x, 825, 200, 200, 255);
                break;
            case 10: CP_Image_Draw(ramp1, x, 825, 200, 200, 255); break;
            case 11: CP_Image_Draw(ramp2, x, 825, 200, 200, 255); break;
            case 12: CP_Image_Draw(bush1, x, 855, 65, 45, 255); break;
            case 13: CP_Image_Draw(bush2, x, 855, 65, 45, 255); break;
            case 14: CP_Image_Draw(bush3, x, 855, 65, 45, 255); break;
            case 15: CP_Image_Draw(bush4, x, 900, 65, 45, 255); break;
            case 16: CP_Image_Draw(bench1, x, y, 65, 45, 255); break;
            case 17: CP_Image_Draw(bench2, x, 910, 45, 35, 255); break;
            case 18: CP_Image_Draw(tree3, x, 675, 400, 400, 255); break;
            case 19: CP_Image_Draw(tree4, x, 275, 400, 400, 255); break; 
            case 20: CP_Image_Draw(Tree2, x, 275, 400, 400, 255); break;
            case 21: CP_Image_Draw(stone6, x, 100, 150, 150, 255); break;
            case 22: CP_Image_Draw(grass1, x, y + 15, 20, 25, 255); break;
            case 23: CP_Image_Draw(grass2, x, y + 15, 20, 25, 255); break;
            case 24: CP_Image_Draw(grass3, x, y + 15, 20, 25, 255); break;
            case 25: CP_Image_Draw(grass4, x, y + 15, 20, 25, 255); break;
            case 26: CP_Image_Draw(grass5, x, y + 15, 20, 25, 255); break;
            }
        }
    }
}

void MainGameLoop(void) {
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255)); 
    UpdateFountainAnimation();
    DrawLevel();
}

void Level_Exit(void) {
    CP_Image_Free(tileImage);
    CP_Image_Free(boxImage);
    CP_Image_Free(ladderImage);
    CP_Image_Free(fenceImage);
    for (int i = 0; i < 4; i++) {
        CP_Image_Free(fountainFrames[i]);
    }
}
