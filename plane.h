#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector3d.h"
#include "ray.h"
#include "hitpoint.h"

namespace RayTracing
{
    class Plane
    {
    private:
        Vector3d _position;
        Vector3d _normal;
    public:
        Plane(const Vector3d position, const Vector3d normal) : _position(position), _normal(normal){}
        
        // 球体と同様に陰関数から衝突判定を行う
        inline bool isIntersect(const Ray &ray, Hitpoint *hitpoint) const
        {
            // 法線をそのまま適応する
            hitpoint->normal = normalize(_normal);
            
            // 自己判定用
            const double EPS = 1e-6;
            
            const double p2n = dot(_position, _normal);
            const double o2n = dot(ray.org, _normal);
            const double d2n = dot(ray.dir, _normal);
            
            // 0除算回避
            if(d2n < EPS)
            {
                return false;
            }
            
            const double t = (p2n - o2n) / d2n;
            
            // t = 0のときはレイの視点が平面上にある場合
            // t < 0はレイの逆方向であるため交点を持たない
            // 自己判定を避けるため、微小範囲内の場合は交差していないと判定する
            if(t < EPS)
            {
                return false;
            }
            hitpoint->distance = t;
            hitpoint->position = ray.org + hitpoint->distance * ray.dir;
            return true;
        }
    };
};


#endif // _PLANE_H_
