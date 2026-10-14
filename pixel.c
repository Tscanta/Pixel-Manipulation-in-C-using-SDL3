#include <stdio.h> 
#include <stdlib.h> // ---> for the EXIT_SUCCESS
#include <SDL3/SDL.h> 
#include <stdint.h> // ---> For the unsigned integer

#define WIDTH 320
#define HEIGHT 220

uint32_t framebuffer[WIDTH * HEIGHT];
const double target_frame = 1.0/60.0; // --> 0.016

// Easier way to enter colors into the window
void put_pixel(int x, int y, uint32_t color)
{
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        return;
    }
    framebuffer [WIDTH * y + x] = color;
}

// Clears the FrameBuffer
void clear(uint32_t color)
{
    for(int i=0;i<WIDTH*HEIGHT;i++)
    {
        framebuffer[i] = color;
    }
}

int main()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf (stderr, "SDL INIT FAILED: %S \n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Creating the window
    SDL_Window *window = SDL_CreateWindow(
        "SDL Frame Buffer",
        WIDTH * 4, // Strectching the contents of the window
        HEIGHT * 4, 
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
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH,
        HEIGHT
    );

    // Error Handling 
    if(window == NULL)
    {
        fprintf (stderr, "SDL CreateWindow() FAILED: %S \n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(renderer == NULL)
    {
        fprintf (stderr, "SDL CreateRenderer() FAILED: %S \n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if(texture == NULL)
    {
        fprintf (stderr, "SDL CreateTexture() FAILED: %S \n", SDL_GetError());
        return EXIT_FAILURE;
    }
    

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    uint8_t is_running = 1;
    SDL_Event event;

    while(is_running)
    {
        uint64_t start = SDL_GetPerformanceCounter(); // Returns ticks per second for the performance

        //Poll the events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                is_running = 0;
            }
        }

        clear(0xFFFFFF);

        // FrameBuffer Manipulation
        /*put_pixel(WIDTH/2, HEIGHT/2, 0x00FF00); // Putting Green color at the center of the window */
 
        for(int y=0; y<HEIGHT; y++)
        {
            for(int x=0; x<WIDTH; x++)
            {
                if(x%8==0 && y%8==0)
                {
                    put_pixel(x,y,0x000000);
                }
            }
        }

        // Updating the texture - Copy the contents of the framebuffer to the texture
        SDL_UpdateTexture(
            texture,
            NULL,
            framebuffer,
            WIDTH * sizeof(uint32_t) // Pitch --> the width of the image/texture in bytes
        ); 

        // Displaying the window
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        uint64_t end = SDL_GetPerformanceCounter();
        double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

        // Cap the framerate to 60fps
        if(elapsed < target_frame)
        {
            SDL_Delay((target_frame - elapsed) * 1000.0); // This will sleep until we reach the target fps of 60fps
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    printf("Window Generated Successfully");

    SDL_Quit();

    return EXIT_SUCCESS;
}