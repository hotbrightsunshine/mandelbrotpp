#include <iostream>
#include <complex>
#include <cmath>
#include <thread>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>

#include "../libs/mandelbrot.hxx"

using namespace std::chrono_literals;

const unsigned int HEIGHT = 800;
const unsigned int WIDTH = HEIGHT;
const unsigned int ITERATIONS = 50;
const double THRESHOLD = 20;
const double ZOOMIN = 0.8;
const double ZOOMOUT = 1.2;
const double TRANSLCOEFF = 0.2;

C vmin = C(-2, -2);
C vmax = C(2, 2);

int main() {

    std::cout << vmin << vmax << std::endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mandelbrot visualizer");
    SDL_SetWindowMaximumSize(window, WIDTH, HEIGHT);

    Record2DArray grid = get_map(HEIGHT, WIDTH, vmin, vmax, ITERATIONS, THRESHOLD);

    paint(HEIGHT, WIDTH, renderer, grid);
    
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
                    case SDLK_UP:
                        translate(direction::UP, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_DOWN:
                        translate(direction::DOWN, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_RIGHT:
                        translate(direction::RIGHT, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_LEFT:
                        translate(direction::LEFT, TRANSLCOEFF, vmin, vmax);
                        break;
                    default:
                        break;
                };
                std::cout << vmin << vmax << std::endl;
                update_map(grid, vmin, vmax, ITERATIONS, THRESHOLD);
                paint(HEIGHT, WIDTH, renderer, grid);
                std::this_thread::sleep_for(2ms);
            }
        }
    }

    clear_map(grid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}