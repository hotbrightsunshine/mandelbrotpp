#include "mandelbrot.hxx"
#include "mandelbrot_display.hxx"

namespace mandel {

    struct MandelbrotConfiguration {
        // TODO
    }

    const Color DEFAULT_MANDELBROT_COLOR_OUT = Color { 0xFF, 0, 0 };
    const Color DEFAULT_MANDELBROT_COLOR_FILL = Color { 0, 0, 0 };
    const Color DEFAULT_MANDELBROT_COLOR_BACKGROUND = Color { 0, 0, 0};
    const double DEFAULT_ZOOMIN_COEFFICIENT = 0.8;
    const double DEFAULT_ZOOMOUT_COEFFICIENT = 1.2;
    const double DEFAULT_TRANSLATION_COEFFICIENT = 0.2;


    MandelbrotDisplay::MandelbrotDisplay() {
        this->_height = DEFAULT_HEIGHT;
        this->_width = DEFAULT_WIDTH;
        this->_iterations = DEFAULT_ITERATIONS;
        this->_threshold = DEFAULT_THRESHOLD;
        this->_renderMax = DEFAULT_RENDER_MAX;
        this->_renderMin = DEFAULT_RENDER_MIN;
        this->_mandelbrotOut = DEFAULT_MANDELBROT_COLOR_OUT;
        this->_mandelbrotFill = DEFAULT_MANDELBROT_COLOR_FILL;
        this->_mandelbrotBackground = DEFAULT_MANDELBROT_COLOR_BACKGROUND;
    }

    MandelbrotDisplay::MandelbrotDisplay(
        unsigned int height,
        // unsigned int width, #TODO Not supported yet
        unsigned int iterations,
        unsigned int threshold,
        Color mandelbrotFill,
        Color mandelbrotOut,
        Color mandelbrotBackground,
        C renderMin,
        C renderMax
    ) {
        this->_height = height;
        this->_width = height; // Not supported yet
        this->_iterations = iterations;
        this->_threshold = threshold;
        this->_mandelbrotOut = mandelbrotOut;
        this->_mandelbrotFill = mandelbrotFill;
        this->_mandelbrotBackground = mandelbrotBackground;
        this->_renderMin = renderMin;
        this->_renderMax = renderMax;
    }
}