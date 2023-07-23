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

Record2DArray get_map(unsigned int height, unsigned int width, C min, C max, unsigned int iterations, unsigned int threshold) {
    Record2DArray map = Record2DArray(height, std::vector<record>(width, record()));

    C c_dimension = C(
        std::abs(min.real()) + std::abs(max.real()),
        std::abs(min.imag()) + std::abs(min.imag())
    );

    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {
            double x_percentage = (double(x) - (c_dimension.real() / 2) ) / double(width);
            double y_percentage = (double(y) - (c_dimension.imag() / 2) ) / double(height);

            double re = std::lerp(min.real(), max.real(), x_percentage);
            double im = std::lerp(min.imag(), max.imag(), y_percentage);

            map[x][y] = record(C(re, im));

            unsigned int iters = is_in_set(map[x][y].z, iterations, threshold);
            map[x][y].iters = iters;
        }
    }

    return map;
}

void update_map(Record2DArray& grid, C min, C max, unsigned int iterations, unsigned int threshold) {
    C c_dimension = C(
        std::abs(min.real()) + std::abs(max.real()),
        std::abs(min.imag()) + std::abs(min.imag())
    );

    int width = grid.size();
    int height = grid[0].size();

    for(unsigned int y = 0; y < width; y++) {
        for(unsigned int x = 0; x < height; x++) {
            double x_percentage = (double(x) - (c_dimension.real() / 2) ) / double(width);
            double y_percentage = (double(y) - (c_dimension.imag() / 2) ) / double(height);

            double re = std::lerp(min.real(), max.real(), x_percentage);
            double im = std::lerp(min.imag(), max.imag(), y_percentage);

            grid[x][y] = record(C(re, im));

            unsigned int iters = is_in_set(grid[x][y].z, iterations, threshold);
            grid[x][y].iters = iters;
        }
    }
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
        }
    }

    SDL_RenderPresent(renderer);
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
