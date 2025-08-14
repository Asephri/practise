/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Headers. */
#include "common.h"
#include "draw.h"
#include "player.h"
#include "input.h"
#include "util.h"

/* Externs. */
extern App app;
extern Entity *player;
extern Entity *playertank;
extern Stage stage;

/* Initialisng the player. */
void initPlayer(void)
{
    // Console message.
    printf("Intialising the player.\n");
    // Assiging memory blocks.
    playertank = malloc(sizeof(Entity));
    memset(playertank, 0, sizeof(Entity));
    // Add playertank to linked list in stage.
    stage.entityTail->next = playertank;
    stage.entityTail = playertank;

    // Assiging memory blocks.
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    // Add player to linked list in stage.
    stage.entityTail->next = player;
    stage.entityTail = player;
    
    // Player variables.
    playertank->texture = loadTexture("gfx/tank.png");
    player->texture = loadTexture("gfx/playerturret.png");
    player->health = 5;

    playertank->x = SCREEN_WIDTH / 2;
    playertank->y = SCREEN_HEIGHT / 2;
    player->x = playertank->x;
    player->y = playertank->y;

    // Query player texture.
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    SDL_QueryTexture(playertank->texture, NULL, NULL, &playertank->w, &playertank->h);
    // Console message.
    printf("Successful.\n");
}

/* Player behaviour. */
void doPlayer(void)
{
    // Decelerating the player by multiplying = smoother movement.
    playertank->dx *= 0.86;
    playertank->dy *= 0.86;

    // Forward
    if (app.keyboard[SDL_SCANCODE_W])
    {   
        double angle_rad = playertank->angle * PI / 180;
        playertank->dx = PLAYER_SPEED * cos(angle_rad);
        playertank->dy = PLAYER_SPEED * sin(angle_rad);
    }

    // Reverse (if needed)
    if (app.keyboard[SDL_SCANCODE_S])
    {
        double angle_rad = playertank->angle * PI / 180;
        playertank->dx = -PLAYER_SPEED * cos(angle_rad) / 4;
        playertank->dy = -PLAYER_SPEED * sin(angle_rad) / 4;
    }

    // Rotation using A and D keys.
    if (app.keyboard[SDL_SCANCODE_A])
    {   
        // Ensure the angle stays within the range of 0 to 359 degrees.
        playertank->angle = playertank->angle - ROTATION_ANGLE_SPEED;
    }
    else if (app.keyboard[SDL_SCANCODE_D])
    {
        playertank->angle = playertank->angle + ROTATION_ANGLE_SPEED;
    }

    // Update the tank's position
    playertank->x += playertank->dx;
    playertank->y += playertank->dy;

    // Update the tank's turret position.
    player->x = playertank->x + (playertank->w - player->w) / 2.0;
    player->y = playertank->y + (playertank->h - player->h) / 2.0;

    // Have the turret track the player's mouse.
    player->angle = getAngle(player->x, player->y, app.mouse.x, app.mouse.y);
}