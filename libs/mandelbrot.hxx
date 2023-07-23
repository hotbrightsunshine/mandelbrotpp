#include <complex>
#include <cmath>


unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold);

struct record {
    std::complex<double> z;
    unsigned int iters;
};
