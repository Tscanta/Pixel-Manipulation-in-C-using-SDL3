// Initializing the SDL library
#include <SDL3/SDL.h>
SDL_Init(SDL_INIT_VIDEO)

// Create the Window
SDL_Window *window = SDL_CreateWindow();

// Render the Window
SDL_Renderer *renderer = SDL_CreateRenderer();

// Add the texture
SDL_Texture *texture = SDL_CreateTexture();

// Creating the framebuffer
uint32_t framebuffer[320*220]; // The frame is of aspect ratio 320x220

// Manipulating the framebuffer
framebuffer[0] 0x00FF00;

// Update then display
SDL_UpdateTexture(texture, framebuffer);

SDL_RenderClear(renderer);
SDL_RenderTexture(renderer, texture);
SDL_RenderPresent(renderer);