#include "player.h"
#include <stdio.h>
#include "level.h"

extern int* levelMap;  // Access levelMap from level.c

void Player_Init(Player* player) {
    player->frames[0] = CP_Image_Load("Assets/00_Walk.png");
    player->frames[1] = CP_Image_Load("Assets/01_Walk.png");
    player->frames[2] = CP_Image_Load("Assets/02_Walk.png");
    player->frames[3] = CP_Image_Load("Assets/03_Walk.png");
    player->frames[4] = CP_Image_Load("Assets/04_Walk.png");
    player->frames[5] = CP_Image_Load("Assets/05_Walk.png");
    player->frames[6] = CP_Image_Load("Assets/06_Walk.png");
    player->frames[7] = CP_Image_Load("Assets/07_Walk.png");

    player->x = 160.0f;
    player->y = 164.0f;
    player->frameTimer = 0.0f;
    player->currentFrame = 0;
    player->isMoving = 0;
    player->facingRight = 1;
    player->velocityY = 0.0f;
    player->isJumping = 0;
}

int CheckCollision(Player* player, float newX, float newY) {
    // Player bounding box (assuming origin is top-left)
    int leftTile = (int)(newX / TILE_SIZE);
    int rightTile = (int)((newX + PLAYER_WIDTH - 1) / TILE_SIZE);
    int topTile = (int)(newY / TILE_SIZE);
    int bottomTile = (int)((newY + PLAYER_HEIGHT - 1) / TILE_SIZE);

    // Clamp to level bounds
    if (leftTile < 0 || rightTile >= GRID_COLS || topTile < 0 || bottomTile >= GRID_ROWS) {
        return 1;  // Out of bounds
    }

    // Check tiles (1 and 14 are solid in your JSON)
    for (int row = topTile; row <= bottomTile; row++) {
        for (int col = leftTile; col <= rightTile; col++) {
            // Ensure we don't access out-of-bounds memory
            if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS) {
                int tileID = levelMap[row * GRID_COLS + col];
                if (tileID == 1 || tileID == 14) {  // Solid tiles
                    return 1;
                }
            }
        }
    }
    return 0;  // No collision
}

void Player_Update(Player* player, float deltaTime) {
    player->isMoving = 0;
    float newX = player->x;
    float newY = player->y;

    // Horizontal movement
    if (CP_Input_KeyDown(KEY_A)) {
        newX -= PLAYER_SPEED * deltaTime;
        player->isMoving = 1;
        player->facingRight = 0;
    }
    if (CP_Input_KeyDown(KEY_D)) {
        newX += PLAYER_SPEED * deltaTime;
        player->isMoving = 1;
        player->facingRight = 1;
    }

    // Jumping
    if (CP_Input_KeyTriggered(KEY_SPACE) && !player->isJumping) {
        player->velocityY = JUMP_POWER;
        player->isJumping = 1;
    }

    // Apply gravity
    player->velocityY += GRAVITY * deltaTime;
    newY += player->velocityY * deltaTime;

    // Horizontal collision check
    if (!CheckCollision(player, newX, player->y)) {
        player->x = newX;  // Update X if no collision
    } else {
        // Snap to nearest tile boundary
        if (newX < player->x) {  // Moving left
            player->x = (float)((int)((player->x + PLAYER_WIDTH) / TILE_SIZE)) * TILE_SIZE - PLAYER_WIDTH;
        } else {  // Moving right
            player->x = (float)((int)(newX / TILE_SIZE)) * TILE_SIZE;
        }
    }

    // Vertical collision check
    if (!CheckCollision(player, player->x, newY)) {
        player->y = newY;  // Update Y if no collision
    } else {
        if (player->velocityY > 0) {  // Falling and hit ground
            player->y = (float)((int)(newY / TILE_SIZE)) * TILE_SIZE;  // Snap to tile top
            player->velocityY = 0.0f;
            player->isJumping = 0;  // Landed
        } else if (player->velocityY < 0) {  // Jumping and hit ceiling
            player->y = (float)((int)((newY + PLAYER_HEIGHT) / TILE_SIZE)) * TILE_SIZE - PLAYER_HEIGHT;
            player->velocityY = 0.0f;
        }
    }

    // Animation
    if (player->isMoving) {
        player->frameTimer += deltaTime;
        if (player->frameTimer >= FRAME_TIME) {
            player->frameTimer = 0.0f;
            player->currentFrame = (player->currentFrame + 1) % FRAME_COUNT;
        }
    } else {
        player->currentFrame = 0;  // Idle frame
    }

    // Keep player in bounds
    if (player->x < 0) player->x = 0;
    if (player->x + PLAYER_WIDTH > SCREEN_WIDTH) player->x = SCREEN_WIDTH - PLAYER_WIDTH;
    if (player->y < 0) player->y = 0;
    if (player->y + PLAYER_HEIGHT > SCREEN_HEIGHT) {
        player->y = SCREEN_HEIGHT - PLAYER_HEIGHT;
        player->velocityY = 0.0f;
        player->isJumping = 0;
    }
}

void Player_Draw(Player* player) {
    float imageWidth = player->facingRight ? PLAYER_WIDTH : -PLAYER_WIDTH;
    CP_Image_Draw(player->frames[player->currentFrame],
                  player->x, player->y,
                  imageWidth, PLAYER_HEIGHT, 255);
}

void Player_Free(Player* player) {
    for (int i = 0; i < FRAME_COUNT; i++) {
        CP_Image_Free(&player->frames[i]);
    }
}