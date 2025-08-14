/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Headers. */
#include "common.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "main.h"
#include "stage.h"

/* Externs. */
App app;
Entity *playertank;
Entity *player;
Stage stage;

/* Functions. */
static void capFrameRate(long *then, float *remainder);

/* Application Entry Point. */
int main(int argc, char *argv[])
{
	long  then;
	float remainder;

    // Redirect console messages to "consolelog.txt"
    freopen("consolelog.txt", "w", stdout);

	printf("----------------------------------------------------------------------------------------------------\n");

	printf("voidFighter - New Session\n");
	
	printf("Copyright (C) 2023-2024 Asephri. All rights reserved.\n");

	printf("consolelog.txt\n");
	
	printf("----------------------------------------------------------------------------------------------------\n");

    // Creating a memory block for the application
	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);

	initGame();

	initStage();

    // Frame rate control variables.
	then = SDL_GetTicks();
	remainder = 0;

    /* Main game loop */
	while (1)
	{
		prepareScene();

		doInput();

		app.delegate.logic();

		app.delegate.draw();

		presentScene();

		capFrameRate(&then, &remainder);
	}

	return 0;
}

/* Frame Rate Cap. */
static void capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;

    // Set the desired time interval between frames (60 FPS is approximately 16 milliseconds per frame).
    wait = 16 + *remainder;

    // Remove the fractional part of the remainder to ensure accurate time measurement.
    *remainder -= (int)*remainder;

    // Calculate the time elapsed since the last frame.
    frameTime = SDL_GetTicks() - *then;

    // Calculate the remaining time to wait before the next frame.
    wait -= frameTime;

    // Ensure there's a minimum wait time of 1 millisecond to avoid busy-waiting.
    if (wait < 1)
    {
        wait = 1;
    }

    // Delay execution for the calculated wait time.
    SDL_Delay(wait);

    // Increment the remainder to account for fractional time for the next frame.
    *remainder += 0.667;

    // Update the reference time for the next frame.
    *then = SDL_GetTicks();
}
