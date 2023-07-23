#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <format>

class record {
    public:
        std::complex<double> z;
        unsigned int iters;
        unsigned int x;
        unsigned int y;

        record(std::complex<double> z, unsigned int x, unsigned int y, unsigned int iters);
        record(std::complex<double> z, unsigned int x, unsigned int y);
        record();
};

// Synonyms
typedef std::complex<double> C;
typedef std::vector<std::vector<record>> Record2DArray;

// Methods
unsigned int is_in_set(std::complex<double> c, unsigned int iterations, double threshold);
Record2DArray get_map(unsigned int height, unsigned int width, C min, C max);
