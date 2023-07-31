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
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_CreateWindowAndRenderer(this->_config._width, this->_config._height, 0, &this->_SDLWindow, &this->_SDLRenderer);
        SDL_SetWindowTitle(this->_SDLWindow, "Mandelbrot visualizer");
        SDL_SetWindowMaximumSize(this->_SDLWindow, this->_config._width, this->_config._height);

        this->_pixels = std::vector(
            this->_config._height * this->_config._width, Cell());

        for(unsigned int i = 0; i < this->_config._width; i++) {
            for(unsigned int j = 0; j < this->_config._height; j++) {
                Cell* current = &_pixels[(this->_config._height * i) + j];
                *current = Cell(DisplayCoordinate{i,j}, this->_config);
                current->compute(this->_config);
            }
        }   

        this->paint();
    }

    void MandelbrotDisplay::paint() {
        Color* pOut = &(this->_config._mandelbrotOut);
        Color* pBack = &(this->_config._mandelbrotBackground);
        Color* pFill = &(this->_config._mandelbrotFill);
        for(unsigned int y=0; y<this->_config._width; ++y) {
            for (unsigned int x=0; x<this->_config._height; ++x) {
                Cell* pCell = &(this->_pixels[this->_config._height*y + x]);
                if(pCell->getIters() == 0) {
                    SDL_SetRenderDrawColor(this->_SDLRenderer, pFill->r, pFill->g, pFill->b, 255);
                } else {
                    /*
                    SDL_SetRenderDrawColor(this->_SDLRenderer, 
                        std::lerp(pOut->r, pBack->r, 1/double(pCell->getIters())),
                        std::lerp(pOut->g, pBack->g, 1/double(pCell->getIters())),
                        std::lerp(pOut->b, pBack->b, 1/double(pCell->getIters())),
                        255
                    );
                    */
                   SDL_SetRenderDrawColor(this->_SDLRenderer, 255, 255, 255, 255);
                }

                SDL_RenderDrawPoint(this->_SDLRenderer, x, y);
            }
        }
        SDL_RenderPresent(this->_SDLRenderer);
    }

    void MandelbrotDisplay::clean() {
        this->_pixels.clear();
        this->_pixels.shrink_to_fit();

        SDL_DestroyRenderer(this->_SDLRenderer);
        SDL_DestroyWindow(this->_SDLWindow);
        SDL_Quit();
    }

        Cell::Cell() {
        this->_iters = 0;
        this->_c = C(0, 0);
    }

    Cell::Cell(C z) {
        this->_c = z;
        this->_iters = 0;
    }

    Cell::Cell(DisplayCoordinate i, MandelbrotConfiguration& c) {
        this->_c = Cell::_fromCoordinates(i, c);
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
        return this->_c;
    }

    void Cell::compute(MandelbrotConfiguration& config) {
        C z(0, 0);

        for(unsigned int i = 0; i < config._iterations; i++) {
            z = z*z + this->_c;
            double candidate = z.real() * z.real() + z.imag() * z.imag();
            if (candidate > 4.0) {
                this->_iters = i;
                return;
            }
        }

        this->_iters = 0;
        return;
    }
}