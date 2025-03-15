#include "player.h"

void Player_Init(Player* player ,float startX, float startY) {

	player -> frames[0] = CP_Image_Load("Assets/00_Walk.png");
	player -> frames[1] = CP_Image_Load("Assets/01_Walk.png");
	player -> frames[2] = CP_Image_Load("Assets/02_Walk.png");
	player -> frames[3] = CP_Image_Load("Assets/03_Walk.png");
	player -> frames[4] = CP_Image_Load("Assets/04_Walk.png");
	player -> frames[5] = CP_Image_Load("Assets/05_Walk.png");
	player -> frames[6] = CP_Image_Load("Assets/06_Walk.png");
	player -> frames[7] = CP_Image_Load("Assets/07_Walk.png");

	player -> x = startX;
	player -> y = startY;
	player -> frameTimer = 0.0f;
	player -> currentFrame = 0;
	player -> isMovingRight = 0;
	player -> facingRight = 1;

	player -> velocityY = 0.0f;
	player -> isJumping = 0;
}

void Player_Update(Player* player, float deltaTime) {
	player->isMovingRight = 0;

	if (CP_Input_KeyDown(KEY_A)) {
		player -> x -= PLAYER_SPEED * deltaTime;
		player -> isMovingRight = 1;
		player -> facingRight = 0;
	}

	if (CP_Input_KeyDown(KEY_D)) {
		player -> x += PLAYER_SPEED * deltaTime;
		player -> isMovingRight = 1;
		player -> facingRight = 1;
	}

	if (CP_Input_KeyTriggered(KEY_SPACE) && !player -> isJumping) {
		player -> velocityY = JUMP_POWER;
		player -> isJumping = 1;
	}


	player -> velocityY += GRAVITY * deltaTime;
	player -> y += player -> velocityY * deltaTime;

	if (player -> isMovingRight)
	{
		player -> frameTimer += deltaTime;
		if (player -> frameTimer >= FRAME_TIME) {
			player -> frameTimer = 0.0f;
			player -> currentFrame = (player -> currentFrame + 1) % FRAME_COUNT;
		}
	}
	else {
		player -> currentFrame = 0;
	}
	/*m.alkhlil */
	// Define the ground level where the player should land.
// Set the ground level to match the background's floor position

	/*m.alkhlil */
	// Ensure the player doesn't fall below the ground level
	if (player->y >= groundLevel) {
		player->y = groundLevel;
		player->velocityY = 0.0f;
		player->isJumping = 0;
	}


}

void Player_Draw(Player* player) {
	float imageWidth = player -> facingRight ? 200 : -200;
	CP_Image_Draw(player -> frames[player -> currentFrame],
		player -> x, player -> y,
		imageWidth, 200, 255);
}

