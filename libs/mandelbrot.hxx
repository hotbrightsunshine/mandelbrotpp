#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <format>
#include <SDL2/SDL.h>

class record {
    public:
        std::complex<double> z;
        unsigned int iters;

        record(std::complex<double> z, unsigned int iters);
        record(std::complex<double> z);
        record();
};

// Synonyms
typedef std::complex<double> C;
typedef std::vector<std::vector<record>> Record2DArray;

// Methods
unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold);
Record2DArray get_map(unsigned int height, unsigned int width, C min, C max, unsigned int iterations, unsigned int threshold);
void paint(unsigned int height, unsigned int width, SDL_Renderer* renderer, Record2DArray& grid);
void zoom(double coefficient, C& min, C& max);
void update_map(Record2DArray& grid, C min, C max, unsigned int iterations, unsigned int threshold);
void clear_map(Record2DArray& map);
