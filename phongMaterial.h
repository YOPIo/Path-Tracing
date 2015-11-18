#ifndef _PHONGEMATERIAL_H_
#define _PHONGEMATERIAL_H_

#include "material.h"
#include "random.h"
#include "vector3d.h"
#include "constant.h"
#include "sampling.h"

namespace RayTracing
{
    
    class PhongMaterial : public Material
    {
    private:
        double _n;
    protected:
    public:
        PhongMaterial(const Vector3d &reflectance, const double n) : Material(Vector3d(), reflectance), _n(n){}
        
        virtual Vector3d eval(const Vector3d &in, const Vector3d &normal, const Vector3d &out) const
        {
            if( dot(normal, out) < 0.0 )
            {
                // 反射方向が下を向いている場合は0
                return Vector3d();
            }
            
            const Vector3d reflectionDir = reflect(in, normal);
            
            double cosa = dot(reflectionDir, out);
            if(cosa < 0.0)
            {
                cosa = 0.0;
            }
            return reflectionDir * (_n + 2.0) / (2.0 * PI) * pow(cosa, _n);
        }
        
        virtual Vector3d sample(Random &random, const Vector3d &in, const Vector3d &normal, double *pdf, Vector3d *brdfValue) const
        {
            Vector3d dir, tangent, binormal;
            
            const Vector3d reflectionDir = reflect(in, normal);
            
            orthoNormalBasis(reflectionDir, &tangent, &binormal);
            
            const double u1 = random.next01();
            const double u2 = random.next01();
            
            const double phi    = u1 * 2.0 * PI;
            const double theta  = acos( pow(u2, 1 / (_n + 1)) );
            
            dir =  tangent * sin(theta) * cos(phi) + reflectionDir * cos(theta) + binormal * sin(theta) * cos(phi);
            
            if(pdf != NULL)
            {
                double cosa = dot(reflectionDir, dir);
                if(cosa < 0.0)
                {
                    cosa = 0.0;
                }
                *pdf = (_n + 1.0) / (2.0 * PI) * pow(cosa, _n);
            }
            
            if(brdfValue != NULL)
            {
                *brdfValue = eval(in, normal, dir);
            }
            
            return dir;
        }

    };

};


#endif // _PHONGEMATERIAL_H_