#ifndef _SAMPLING_H_
#define _SAMPLING_H_

#include "vector3d.h"
#include "random.h"
#include "constant.h"

namespace Intersection
{
    class Sampling
    {
    public:
        static Vector3d uniformHemisphereSurface(Random &random, const Vector3d &normal, const Vector3d &tangent, const Vector3d &binormal)
        {
            const double tz     = random.next(0.0, 1.0);
            const double phi    = random.next(0.0, 2.0 * PI);
            const double k      = sqrt(1.0 - tz * tz);
            const double tx     = k * cos(phi);
            const double ty     = k * sin(phi);

            return tz * normal + tx * tangent + ty * binormal;
        }
    };
};
#endif //_SAMPLING_H_
