#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <format>
#include <SDL2/SDL.h>

namespace mandel {

class MandelbrotDisplay {
    // TODO: in another file
};

class Cell {
    public:
        std::complex<double> z;
        unsigned int iters;

        Cell(std::complex<double> z, unsigned int iters);
        Cell(std::complex<double> z);
        Cell();
};

enum Direction {
    UP,
    DOWN,
    LEFT, 
    RIGHT
};

// Synonyms
typedef std::complex<double> C;
typedef std::vector<std::vector<Cell>> Record2DArray;

// Methods
unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold);
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

}