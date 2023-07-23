#include <complex>
#include <cmath>

#include "mandelbrot.hxx"

unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold) {
    std::complex<double> z(0, 0);

    for(int re = 0; re < iterations; ++re) {
        z = z*z + c;
        if (std::norm(z) > threshold) {
            return re;
        }
    }

    return 0;
}
