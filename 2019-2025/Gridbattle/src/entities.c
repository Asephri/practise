/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Headers. */
#include "common.h"
#include "draw.h"
#include "entities.h"

/* Externs. */
extern Entity *player;
extern Entity *playertank;
extern Stage stage;

/* Entity Creation. */
void doEntities(void)
{
    Entity *e;

    for (e = stage.entityHead.next; e != NULL; e = e->next)
    {
        // Motion. adding dx and dy to their x and y causing movement.
        e->x += e->dx;
        e->y += e->dy;

        
        if (e == playertank) 
        {   // Clipping player to screen.
            playertank->x = MIN(MAX(playertank->x, e->w/2), SCREEN_WIDTH - e->w/2);
            playertank->y = MIN(MAX(playertank->y, e->h/2), SCREEN_HEIGHT - e->h/2);
        }   
    }
}

/* Rendering Entities. */
void drawEntities(void)
{
    Entity *e;

    for (e = stage.entityHead.next; e != NULL; e = e->next)
    {   // Stepping through the list of entities and drawing them with their texture and positions. as well as angle.
        blitRotated(e->texture, e->x, e->y, e->angle);
    }
}