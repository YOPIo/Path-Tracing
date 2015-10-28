//
//  sphere.h
//  RayIntersection
//
//  Created by YOPIo on 2015/10/27.
//  Copyright (c) 2015年 YOPIo. All rights reserved.
//

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vector3d.h"
#include "hitpoint.h"
#include "ray.h"

namespace Intersection
{
    class Sphere
    {
    private:
        Vector3d _position;
        double _radius;
        
    public:
        Sphere(const Vector3d position, const double radius) : _position(position), _radius(radius){}
        
        inline bool isIntersect(const Ray &ray, Hitpoint *hitpoint) const
        {
            // 自己交差の判定用定数。
            const double kEPS = 1e-6;
            
            const Vector3d o_to_p = _position - ray.org;
            const double b = dot(o_to_p, ray.dir);
            const double c = b * b - dot(o_to_p, o_to_p) + _radius * _radius;
            
            if (c < 0.0)
                return false;
            
            const double sqrt_c = sqrt(c);
            const double t1 = b - sqrt_c, t2 = b + sqrt_c;
            
            // 微小距離内だったら交差しないとする（自己交差を避けるため）。
            if (t1 < kEPS && t2 < kEPS)
                return false;
            
            // 交差するときは二点以上で交差する。（接する場合は一点）
            // 近い方を交差点とする。また、負値の場合はレイの逆方向で交差してるため交差していないとする。
            if (t1 > kEPS) {
                hitpoint->distance = t1;
            } else {
                hitpoint->distance = t2;
            }
            
            hitpoint->position = ray.org + hitpoint->distance * ray.dir;
            hitpoint->normal   = normalize(hitpoint->position - _position);
            return true;
        }
    
    };
};


#endif // _SPHERE_H_
