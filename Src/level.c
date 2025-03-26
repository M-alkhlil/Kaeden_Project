#include "level.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Individual tile images
CP_Image tile_01, tile_02, tile_03, tile_13, tile_14;
// Foreground object images
CP_Image fountainFrames[4], bush1, bush2, bush3, bush4, bench1, bench2, tree4, tree3, Tree2, stone6, grass1, grass2, grass3, grass4, grass5;
int fountainFrameIndex = 0;
float fountainAnimationTime = 0.0f;
const float fountainFrameDuration = 0.2f;

// Dynamic tilemap data
int* levelMap = NULL;

void LoadJSONMap(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* jsonString = (char*)malloc(fileSize + 1);
    fread(jsonString, 1, fileSize, file);
    jsonString[fileSize] = '\0';
    fclose(file);

    cJSON* json = cJSON_Parse(jsonString);
    if (!json) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        free(jsonString);
        return;
    }

    cJSON* layers = cJSON_GetObjectItem(json, "layers");
    if (!layers || !cJSON_IsArray(layers)) {
        printf("No layers found in JSON\n");
        cJSON_Delete(json);
        free(jsonString);
        return;
    }

    cJSON* layer = cJSON_GetArrayItem(layers, 0);
    cJSON* data = cJSON_GetObjectItem(layer, "data");
    if (!data || !cJSON_IsArray(data)) {
        printf("No data array found in layer\n");
        cJSON_Delete(json);
        free(jsonString);
        return;
    }

    int dataSize = cJSON_GetArraySize(data);
    if (dataSize != GRID_ROWS * GRID_COLS) {
        printf("Data size mismatch: expected %d, got %d\n", GRID_ROWS * GRID_COLS, dataSize);
        cJSON_Delete(json);
        free(jsonString);
        return;
    }

    levelMap = (int*)malloc(dataSize * sizeof(int));
    for (int i = 0; i < dataSize; i++) {
        cJSON* tile = cJSON_GetArrayItem(data, i);
        levelMap[i] = tile->valueint;
    }

    cJSON_Delete(json);
    free(jsonString);
}

void InitializeLevel(void) {
    // Load individual tile images based on JSON tile IDs
    tile_01 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_01.png"); // ID 1 (grass or ground)
    tile_14 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_14.png"); // ID 14 (path or platform)

    // Optional: Load other tiles if you plan to expand the JSON later
    tile_02 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_02.png"); // ID 2
    tile_03 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_03.png"); // ID 3
    tile_13 = CP_Image_Load("Assets/Tiles/1 Tiles/Tile_13.png"); // ID 13

    // Load foreground object images (if used later)
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

    // Load the JSON map
    LoadJSONMap("Assets/map.json"); // Adjust path as needed
}

void UpdateFountainAnimation(void) {
    fountainAnimationTime += CP_System_GetDt();
    if (fountainAnimationTime >= fountainFrameDuration) {
        fountainAnimationTime = 0;
        fountainFrameIndex = (fountainFrameIndex + 1) % 4;
    }
}

void DrawLevel(void) {
    if (!levelMap) {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
        return;
    }

    CP_Graphics_ClearBackground(CP_Color_Create(135, 206, 235, 255)); // Sky blue background

    // Draw background tiles from JSON
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;
            int tileID = levelMap[row * GRID_COLS + col];

            switch (tileID) {
            case 1: CP_Image_Draw(tile_01, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 2: CP_Image_Draw(tile_02, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 3: CP_Image_Draw(tile_03, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 13: CP_Image_Draw(tile_13, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            case 14: CP_Image_Draw(tile_14, x, y, TILE_SIZE, TILE_SIZE, 255); break;
            }
        }
    }

    // Optional: Draw foreground objects (manually placed)
    /*
    CP_Image_Draw(fountainFrames[fountainFrameIndex], 500, 825, 200, 200, 255); // Fountain
    CP_Image_Draw(bush1, 600, 855, 65, 45, 255); // Bush 1
    CP_Image_Draw(bush2, 700, 855, 65, 45, 255); // Bush 2
    CP_Image_Draw(bush3, 800, 855, 65, 45, 255); // Bush 3
    CP_Image_Draw(bush4, 900, 900, 65, 45, 255); // Bush 4
    CP_Image_Draw(bench1, 1000, 900, 65, 45, 255); // Bench 1
    CP_Image_Draw(bench2, 1100, 910, 45, 35, 255); // Bench 2
    CP_Image_Draw(tree3, 1200, 675, 400, 400, 255); // Tree 3
    CP_Image_Draw(tree4, 1400, 275, 400, 400, 255); // Tree 4
    CP_Image_Draw(Tree2, 1600, 275, 400, 400, 255); // Tree 2
    CP_Image_Draw(stone6, 300, 100, 150, 150, 255); // Stone
    CP_Image_Draw(grass1, 400, 1015, 20, 25, 255); // Grass 1
    CP_Image_Draw(grass2, 450, 1015, 20, 25, 255); // Grass 2
    CP_Image_Draw(grass3, 500, 1015, 20, 25, 255); // Grass 3
    CP_Image_Draw(grass4, 550, 1015, 20, 25, 255); // Grass 4
    CP_Image_Draw(grass5, 600, 1015, 20, 25, 255); // Grass 5
    */
}

void MainGameLoop(void) {
    UpdateFountainAnimation();
    DrawLevel();
}

void Level_Exit(void) {
    // Free tile images
    CP_Image_Free(&tile_01);
    CP_Image_Free(&tile_02);
    CP_Image_Free(&tile_03);
    CP_Image_Free(&tile_13);
    CP_Image_Free(&tile_14);

    // Free foreground object images
    for (int i = 0; i < 4; i++) {
        CP_Image_Free(&fountainFrames[i]);
    }
    CP_Image_Free(&bush1);
    CP_Image_Free(&bush2);
    CP_Image_Free(&bush3);
    CP_Image_Free(&bush4);
    CP_Image_Free(&bench1);
    CP_Image_Free(&bench2);
    CP_Image_Free(&tree3);
    CP_Image_Free(&tree4);
    CP_Image_Free(&Tree2);
    CP_Image_Free(&stone6);
    CP_Image_Free(&grass1);
    CP_Image_Free(&grass2);
    CP_Image_Free(&grass3);
    CP_Image_Free(&grass4);
    CP_Image_Free(&grass5);

    // Free dynamic levelMap
    if (levelMap) {
        free(levelMap);
        levelMap = NULL;
    }
}