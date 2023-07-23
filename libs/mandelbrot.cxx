#include <complex>
#include <cmath>
#include <vector>

#include "mandelbrot.hxx"

record::record(std::complex<double> z, unsigned int x, unsigned int y, unsigned int iters) {
    this->z = z;
    this->x = x;
    this->y = y;
    this->iters = iters;
};

record::record(std::complex<double> z, unsigned int x, unsigned int y) {
    this->z = z;
    this->x = x;
    this->y =  y;
    this->iters = 0;
};

record::record() {
    this->z = C(0, 0);
    this->x = 0;
    this->y =  0;
    this->iters = 0;
};

unsigned int is_in_set(C c, unsigned int iterations, double threshold) {
    C z(0, 0);

    for(int re = 0; re < iterations; ++re) {
        z = z*z + c;
        if (std::norm(z) > threshold) {
            return re;
        }
    }

    return 0;
}

Record2DArray get_map(unsigned int height, unsigned int width, C min, C max ) {
    Record2DArray map = Record2DArray(height);
    for (std::vector<record> row : map) {
        row = std::vector<record>(width);
    }

    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {

            C c_dimension = C(
                std::abs(min.real()) + std::abs(max.real()),
                std::abs(min.imag()) + std::abs(min.imag())
            );

            double x_percentage = double(width) - (c_dimension.real() / 2) / double(width);
            double y_percentage = double(height) - (c_dimension.imag() / 2) / double(height);

            double re = std::lerp(min.real(), max.real(), x_percentage);
            double im = std::lerp(min.imag(), max.imag(), y_percentage);

            map[x][y] = record(C(re, im), x, y);
        }
    }

    return map;
}
