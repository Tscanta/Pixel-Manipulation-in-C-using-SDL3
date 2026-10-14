#include <stdio.h> 
#include <stdlib.h> // ---> for the EXIT_SUCCESS
#include <SDL3/SDL.h> 
#include <stdint.h> // ---> For the unsigned integer

#define WIDTH 320
#define HEIGHT 220

uint32_t framebuffer[WIDTH * HEIGHT];

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    // Creating the window
    SDL_Window *window = SDL_CreateWindow(
        "SDL Frame Buffer",
        WIDTH,
        HEIGHT,
        0
    );

    // Rendering the window
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        NULL
    );

    // Giving the window some texture
    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA64,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );

    // Displaying the window
    while(true)
    {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    printf("Window Generated Successfully");


    return EXIT_SUCCESS;
}