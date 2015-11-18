#ifndef _SAMPLING_H_
#define _SAMPLING_H_

#include "vector3d.h"
#include "random.h"
#include "constant.h"

namespace RayTracing
{
    class Sampling
    {
    public:
        static Vector3d uniformHemisphereSurface(Random &random, const Vector3d &normal, const Vector3d &tangent, const Vector3d &binormal)
        {
            // 適当にランダム値でサンプリングを行う
            const double tz     = random.next(0.0, 1.0);
            const double phi    = random.next(0.0, 2.0 * PI);
            const double k      = sqrt(1.0 - tz * tz);
            const double tx     = k * cos(phi);
            const double ty     = k * sin(phi);

            return tz * normal + tx * tangent + ty * binormal;
        }
        
        static Vector3d cosineWeightHemisphereSurface(Random &random, const Vector3d &normal, const Vector3d &tangent, const Vector3d &binormal)
        {
            /*
             あってるかわからないけどおそらく以下の式から値を求めている
             F(φ) = φ / (2 * PI)
             ->
                φ = 2 * PI * r1
             
             F(θ)   = 1 - cos^2(θ)
                    = sin^2(θ)
             ->
                θ = arcsin(√r2)
             1次近似して
                θ = √r2
            */
            
            const double phi    = random.next(0.0, 2.0 * PI); // r1
            const double r2     = random.next01();
            const double r2s    = sqrt(r2);
            
            const double tx     = r2s * cos(phi);
            const double ty     = r2s * sin(phi);
            const double tz     = sqrt(1 - r2);
            
            return  tz * normal + tx *tangent + ty * binormal;
        }
    };
};
#endif //_SAMPLING_H_
