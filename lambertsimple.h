#ifndef _LAMBERT_H_
#define _LAMBERT_H_

#include "material.h"
#include "random.h"
#include "vector3d.h"
#include "constant.h"

namespace Intersection
{
    class LambertSimple : public Material
    {
    protected:
    public:
        LambertSimple(const Vector3d &reflectance) : Material(Vector3d(), reflectance){};
        // lambert BRDF ρ/π ρは[0, 1]の反射率
        virtual Vector3d eval(const Vector3d &in, const Vector3d &out)
        {
            return _reflectance / PI;
        }
        // 半球一様にサンプリング
        virtual Vector3d sample(Random &random, const Vector3d &in, const Vector3d &normal, double *pdf, Vector3d *brdfValue)
        {
            Vector3d binormal, tangent, nowNormal = normal;
            orthoNormalBasis(nowNormal, &tangent, &binormal);
            const Vector3d dir;
        }

    };
};

#endif // _LAMBERT_H_