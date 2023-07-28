#include <SDL2/SDL.h>
#include <vector>

#include "mandelbrot.hxx"

namespace mandel {

    struct Color {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };

    class MandelbrotDisplay {
        private:
            std::vector<Cell> _pixels;
            unsigned int _height;
            unsigned int _width;
            unsigned int _iterations;
            unsigned int _threshold; 
            Color _mandelbrotFill;
            Color _mandelbrotOut;
            Color _mandelbrotBackground;
            C _renderMin;
            C _renderMax;
            double _zoomCoefficient;
            double _translationCoefficient;
            SDL_Renderer* _SDLRenderer;
            SDL_Window* _SDLWindow; 

            void paint();

        public:
            MandelbrotDisplay();
            MandelbrotDisplay(
                unsigned int height,
                // unsigned int width, #TODO Not supported yet
                unsigned int iterations,
                unsigned int threshold,
                Color mandelbrotFill,
                Color mandelbrotOut,
                Color mandelbrotBackground,
                C renderMin,
                C renderMax
            );

            void zoom(Sense d);
            void translate(Direction d);
            void clean();
            void initialize();
    };

    class Cell {
        private: 
            C z;
            unsigned int iters;
            C fromCoordinates(DisplayCoordinate i);

        public:
            Cell(C z, unsigned int iters);
            Cell(C z);
            Cell(DisplayCoordinate i);
            Cell();

            void compute(); // compute the mandelbrot calculation = is in set

            unsigned int getIters();

    };

}