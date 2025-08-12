/*
Copyright (C) 2023-2024 Asephri. All rights reserved.
*/

/* Type definitions for structures. */
typedef struct Texture Texture;
typedef struct Entity Entity;

/* App delegation structure.*/
typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

/* Texture structure. */
struct Texture
{
    char name[MAX_NAME_LENGTH];
    SDL_Texture *texture;
    Texture *next;
};

/* Mouse Reader structure.*/
typedef struct
{
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
} Mouse;

/* Entity struct. */
struct Entity
{
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int health;
    int angle;
    SDL_Texture *texture;
    Entity *next;
};

/* App structure. */
typedef struct 
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate; // App delegation.
    int keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse; // Reading the mouse.
    Texture textureHead, *textureTail;
} App;

/* Stage struct. */
typedef struct 
{
    Entity entityHead, *entityTail; // Holds linked list of entites.
} Stage;
