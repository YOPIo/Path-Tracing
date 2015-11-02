#ifndef _LAMBERT_H_
#define _LAMBERT_H_

#include <iostream>

#include "material.h"
#include "random.h"
#include "vector3d.h"
#include "constant.h"
#include "sampling.h"

namespace Intersection
{
    class LambertSimpleMaterial : public Material
    {
    private:
    protected:
    public:
        LambertSimpleMaterial(const Vector3d &reflectance) : Material(Vector3d(), reflectance){};

        // lambert BRDF ρ/π でρは[0, 1]を返す反射率
        virtual Vector3d eval(const Vector3d &in, const Vector3d &normal, const Vector3d &out) const
        {
            return _reflectance / PI;
        }

        // 半球一様サンプリングを行う
        virtual Vector3d sample(Random &random, const Vector3d &in, const Vector3d &normal, double *pdf, Vector3d *brdfValue) const
        {
            Vector3d binormal, tangent, nowNormal = normal;

            // 正規直交基底を作る
            orthoNormalBasis(nowNormal, &tangent, &binormal);
            // 次に反射する方向を計算する
            const Vector3d dir = Sampling::uniformHemisphereSurface(random, nowNormal, tangent, binormal);

            //pdf : 1 / (2 * pi)
            if (pdf != NULL)
            {
                *pdf = 1.0 / (2.0 * PI);
            }
            if(brdfValue != NULL)
            {
                *brdfValue = eval(in, normal, dir);
            }

            return dir;
        }
    };
};

#endif // _LAMBERT_H_
