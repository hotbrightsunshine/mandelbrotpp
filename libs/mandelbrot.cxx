/*
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

#include "mandelbrot.hxx"

unsigned int mandel::is_in_set(C c, unsigned int iterations, double threshold) {
    C _z(0, 0);

    for(int re = 0; re < iterations; ++re) {
        _z = _z*_z + c;
        if (std::norm(_z) > threshold) {
            return re;
        }
    }

    return 0;
}

double mandel::coord(double w, double a, double c, double x) {
    return a + (c - a) * (2 * x - (std::abs(a) + std::abs(c))) / (2 * w); 
}

mandel::C mandel::get_complex_coord(unsigned int height, unsigned int width, C min, C max, unsigned int x, unsigned int y) {
    double real = coord(double(width), min.real(), max.real(), x);
    double imag = coord(double(height), min.imag(), max.imag(), y);
    return C(real, imag);
}

mandel::Record2DArray mandel::get_map(unsigned int height, unsigned int width, C min, C max, unsigned int iterations, unsigned int threshold) {
    Record2DArray map = Record2DArray(height, std::vector<Cell>(width, Cell()));

    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {
            C _z = mandel::get_complex_coord(height, width, min, max, x, y);

            map[x][y] = Cell(_z);

            unsigned int iters = is_in_set(map[x][y]._z, iterations, threshold);
            map[x][y].iters = iters;
        }
    }

    return map;
}

void mandel::update_map(Record2DArray& grid, C min, C max, unsigned int iterations, unsigned int threshold) {
    int width = grid.size();
    int height = grid[0].size();

    unsigned long int _iterations = 0;

    for(unsigned int y = 0; y < width; y++) {
        for(unsigned int x = 0; x < height; x++) {

            C _z = get_complex_coord(height, width, min, max, x, y);

            grid[x][y] = Cell(_z);

            unsigned int iters = is_in_set(grid[x][y]._z, iterations, threshold);
            grid[x][y].iters = iters;
            _iterations++;
        }
    }
    std::cout << "Iterations in calculation: " << _iterations << std::endl;
}

void mandel::update_map_and_paint(
    Record2DArray& grid, 
    C min, C max, 
    unsigned int iterations, 
    unsigned int threshold, 
    unsigned int height, 
    unsigned int width, 
    SDL_Renderer* renderer) {
        for(unsigned int y = 0; y < width; y++) {
        for(unsigned int x = 0; x < height; x++) {

            C _z = get_complex_coord(height, width, min, max, x, y);

            grid[x][y] = Cell(_z);

            unsigned int iters = is_in_set(grid[x][y]._z, iterations, threshold);
            grid[x][y].iters = iters;
            
            if (grid[x][y].iters == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
            } else {
                SDL_SetRenderDrawColor(renderer, 
                    std::lerp(255, 0, 1/double(grid[x][y].iters)), 
                255, 0, 1);
            }

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}

void mandel::clear_map(Record2DArray& map) {
    for (unsigned int i = 0; i < map.size(); i ++) {
        map[i].clear();
        map[i].shrink_to_fit();
    }
    map.clear();
    map.shrink_to_fit();
}

void mandel::paint(unsigned int height, unsigned int width, SDL_Renderer* renderer, Record2DArray& grid) {
    SDL_RenderClear(renderer);
    unsigned long int _iterations = 0;
    for (int x = 0; x < height; x++) { // rows
        for (int y = 0; y < width; y++) { //columns

            if (grid[x][y].iters == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
            } else {
                SDL_SetRenderDrawColor(renderer, 
                    std::lerp(255, 0, 1/double(grid[x][y].iters)), 
                255, 0, 1);
            }

            SDL_RenderDrawPoint(renderer, x, y);
            _iterations ++;
        }
    }

    SDL_RenderPresent(renderer);
    std::cout << "Iterations in paint: " << _iterations << std::endl;
}

void mandel::zoom(double coefficient, C& min, C& max) {
    min.real(min.real() * coefficient);
    min.imag(min.imag() * coefficient);
    max.real(max.real() * coefficient);
    max.imag(max.imag() * coefficient);
}

void mandel::translate(Direction d, double coefficient, C& min, C& max) {
    double deltaX = (max.real() - min.real()) * coefficient;
    double deltaY = (max.imag() - min.imag()) * coefficient;

    switch (d) {
        case Direction::DOWN:
            min.imag(min.imag() + deltaY);
            max.imag(max.imag() + deltaY);
            break;
        case Direction::UP:
            min.imag(min.imag() - deltaY);
            max.imag(max.imag() - deltaY);
            break;
        case Direction::RIGHT:
            min.real(min.real() + deltaX);
            max.real(max.real() + deltaX);
            break;
        case Direction::LEFT:
            min.real(min.real() - deltaX);
            max.real(max.real() - deltaX);
            break;
        default:
            break;
    }
}
*/