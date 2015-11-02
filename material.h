#ifndef _MATERIALE_H_
#define _MATERIALE_H_

#include "random.h"
#include "vector3d.h"
#include "constant.h"

namespace Intersection
{
    class Material
    {
    protected:
        Vector3d _emission;
        Vector3d _reflectance;
    public:
        Material(const Vector3d& emission, const Vector3d &reflectance) : _emission(emission), _reflectance(reflectance){}

        virtual Vector3d emission() const
        {
            return _emission;
        }
        virtual Vector3d reflectance() const
        {
            return _reflectance;
        }
        virtual Vector3d eval(const Vector3d &in, const Vector3d &normal, const Vector3d &out) const = 0;
        virtual Vector3d sample(Random &ramdom, const Vector3d &in, const Vector3d &normal, double *pdf, Vector3d *brdfValue) const = 0;
    };
};
#endif // _MATERIAL_H_
