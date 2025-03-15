#include <stdlib.h>
#include "game.h"
#include "cprocessing.h"
#include "splashscreen.h"
#include "mainmenu.h"

int main(void)
{
	CP_System_SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	CP_System_SetFrameRate(60.0f);

	CP_Engine_SetNextGameState(InitializeSplashScreen, UpdateSplashScreen, ExitSplashScreen);
	CP_Engine_Run();
	return 0;
}
