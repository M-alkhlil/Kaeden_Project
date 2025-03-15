#include "cprocessing.h"
#include "splashscreen.h"
#include "mainmenu.h"
#include <stdbool.h>
#include <stdlib.h>

static CP_Image g_digipenLogo = NULL;
static CP_Image Splash_screen = NULL;
static CP_Image menuBackground = NULL;

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_PADDING 40

typedef enum {
	BUTTON_START,
	BUTTON_OPTIONS,
	BUTTON_EXIT
}ButtonType;

void DrawButton(float x, float y, const char* text);

enum SplashScreenState g_splashScreenState = DIGIPENLOGO;

void InitializeSplashScreen(void) {
	g_digipenLogo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	Splash_screen = CP_Image_Load("Assets/splash-screen.png");
}

void UpdateSplashScreen(void) {
	if (CP_Input_KeyTriggered(KEY_ANY) || CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		g_splashScreenState++;
	}


	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	switch (g_splashScreenState) {
	case DIGIPENLOGO:
		CP_Image_Draw(g_digipenLogo,
			CP_System_GetWindowHeight() / 2.0f,
			CP_System_GetWindowWidth() / 2.0f,
			762.5f, 222.5f, 255);

		break;

	case SPLASH_SCREEN:
		CP_Image_Draw(Splash_screen,
			CP_System_GetWindowHeight() / 2.0f,
			CP_System_GetWindowWidth() / 2.0f,
			512.f, 512.f, 255);

		break;

	default:
		CP_Engine_SetNextGameState(InitializeMainMenu, UpdateMainMenu, ExitMainMenu);
		break;
	}
}
void ExitSplashScreen(void) {
	CP_Image_Free(&g_digipenLogo);
	CP_Image_Free(&Splash_screen);
}

void InitializeMainMenu(void) {
	menuBackground = CP_Image_Load("Assets/Background_Menu_NoClouds.png");
}

void UpdateMainMenu(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (menuBackground != NULL) {
		CP_Image_Draw(menuBackground,
			CP_System_GetWindowHeight() / 2.0f,
			CP_System_GetWindowWidth() / 2.0f,
			CP_System_GetWindowHeight(),
			CP_System_GetWindowWidth(),
			255);
	}

	float centerX = CP_System_GetWindowWidth() / 2.0f;
	float startY = CP_System_GetWindowHeight() / 2.0f - (BUTTON_HEIGHT + BUTTON_PADDING) * 1.5f;

	DrawButton(centerX - BUTTON_WIDTH / 2, startY, "Start Game");
	DrawButton(centerX - BUTTON_WIDTH / 2, startY + BUTTON_HEIGHT + BUTTON_PADDING, "Options");
	DrawButton(centerX - BUTTON_WIDTH / 2, startY + 2 * (BUTTON_HEIGHT + BUTTON_PADDING), "Exit");
}

void ExitMainMenu(void) {
	CP_Image_Free(&menuBackground);
}

void DrawButton(float x, float y, const char* text) {
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
	CP_Graphics_DrawRect(x, y, BUTTON_WIDTH, BUTTON_HEIGHT);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(text, x + BUTTON_WIDTH / 2 - strlen(text) * 4, y + BUTTON_HEIGHT / 2 - 8);
}