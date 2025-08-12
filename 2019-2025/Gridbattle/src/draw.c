/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Libraries. */
#include <SDL2/SDL_image.h>

/* Headers. */
#include "common.h"
#include "draw.h"

/* Externs. */
extern App app;

/* Preparing the renderer. */
void prepareScene(void)
{
    // Console message.
    //printf("Preparing the Renderer.\n");
    // Overall drawcolour.
    SDL_SetRenderDrawColor(app.renderer, 0,255,0,255);
    SDL_RenderClear(app.renderer);
    // Console Message.
    //printf("Successful.\n");
}

/* Presenting the renderer. */
void presentScene(void)
{
    //printf("Presenting the renderer.\n");
    SDL_RenderPresent(app.renderer);
    //printf("Successful.\n");
}

/* Get a texture from the texture cache. */
static SDL_Texture *getTexture(char *name)
{
    printf("Getting Textures\n");

    Texture *t;

    for (t = app.textureHead.next; t !=NULL; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }
    return NULL;
    printf("Successful.\n");
}

/* add Textures from cache. */
static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
    // Console message.
    printf("Adding Textures to cache.\n");
    Texture *texture;

    printf("Assigning memory blocks.\n");
    texture = malloc(sizeof(Texture));
    memset(texture, 0, sizeof(Texture));
    app.textureTail->next = texture;
    app.textureTail = texture;

    STRNCPY(texture->name, name, MAX_NAME_LENGTH);
    texture->texture = sdlTexture;
    printf("Successful.\n");
}

/* Load Textures. */
SDL_Texture *loadTexture(char *filename)
{
    // Console message.
    //printf("Loading Textures.\n");
    SDL_Texture *texture;

    texture = getTexture(filename);

    if (texture == NULL)
    {
        // SDL Error Message.
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s...", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
        addTextureToCache(filename, texture);
    }
    return texture;
    //printf("Successful.\n");
}

/* Blit function for Textures. */
void blit(SDL_Texture *texture, int x, int y, int center)
{
    // Console message.
    //printf("Applying Textures.\n");
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    // Query Texture
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    if (center)
    {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }
    // Apply Texture.
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
    //printf("Successful.\n");
}

/* Create rectangle for texture. */
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}

/* Rotate texture. */
void blitRotated(SDL_Texture *texture, int x, int y, float angle)
{
    SDL_Rect dstRect;

    dstRect.x = x; // Where to draw.
    dstRect.y = y; // Where to draw at y.
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
    dstRect.x -= (dstRect.w / 2); // Shift texture by half width.
    dstRect.y -= (dstRect.h / 2);// Shift texture by half height.

    SDL_RenderCopyEx(app.renderer, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
}