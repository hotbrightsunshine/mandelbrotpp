#include <vector>
#include <iostream>

#include "mandelbrot.hxx"
#include "mandelbrot_display.hxx"
//#include "mandelbrot_cell.hxx"

namespace mandel {
    MandelbrotDisplay::MandelbrotDisplay(MandelbrotConfiguration& config) {
        this->_grid = Grid(config);
        this->_config = config;
    }

    MandelbrotDisplay::MandelbrotDisplay() {
        this->_config = MandelbrotConfiguration();
        this->_grid = Grid(this->_config);
    }

    void MandelbrotDisplay::initialize() {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_CreateWindowAndRenderer(this->_config._width, this->_config._height, 0, &this->_SDLWindow, &this->_SDLRenderer);
        SDL_SetWindowTitle(this->_SDLWindow, "Mandelbrot visualizer");
        SDL_SetWindowMaximumSize(this->_SDLWindow, this->_config._width, this->_config._height);

        this->paint();
    }

    void MandelbrotDisplay::paint() {
        Color* pOut = &(this->_config._mandelbrotOut);
        Color* pBack = &(this->_config._mandelbrotBackground);
        Color* pFill = &(this->_config._mandelbrotFill);
        for(unsigned int y=0; y<this->_config._width; ++y) {
            for (unsigned int x=0; x<this->_config._height; ++x) {
                Cell* pCell = this->_grid.getpCell(x, y, this->_config);
                if(pCell->getIters() == 0) {
                    SDL_SetRenderDrawColor(this->_SDLRenderer, pFill->r, pFill->g, pFill->b, 255);
                } else {
                    SDL_SetRenderDrawColor(this->_SDLRenderer, 
                        std::lerp(pOut->r, pBack->r, 1/double(pCell->getIters())),
                        std::lerp(pOut->g, pBack->g, 1/double(pCell->getIters())),
                        std::lerp(pOut->b, pBack->b, 1/double(pCell->getIters())),
                        255
                    );
                }

                SDL_RenderDrawPoint(this->_SDLRenderer, x, y);
            }
        }
        SDL_RenderPresent(this->_SDLRenderer);
    }

    void MandelbrotDisplay::startListening() {
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while(SDL_PollEvent( &e )) {
                if ( e.type == SDL_QUIT )
                    quit = !quit; 
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_o:
                            this->zoom(Sense::OUT);
                            break;
                        case SDLK_i:
                            this->zoom(Sense::IN);
                            break;
                        case SDLK_UP:
                            this->translate(Direction::UP);
                            break;
                        case SDLK_DOWN:
                            this->translate(Direction::DOWN);
                            break;
                        case SDLK_RIGHT:
                            this->translate(Direction::RIGHT);
                            break;
                        case SDLK_LEFT:
                            this->translate(Direction::LEFT);
                            break;
                        default:
                            break;
                    };
                    this->_grid.compute(this->_config);
                    this->paint();
                }
            }
        }
    }

    void MandelbrotDisplay::zoom(Sense s) {

        double _zoomCoefficient = 
            (s == Sense::IN) ? 
            this->_config._zoomInCoefficient : 
            this->_config._zoomOutCoefficient;

        Complex newMin =  Complex(
            this->_config._renderMin.real() * _zoomCoefficient,
            this->_config._renderMin.imag() * _zoomCoefficient
        );
        Complex newMax = Complex(
            this->_config._renderMax.real() * _zoomCoefficient,
            this->_config._renderMax.imag() * _zoomCoefficient
        );
        this->_config._renderMin = newMin;
        this->_config._renderMax = newMax;
    }

    void MandelbrotDisplay::translate(Direction d) {
        Complex* min = &this->_config._renderMin;
        Complex* max = &this->_config._renderMax;

        Complex delta(
            (min->real() - max->real()) * this->_config._translationCoefficient,
            (min->real() - max->real()) * this->_config._translationCoefficient
        );

        switch (d) {
            case Direction::DOWN:
                min->imag(min->imag() + delta.imag());
                max->imag(max->imag() + delta.imag());
                break;
            case Direction::UP:
                min->imag(min->imag() - delta.imag());
                max->imag(max->imag() - delta.imag());
                break;
            case Direction::RIGHT:
                min->real(min->real() + delta.real());
                max->real(max->real() + delta.real());
                break;
            case Direction::LEFT:
                min->real(min->real() - delta.real());
                max->real(max->real() - delta.real());
                break;
            default:
                break;
        }
    }

    void MandelbrotDisplay::clean() {
        this->_grid.clear();

        SDL_DestroyRenderer(this->_SDLRenderer);
        SDL_DestroyWindow(this->_SDLWindow);
        SDL_Quit();
    }

        Cell::Cell() {
        this->_iters = 0;
        this->_c = Complex(0, 0);
    }

    Cell::Cell(Complex z) {
        this->_c = z;
        this->_iters = 0;
    }

    Cell::Cell(DisplayCoordinate i, MandelbrotConfiguration& c) {
        this->_c = Cell::_fromCoordinates(i, c);
        this->_iters = 0;
    }

    Complex Cell::_fromCoordinates(DisplayCoordinate i, MandelbrotConfiguration& c) {
        double real = Cell::_coordFunction(double(c._width), c._renderMin.real(), c._renderMax.real(), i.x);
        double imag = Cell::_coordFunction(double(c._height), c._renderMin.imag(), c._renderMax.imag(), i.y);
        return Complex(real, imag);
    }

    double Cell::_coordFunction(double w, double a, double c, double x) {
        return a + (c - a) * (2 * x - (std::abs(a) + std::abs(c))) / (2 * w); 
    }

    unsigned int Cell::getIters() {
        return this->_iters;
    }

    Complex Cell::getZ() {
        return this->_c;
    }

    void Cell::compute(MandelbrotConfiguration& config) {
        Complex z(0, 0);

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

    Cell* Grid::getpCell(unsigned int x, unsigned int y, MandelbrotConfiguration& c) {
        return &this->_pixels.at(c._height*y + x);
    }

    Grid::Grid(MandelbrotConfiguration& c) {
        this->_pixels = std::vector(
            c._height * c._width, Cell());
        this->compute(c);
    }

    Grid::Grid() {
        MandelbrotConfiguration c = MandelbrotConfiguration();
        this->_pixels = std::vector(
            c._height * c._width, Cell()
        );
        this->compute(c);
    }

    void Grid::compute(MandelbrotConfiguration& config) {
        for(unsigned int i = 0; i < config._width; i++) {
            for(unsigned int j = 0; j < config._height; j++) {
                Cell* current = this->getpCell(i, j, config);
                *current = Cell(DisplayCoordinate{i,j}, config);
                current->compute(config);
            }
        }   
        std::cout << "Min: " << config._renderMin << std::endl;
        std::cout << "Max: " << config._renderMax << std::endl;
    }

    void Grid::clear() {
        this->_pixels.clear();
        this->_pixels.shrink_to_fit();
    }
}