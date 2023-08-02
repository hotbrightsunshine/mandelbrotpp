#ifndef mandelbrot
#define mandelbrot

#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

namespace mandel {

    // Synonyms
    typedef std::complex<double> ComplexNumber;

    static constexpr unsigned int DEFAULT_ITERATIONS = 190;
    static constexpr unsigned int DEFAULT_THRESHOLD = 4;
    static constexpr unsigned int DEFAULT_WIDTH = 1000;
    static constexpr unsigned int DEFAULT_HEIGHT = 1000;
    static constexpr ComplexNumber DEFAULT_RENDER_MIN = ComplexNumber(-2, -2);
    static constexpr ComplexNumber DEFAULT_RENDER_MAX = ComplexNumber(2, 2);

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

}

#endif