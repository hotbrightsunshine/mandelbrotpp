#include "mandelbrot.hxx"

namespace mandel {

    typedef std::vector<std::vector<Cell>> Record2DArray;

    struct Color {
        unsigned int r;
        unsigned int g;
        unsigned int b;
    };

    class MandelbrotDisplay {
        private:
            Record2DArray _pixels;
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