#include "player.h"
#include "game.h"



CP_Image background;
Player player;
CP_Sound overworld, menuInteract;

void StartGame(void) {
	
	CP_Engine_SetNextGameState(InitializeGame, UpdateGame, ExitGame);
	CP_Sound_StopGroup(CP_SOUND_GROUP_0);
	
}

void InitializeGame(void) {
	CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	CP_System_SetFrameRate(60);

	background = CP_Image_Load("Assets/Tiles/2 Background/Day/Background.png");

	overworld = CP_Sound_Load("Assets/Katz Theme - Extended Version.mp3");
	

	CP_Sound_PlayAdvanced(overworld, 0.3, 1, 1, CP_SOUND_GROUP_0);

	/*m.alkhlil */
	// Initialize the player at (100, groundLevel) to start on the ground and avoid unnecessary falling

	Player_Init(&player,100,groundLevel);

	InitializeLevel();
}

void UpdateGame(void) {

	/*m.alkhlil */

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	// Draw the background image centered on the screen
	CP_Image_Draw(background, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0, SCREEN_WIDTH, SCREEN_HEIGHT, 255);
	// Draw the level before drawing the player
	DrawLevel();

	float deltaTime = CP_System_GetDt();
	Player_Update(&player, deltaTime);
	// Draw the player on top of the level
	Player_Draw(&player);

	
}

void ExitGame(void) {
	CP_Image_Free(&background);
	for (int i = 0; i < FRAME_COUNT; i++) {
		CP_Image_Free(&player.frames[i]);
	}
}
