#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <limits>
#include <cstdlib>

#include "constant.h"

namespace Intersection
{

    class XorShift
    {
    private:
        unsigned long long x;
    public:
        unsigned long long next(void)
        {
            x ^= x >> 12;
            x ^= x << 25;
            x ^= x >> 27;
            return x * 2685821657736338717LL;
        }

        double next01(void) {
            return (double)next() / std::numeric_limits<unsigned long long>::max();
        }

        // [min_value, max_value]
        double next(double min_value, double max_value) {
            const double inv = (max_value - min_value);
            return ((double)next() * (inv / std::numeric_limits<unsigned long long>::max())) + min_value;
        }

        XorShift(const unsigned long long initial_seed) {
            if (initial_seed == 0)
                x = 0xDEADBEEFDEADBEEF; // xorshift64*のseedは非ゼロでないといけない。
            else
                x = initial_seed;
        }

    };

    typedef XorShift Random;

};


#endif // _RANDOM_H_
