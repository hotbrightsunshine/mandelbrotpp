#include <iostream>
#include <complex>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>

#include "../libs/mandelbrot.hxx"

#define HEIGHT 1000
#define WIDTH 1000

struct record {
    std::complex<double> z;
    unsigned int iters;
};

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mandelbrot visualizer");
    SDL_SetWindowMaximumSize(window, WIDTH, HEIGHT);

    record** grid = new record*[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i) {
        grid[i] = new record[WIDTH];
    }

    for (int x = 0; x < HEIGHT; x++) { // rows
        for (int y = 0; y < WIDTH; y++) { //columns

            double actual_x = (x / double(WIDTH/2)) - 1.5;
            double actual_y = (y / double(HEIGHT/2)) - 1;

            grid[x][y].z = std::complex<double>(
                actual_x, actual_y
            );

            grid[x][y].iters = mdl::is_in_set(grid[x][y].z, 50, 10);

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

    for (int i = 0; i < HEIGHT; ++i) {
        delete[] grid[i];
    }
    delete[] grid;


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}