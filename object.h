#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "hitpoint.h"

namespace Intersection
{
    class Object
    {
    private:
    protected:
    public:
        virtual bool isIntersect(const Ray&, Hitpoint*) const = 0;
    };
};
#endif //_OBJECT_H_
