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
#include "../libs/mandelbrot_display.hxx"

using namespace std::chrono_literals;

const unsigned int HEIGHT = 800;
const unsigned int WIDTH = HEIGHT;
const unsigned int ITERATIONS = 25;
const double THRESHOLD = 5;
const double ZOOMIN = 0.8;
const double ZOOMOUT = 1.2;
const double TRANSLCOEFF = 0.2;

mandel::C vmin = mandel::C(-2, -2);
mandel::C vmax = mandel::C(2, 2);
using namespace mandel;

int main() {
    MandelbrotDisplay d = MandelbrotDisplay();
    d.initialize();
    std::this_thread::sleep_for(5s);
    d.clean();

/*
    std::cout << vmin << vmax << std::endl; 

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Mandelbrot visualizer");
    SDL_SetWindowMaximumSize(window, WIDTH, HEIGHT);

    mandel::Record2DArray grid = mandel::get_map(HEIGHT, WIDTH, vmin, vmax, ITERATIONS, THRESHOLD);

    mandel::paint(HEIGHT, WIDTH, renderer, grid);
    
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while(SDL_PollEvent( &e )) {
            if ( e.type == SDL_QUIT )
                quit = !quit; 
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_o:
                        mandel::zoom(ZOOMOUT, vmin, vmax);
                        break;
                    case SDLK_i:
                        mandel::zoom(ZOOMIN, vmin, vmax);
                        break;
                    case SDLK_UP:
                        mandel::translate(mandel::Direction::UP, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_DOWN:
                        mandel::translate(mandel::Direction::DOWN, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_RIGHT:
                        mandel::translate(mandel::Direction::RIGHT, TRANSLCOEFF, vmin, vmax);
                        break;
                    case SDLK_LEFT:
                        mandel::translate(mandel::Direction::LEFT, TRANSLCOEFF, vmin, vmax);
                        break;
                    default:
                        break;
                };
                std::cout << vmin << vmax << std::endl;
                mandel::update_map_and_paint(grid, vmin, vmax, ITERATIONS, THRESHOLD, HEIGHT, WIDTH, renderer);
                std::this_thread::sleep_for(2ms);
            }
        }
    }

    mandel::clear_map(grid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    */
}