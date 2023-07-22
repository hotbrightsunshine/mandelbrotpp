#include <iostream>
#include <complex>
#include <SDL2/SDL.h>
#include <cmath>
#include <tuple>
#include <fstream>

#define HEIGHT 500
#define WIDTH 500

struct record {
    std::complex<double> z;
    unsigned int iters;
};

unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold) {
    
    std::complex<double> z(0, 0);

    for(int re = 0; re < iterations; ++re) {
        z = z*z + c;
        if (std::norm(z) > threshold) {
            return re;
        }
    }

    return 0;
}

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

            grid[x][y].iters = is_in_set(grid[x][y].z, 50, 10);

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