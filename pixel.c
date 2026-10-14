#include <stdio.h> 
#include <stdlib.h> // ---> for the EXIT_SUCCESS
#include <SDL3/SDL.h> 
#include <stdint.h> // ---> For the unsigned integer

#define WIDTH 1240
#define HEIGHT 730

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

    uint8_t is_running = 1;
    SDL_Event event;

    while(is_running)
    {
        //Poll the events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                is_running = 0;
            }
        }

        // Displaying the window
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    printf("Window Generated Successfully");

    SDL_Quit();

    return EXIT_SUCCESS;
}