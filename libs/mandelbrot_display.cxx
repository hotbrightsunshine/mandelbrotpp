#include <vector>

#include "mandelbrot.hxx"
#include "mandelbrot_display.hxx"
//#include "mandelbrot_cell.hxx"

namespace mandel {
    MandelbrotDisplay::MandelbrotDisplay(MandelbrotConfiguration& config) {
        this->_config = config;
    }

    MandelbrotDisplay::MandelbrotDisplay() {
        this->_config = MandelbrotConfiguration();
    }

    void MandelbrotDisplay::initialize() {
        /*
        this->_pixels = std::vector(
            this->_config._height * this->_config._width, Cell());

        for(unsigned int i = 0; i < this->_config._width; i++) {
            for(unsigned int j = 0; j < this->_config._height; j++) {
                Cell* current = &_pixels[this->_config._height * j + i];
                *current = Cell(DisplayCoordinate{i,j}, this->_config);
                current->compute(this->_config);
            }
        }   

        (*this)._config;
        */
    }

        Cell::Cell() {
        this->_iters = 0;
        this->_z = C(0, 0);
    }

    Cell::Cell(C z) {
        this->_z = z;
        this->_iters = 0;
    }

    Cell::Cell(DisplayCoordinate i, MandelbrotConfiguration& c) {
        this->_z = Cell::_fromCoordinates(i, c);
        this->_iters = 0;
    }

    C Cell::_fromCoordinates(DisplayCoordinate i, MandelbrotConfiguration& c) {
        double real = Cell::_coordFunction(double(c._width), c._renderMin.real(), c._renderMax.real(), i.x);
        double imag = Cell::_coordFunction(double(c._height), c._renderMin.imag(), c._renderMax.imag(), i.y);
        return C(real, imag);
    }

    double Cell::_coordFunction(double w, double a, double c, double x) {
        return a + (c - a) * (2 * x - (std::abs(a) + std::abs(c))) / (2 * w); 
    }

    unsigned int Cell::getIters() {
        return this->_iters;
    }

    C Cell::getZ() {
        return this->_z;
    }

    void Cell::compute(MandelbrotConfiguration& c) {
        C z(0, 0);

        for(int re = 0; re < c._iterations; ++re) {
            z = z*z + this->_z;
            if (std::norm(_z) > c._threshold) {
                this->_iters = re;
                return;
            }
        }

        this->_iters = 0;
        return;
    }
}