#include <iostream>
#include <complex>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>

#include "../libs/mandelbrot.hxx"

const unsigned int HEIGHT = 800;
const unsigned int WIDTH = HEIGHT;
const unsigned int ITERATIONS = 50;
const unsigned int THRESHOLD = 20;
const double ZOOMIN = 0.8;
const double ZOOMOUT = 1.2;

C vmin = (-2, -2);
C vmax = (2, 2);

int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mandelbrot visualizer");
    SDL_SetWindowMaximumSize(window, WIDTH, HEIGHT);

    Record2DArray grid = get_map(HEIGHT, WIDTH, vmin, vmax, ITERATIONS, THRESHOLD);

    paint(HEIGHT, WIDTH, renderer, grid);
    
    SDL_RenderPresent(renderer);
    
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while(SDL_PollEvent( &e )) {
            if ( e.type == SDL_QUIT )
                quit = !quit; 
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_o:
                        zoom(ZOOMOUT, vmin, vmax);
                        break;
                    case SDLK_i:
                        zoom(ZOOMIN, vmin, vmax);
                        break;
                    default:
                        break;
                }

                grid = get_map(HEIGHT, WIDTH, vmin, vmax, ITERATIONS, THRESHOLD);
                paint(HEIGHT, WIDTH, renderer, grid);
            }
        }
    }

    grid.clear();
    grid.shrink_to_fit();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}