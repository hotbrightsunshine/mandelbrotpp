#include <vector>

#include "mandelbrot.hxx"
#include "mandelbrot_display.hxx"
#include "mandelbrot_cell.hxx"

namespace mandel {

    MandelbrotConfiguration::MandelbrotConfiguration() {
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

    MandelbrotDisplay::MandelbrotDisplay(MandelbrotConfiguration config) {
        this->_config = config;
    }

    MandelbrotDisplay::MandelbrotDisplay() {
        this->_config = MandelbrotConfiguration();
    }

    void MandelbrotDisplay::initialize() {
        this->_pixels = std::vector(
            this->_config._height * this->_config._width, Cell());

        for(unsigned int i = 0; i < this->_config._width; i++) {
            for(unsigned int j = 0; j < this->_config._height; j++) {
                _pixels[this->_config._height * j + i] = Cell(DisplayCoordinate{i,j}, this->_config);
            }
        }   
        
    }
}