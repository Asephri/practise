/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Headers. */
#include "common.h"
#include "draw.h"
#include "entities.h"
#include "player.h"
#include "stage.h"

extern App   app;
extern Stage stage;

static void logic(void);
static void draw(void);

static SDL_Texture *mousetargetTexture;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	stage.entityTail = &stage.entityHead;

	mousetargetTexture = loadTexture("gfx/mousetarget.png");

	initPlayer();
}

static void logic(void)
{
	doPlayer();

	doEntities();
}

static void draw(void)
{
	drawEntities();

	blit(mousetargetTexture, app.mouse.x, app.mouse.y, 1);
}
