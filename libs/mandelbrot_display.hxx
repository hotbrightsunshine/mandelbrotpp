#include <SDL2/SDL.h>
#include <vector>

#include "mandelbrot.hxx"

namespace mandel {

    struct Color {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };

    const Color DEFAULT_MANDELBROT_COLOR_OUT = Color { 0xFF, 0, 0 };
    const Color DEFAULT_MANDELBROT_COLOR_FILL = Color { 0, 0, 0 };
    const Color DEFAULT_MANDELBROT_COLOR_BACKGROUND = Color { 0, 0, 0};
    const double DEFAULT_ZOOMIN_COEFFICIENT = 0.8;
    const double DEFAULT_ZOOMOUT_COEFFICIENT = 1.2;
    const double DEFAULT_TRANSLATION_COEFFICIENT = 0.2;

    struct MandelbrotConfiguration {
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
    };

    class MandelbrotDisplay {
        private:
            std::vector<Cell> _pixels;
            MandelbrotConfiguration _config;
            SDL_Renderer* _SDLRenderer;
            SDL_Window* _SDLWindow; 

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