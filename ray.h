#ifndef _RAY_H_
#define _RAY_H_

#include "vector3d.h"
#include "constant.h"

namespace Intersection
{
    struct Ray
    {
        Vector3d org, dir;
        Ray(const Vector3d &org, const Vector3d &dir) : org(org), dir(dir){}
    };
};


#endif // _RAY_H_
