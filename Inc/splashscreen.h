 

#include "cprocessing.h"

enum SplashScreenState
{
    DIGIPENLOGO,     // State for displaying the DigiPen logo
    SPLASH_SCREEN,   // State for displaying the studio logo
};

/// Initializes the splash screen state.

void InitializeSplashScreen(void);
// Updates the splash screen state. 
//Handles transitions between logos and to the main menu.
void UpdateSplashScreen(void);
/// Cleans up resources used by the splash screen (e.g., freeing images).

void ExitSplashScreen(void);

 