#include "mandelbrot.hxx"

namespace mandel {
    class Cell {
        private: 
            C _z;
            unsigned int _iters;
            /**
             * This method converts SDL's (X;Y) coordinates into the (Re;Im) coordinates of the complex plane 
            */
            static C _fromCoordinates(DisplayCoordinate i, MandelbrotConfiguration c);
            static double _coordFunction(double w, double a, double c, double x);

        public:
            Cell(C z);
            Cell(DisplayCoordinate i, MandelbrotConfiguration c);
            Cell();

            void compute(MandelbrotConfiguration C); // compute the mandelbrot calculation = is in set

            unsigned int getIters();
            C getZ();

    };
}