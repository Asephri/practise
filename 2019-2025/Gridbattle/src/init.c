/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Libraries. */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/* Headers. */
#include "common.h"
#include "init.h"

/* Externs. */
extern App app;

/*Intialise SDL.*/
void initSDL(void)
{
    int rendererFlags, windowFlags;
    // Use gpu if available.
    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    // INIT VIDEO
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialise SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // Set audio definition.
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialise SDL Mixer.\n");
        exit(1);
    }

    // Max audio channels.
    Mix_AllocateChannels(MAX_SND_CHANNELS);
    // Create window.
    app.window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    // Set render scale quality.
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // Create Renderer.
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    // Initialising SDL_IMAGE.
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    // If the system cursor is true or not.
    SDL_ShowCursor(0);
}

/* Intialise game. */
void initGame(void)
{
}

/* Intialise Cleanup. */
void cleanup(void)
{
    printf("Quitting Audio mixer.\n");
    Mix_Quit();
    printf("Quitting SDL_Image.\n");
    IMG_Quit();
    printf("Destroying the app renderer.\n");
    SDL_DestroyRenderer(app.renderer);
    printf("Destroying the app window\n");
    SDL_DestroyWindow(app.window);
    printf("Quitting the application.\n");
    SDL_Quit();
    printf("Successful.\n");
}