/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Application Window Settings. */
#define APP_NAME "Gridbattle!"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

// Max name length for interal reads ect
#define MAX_NAME_LENGTH 32
// Max keyboard keys available.
#define MAX_KEYBOARD_KEYS 350
// Max mouse buttons available.
#define MAX_MOUSE_BUTTONS 6
// Max Sound channels available.
#define MAX_SND_CHANNELS 16


/* Texture defines. */
// Texture STRNCPY
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

/* Game logic defines. */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define PI 3.14159265358979323846

// Player Defines.
#define PLAYER_SPEED 2
#define ROTATION_ANGLE_SPEED 1