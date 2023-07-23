#include <iostream>
#include <complex>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>

#include "../libs/mandelbrot.hxx"

const unsigned int HEIGHT = 1000;
const unsigned int WIDTH = 1000;
const unsigned int ITERATIONS = 20;
const unsigned int THRESHOLD = 10;

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mandelbrot visualizer");
    SDL_SetWindowMaximumSize(window, WIDTH, HEIGHT);

    Record2DArray grid = get_map(HEIGHT, WIDTH, C(-2, -2), C(2, 2));

    for (int x = 0; x < HEIGHT; x++) { // rows
        for (int y = 0; y < WIDTH; y++) { //columns

            grid[x][y].iters = is_in_set(grid[x][y].z, ITERATIONS, THRESHOLD);

            if (grid[x][y].iters == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
            } else {
                SDL_SetRenderDrawColor(renderer, 
                    std::lerp(255, 0, 1/double(grid[x][y].iters)), 
                0, 0, 1);
            }

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    
    SDL_RenderPresent(renderer);
    
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while(SDL_PollEvent( &e )) {
            if ( e.type == SDL_QUIT )
                quit = !quit; 
        }
    }

    grid.clear();
    grid.shrink_to_fit();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}