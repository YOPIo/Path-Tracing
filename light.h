#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "material.h"
#include "vector3d.h"
#include "random.h"

#include <assert.h>

namespace RayTracing
{
    class Light : public Material
    {
    public:
        Light(const Vector3d &emission) : Material(emission, Vector3d()){}

        virtual Vector3d eval(const Vector3d &in, const Vector3d &normal, const Vector3d &out) const
        {
            assert(false);
            return Vector3d();
        }

        virtual Vector3d sample(Random &ramdom, const Vector3d &in, const Vector3d &normal, double *pdf, Vector3d *brdfValue) const
        {
            assert(false);
            return Vector3d();
        }

        virtual double evalPdf(const Vector3d &in, const Vector3d &normal, const Vector3d &out) const
        {
            assert(false);
            return -1.0;
        }

    };

};
#endif //_LIGHT_H_
