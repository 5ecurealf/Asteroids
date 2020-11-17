#include <SDL.h>
#include <stdio.h>
#include <memory>
#include <iostream>

#include "drawer.h"
#include "game.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    const int width = 800;
    const int height = 600;

    auto window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
                                                  "Asteroids",
                                                  SDL_WINDOWPOS_UNDEFINED,
                                                  SDL_WINDOWPOS_UNDEFINED,
                                                  width,
                                                  height,
                                                  SDL_WINDOW_SHOWN),
                                              SDL_DestroyWindow);

    if (window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    auto renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE),
        SDL_DestroyRenderer);

    Drawer drawer(window, renderer);
    Game game(drawer, width, height);

    float lastFrame = (float)SDL_GetTicks() * 0.001f;
    bool running = true;
    while (running)
    {
        SDL_Event event;                        // handles the quit event 
        while (SDL_PollEvent(&event))
        {
            running = event.type != SDL_QUIT;   // run the while loop until we get a quit event
        }

        float currentFrame = (float)SDL_GetTicks() * 0.001f;    
        float elapsedTime = currentFrame - lastFrame;           //tells me how long it takes to render the image 

        SDL_RenderClear(renderer.get());                        //???????           

        game.Update(elapsedTime);
        game.Draw();

        SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
        SDL_RenderPresent(renderer.get());

        lastFrame = currentFrame;

        // Cap to 60 FPS
        SDL_Delay((16.666f - elapsedTime));
    }
    SDL_Quit();

    return 0;
}
