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
        //std::vector<Cell*> renderable = this->_grid.renderCandidates(this->_config);
        //int width = this->_config._width / this->_config._scaleFactor;
        //int height = this->_config._height / this->_config._scaleFactor;

        for(unsigned int y=0; y< this->_config._width; ++y) {
            for (unsigned int x=0; x< this->_config._height; ++x) {
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

        ComplexNumber newMin =  ComplexNumber(
            this->_config._renderMin.real() * _zoomCoefficient,
            this->_config._renderMin.imag() * _zoomCoefficient
        );
        ComplexNumber newMax = ComplexNumber(
            this->_config._renderMax.real() * _zoomCoefficient,
            this->_config._renderMax.imag() * _zoomCoefficient
        );
        this->_config._renderMin = newMin;
        this->_config._renderMax = newMax;
    }

    void MandelbrotDisplay::translate(Direction d) {
        ComplexNumber* min = &this->_config._renderMin;
        ComplexNumber* max = &this->_config._renderMax;

        ComplexNumber delta(
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
        this->_c = ComplexNumber(0, 0);
    }

    Cell::Cell(ComplexNumber z) {
        this->_c = z;
        this->_iters = 0;
    }

    Cell::Cell(DisplayCoordinate i, MandelbrotConfiguration& c) {
        this->_c = Cell::_fromCoordinates(i, c);
        this->_iters = 0;
    }

    ComplexNumber Cell::_fromCoordinates(DisplayCoordinate i, MandelbrotConfiguration& c) {
        double real = Cell::_coordFunction(double(c._width), c._renderMin.real(), c._renderMax.real(), i.x);
        double imag = Cell::_coordFunction(double(c._height), c._renderMin.imag(), c._renderMax.imag(), i.y);
        return ComplexNumber(real, imag);
    }

    double Cell::_coordFunction(double w, double a, double c, double x) {
        return a + (c - a) * (2 * x - (std::abs(a) + std::abs(c))) / (2 * w); 
    }

    unsigned int Cell::getIters() {
        return this->_iters;
    }

    ComplexNumber Cell::getComplex() {
        return this->_c;
    }

    void Cell::setComplex(ComplexNumber c) {
        this->_c = c;
    }

    void Cell::setComplex(DisplayCoordinate i, MandelbrotConfiguration& c) {
        this->_c = Cell::_fromCoordinates(i, c);
    }

    void Cell::setIters(unsigned int i) {
        this->_iters = i;
    }

    void Cell::compute(MandelbrotConfiguration& config) {
        ComplexNumber z(0, 0);

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
        std::vector<Cell*> candidates = renderCandidates(config);

/*      for(unsigned int i = 0; i < config._width; i++) {
            for(unsigned int j = 0; j < config._height; j++) {
                Cell* current = this->getpCell(i, j, config);
                current->setComplex(
                    DisplayCoordinate{i,j}, config
                );
                current->compute(config);
            }
        }   */

        for(Cell* candidate : candidates) {
            candidate->compute(config);
        }
    }

    inline std::vector<Cell*> Grid::renderCandidates(MandelbrotConfiguration& c) {
        std::vector<Cell*> toRender{};
        unsigned int iters{0};
        for(unsigned int x = 0; x < c._width; x++) {
            for(unsigned int y = 0; y < c._height; y++) {
                int remainderx = x%c._scaleFactor;
                int remaindery = y%c._scaleFactor;
                Cell* currentCell = this->getpCell(x, y, c);
                if (remainderx == 0 && remaindery == 0) {
                    currentCell->setComplex(
                        DisplayCoordinate{x, y}, c
                    );
                    currentCell->compute(c);
                    toRender.push_back(currentCell);

                for (unsigned int subX = 0; subX < c._scaleFactor; ++subX) {
                    for (unsigned int subY = 0; subY < c._scaleFactor; ++subY) {
                        this->getpCell(x+subX, y+subY, c)->setIters(currentCell->getIters());
                    }
                }
                }
            }
        }
        return toRender;
    }

    void Grid::clear() {
        this->_pixels.clear();
        this->_pixels.shrink_to_fit();
    }
}