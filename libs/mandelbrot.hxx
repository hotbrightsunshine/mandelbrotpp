#ifndef mandelbrot
#define mandelbrot

#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

namespace mandel {

// Synonyms
typedef std::complex<double> C;

static constexpr unsigned int DEFAULT_ITERATIONS = 190;
static constexpr unsigned int DEFAULT_THRESHOLD = 4;
static constexpr unsigned int DEFAULT_WIDTH = 1000;
static constexpr unsigned int DEFAULT_HEIGHT = 1000;
static constexpr C DEFAULT_RENDER_MIN = C(-2, -2);
static constexpr C DEFAULT_RENDER_MAX = C(2, 2);

enum Direction {
    UP,
    DOWN,
    LEFT, 
    RIGHT
};

enum Sense {
    IN,
    OUT
};

struct DisplayCoordinate {
    unsigned int x;
    unsigned int y;
};

// Methods
/*
Record2DArray get_map(unsigned int height, unsigned int width, C min, C max, unsigned int iterations, unsigned int threshold);
void paint(unsigned int height, unsigned int width, SDL_Renderer* renderer, Record2DArray& grid);
void zoom(double coefficient, C& min, C& max);
void translate(Direction d, double coefficient, C&min, C&max);
void update_map(Record2DArray& grid, C min, C max, unsigned int iterations, unsigned int threshold);
void clear_map(Record2DArray& map);
double coord(double w, double a, double c, double x);
C get_complex_coord(unsigned int height, unsigned int width, C min, C max, unsigned int x, unsigned int y);

void update_map_and_paint(
    Record2DArray& grid, 
    C min, C max, 
    unsigned int iterations, 
    unsigned int threshold, 
    unsigned int height, 
    unsigned int width, 
    SDL_Renderer* renderer);

*/

}

#endif