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
using namespace mandel;

int main() {
    MandelbrotDisplay d = MandelbrotDisplay();
    d.initialize();
    std::this_thread::sleep_for(5s);
    d.clean();
}