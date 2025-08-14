/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Headers. */
#include "common.h"
#include "input.h"

/* Externs. */
extern App app;

/* If A keyboard key is NOT pressed. */
static void doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}
}

/* If A keyboard key IS pressed. */
static void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

/* Game Input Reciever*/
void doInput(void)
{
    // Console Message.
    //printf("Calling doInput.\n");
    SDL_Event event;

    // While input is polled.
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT: // If the application is closed.
                printf("SDL_QUIT has been called! Closing application.\n");
                exit(0);
                break;
            case SDL_KEYDOWN: // If keydown is pressed.
                //printf("Keydown was pressed!\n");
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP: // If keydown isnt pressed.
                //printf("Keydown was released!\n");
                doKeyUp(&event.key);
                break;
            default: // Default outcome.
                //printf("default break was called in SDL_PollEvent\n");
                break;
        }
    }
    // Get Mouse location Information.
    SDL_GetMouseState(&app.mouse.x,&app.mouse.y);
}