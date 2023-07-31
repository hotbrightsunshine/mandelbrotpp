#ifndef mandelbrot_display_hxx
#define mandelbrot_display_hxx

#include <SDL2/SDL.h>
#include <vector>

#include "mandelbrot.hxx"

namespace mandel {

    struct Color {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };

    static constexpr Color DEFAULT_MANDELBROT_COLOR_OUT = Color { 0xFF, 0, 0 };
    static constexpr Color DEFAULT_MANDELBROT_COLOR_FILL = Color { 0, 0, 0 };
    static constexpr Color DEFAULT_MANDELBROT_COLOR_BACKGROUND = Color { 0xAA, 0, 0xFF};
    static constexpr double DEFAULT_ZOOMIN_COEFFICIENT = 0.8;
    static constexpr double DEFAULT_ZOOMOUT_COEFFICIENT = 1.2;
    static constexpr double DEFAULT_TRANSLATION_COEFFICIENT = 0.2;

    struct MandelbrotConfiguration { //should be stored in the heap
        unsigned int _height = DEFAULT_HEIGHT;
        unsigned int _width = DEFAULT_WIDTH;
        unsigned int _iterations = DEFAULT_ITERATIONS;
        unsigned int _threshold = DEFAULT_THRESHOLD; 
        Color _mandelbrotFill = DEFAULT_MANDELBROT_COLOR_FILL;
        Color _mandelbrotOut = DEFAULT_MANDELBROT_COLOR_OUT;
        Color _mandelbrotBackground = DEFAULT_MANDELBROT_COLOR_BACKGROUND;
        C _renderMin = DEFAULT_RENDER_MIN;
        C _renderMax = DEFAULT_RENDER_MAX;
        double _zoomInCoefficient = DEFAULT_ZOOMIN_COEFFICIENT;
        double _zoomOutCoefficient = DEFAULT_ZOOMOUT_COEFFICIENT;
        double _translationCoefficient = DEFAULT_TRANSLATION_COEFFICIENT;
    };

    class Cell {
        private: 
            C _c;
            unsigned int _iters;
            /**
             * This method converts SDL's (X;Y) coordinates into the (Re;Im) coordinates of the complex plane 
            */
            static C _fromCoordinates(DisplayCoordinate i, MandelbrotConfiguration& c);
            static double _coordFunction(double w, double a, double c, double x);

        public:
            Cell(C z);
            Cell(DisplayCoordinate i, MandelbrotConfiguration& c);
            Cell();

            void compute(MandelbrotConfiguration& C); // compute the mandelbrot calculation = is in set

            unsigned int getIters();
            C getZ();
    };

    class Grid {
        private:
            std::vector<Cell> _pixels;
        public:
            Grid(MandelbrotConfiguration& c);
            Grid();
            
            Cell* getpCell(unsigned int x, unsigned int y, MandelbrotConfiguration& c);
            void clear();
    };

    class MandelbrotDisplay {
        private:
            Grid _grid;
            MandelbrotConfiguration _config;
            SDL_Renderer* _SDLRenderer = nullptr;
            SDL_Window* _SDLWindow = nullptr; 

            void paint();

        public:
            MandelbrotDisplay();
            MandelbrotDisplay(
                MandelbrotConfiguration& mandelbrot
            );

            void zoom(Sense d);
            void translate(Direction d);
            void clean();
            void initialize();
    };
}

#endif