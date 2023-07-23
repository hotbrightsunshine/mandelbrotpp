#include <complex>
#include <cmath>
#include <vector>
#include <iostream>
#include <format>
#include <SDL2/SDL.h>

#include "mandelbrot.hxx"

record::record(std::complex<double> z, unsigned int iters) {
    this->z = z;
    this->iters = iters;
};

record::record(std::complex<double> z) {
    this->z = z;
    this->iters = 0;
};

record::record() {
    this->z = C(0, 0);
    this->iters = 0;
};

unsigned int is_in_set(C c, unsigned int iterations, double threshold) {
    C z(0, 0);

    for(int re = 0; re < iterations; ++re) {
        z = z*z + c;
        if (std::norm(z) > threshold) {
            return re;
        }
    }

    return 0;
}

double coord(double w, double a, double c, double x) {
    return a + (c - a) * (2 * x - (std::abs(a) + std::abs(c))) / (2 * w); 
}

C get_complex_coord(unsigned int height, unsigned int width, C min, C max, unsigned int x, unsigned int y) {
    double real = coord(double(width), min.real(), max.real(), x);
    double imag = coord(double(height), min.imag(), max.imag(), y);
    return C(real, imag);
}

Record2DArray get_map(unsigned int height, unsigned int width, C min, C max, unsigned int iterations, unsigned int threshold) {
    Record2DArray map = Record2DArray(height, std::vector<record>(width, record()));

    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {
            C z = get_complex_coord(height, width, min, max, x, y);

            map[x][y] = record(z);

            unsigned int iters = is_in_set(map[x][y].z, iterations, threshold);
            map[x][y].iters = iters;
        }
    }

    return map;
}

void update_map(Record2DArray& grid, C min, C max, unsigned int iterations, unsigned int threshold) {
    int width = grid.size();
    int height = grid[0].size();

    unsigned long int _iterations = 0;

    for(unsigned int y = 0; y < width; y++) {
        for(unsigned int x = 0; x < height; x++) {

            C z = get_complex_coord(height, width, min, max, x, y);

            grid[x][y] = record(z);

            unsigned int iters = is_in_set(grid[x][y].z, iterations, threshold);
            grid[x][y].iters = iters;
            _iterations++;
        }
    }
    std::cout << "Iterations in calculation: " << _iterations << std::endl;
}

void clear_map(Record2DArray& map) {
    for (unsigned int i = 0; i < map.size(); i ++) {
        map[i].clear();
        map[i].shrink_to_fit();
    }
    map.clear();
    map.shrink_to_fit();
}

void paint(unsigned int height, unsigned int width, SDL_Renderer* renderer, Record2DArray& grid) {
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

void zoom(double coefficient, C& min, C& max) {
    min.real(min.real() * coefficient);
    min.imag(min.imag() * coefficient);
    max.real(max.real() * coefficient);
    max.imag(max.imag() * coefficient);
}

void translate(direction d, double coefficient, C& min, C& max) {
    double deltaX = (max.real() - min.real()) * coefficient;
    double deltaY = (max.imag() - min.imag()) * coefficient;

    switch (d) {
        case direction::DOWN:
            min.imag(min.imag() + deltaY);
            max.imag(max.imag() + deltaY);
            break;
        case direction::UP:
            min.imag(min.imag() - deltaY);
            max.imag(max.imag() - deltaY);
            break;
        case direction::RIGHT:
            min.real(min.real() + deltaX);
            max.real(max.real() + deltaX);
            break;
        case direction::LEFT:
            min.real(min.real() - deltaX);
            max.real(max.real() - deltaX);
            break;
        default:
            break;
    }
}
