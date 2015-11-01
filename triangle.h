#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "scene.h"
#include "vector3d.h"
#include "ray.h"
#include "hitpoint.h"
#include "object.h"

#include <stdio.h>

namespace Intersection
{
    class Triangle : public Object
    {
    private:
        Vector3d _vertex0, _vertex1, _vertex2;
    public:
        Triangle(Vector3d p0, Vector3d p1, Vector3d p2) : _vertex0(p0), _vertex1(p1), _vertex2(p2){}
        
        
        // Fast, Minimum Storage Ray/Triangle Intersection
        inline bool isIntersect(const Ray &ray, Hitpoint *hitpoint) const
        {
            // 自己判定用
            double EPS = 1e-6;
            
            // _vertex0が共有している2つのエッジを求める
            Vector3d edge0 = _vertex1 - _vertex0;
            Vector3d edge1 = _vertex2 - _vertex0;
            
            // determinantを計算
            Vector3d p = cross(ray.dir, edge1);
            
            // detが0に近い場合はrayは三角形の面内で交わっている
            double det = dot(edge0, p);
            if(-EPS < det && det < EPS)
            {
                return false;   // 交わらない
            }
            
            double invDet = 1.0 / det;
            
            // レイの光源から_vertex0までのベクトルを求める
            Vector3d t = ray.org - _vertex0;
            
            double u = dot(t, p) * invDet;
            if(u < 0.0 || u > 1.0)
            {
                return false;
            }
            
            Vector3d q = cross(t, edge0);
            double v = dot(ray.dir, q) * invDet;
            if(v < 0.0 || u + v > 1.0)
            {
                return false;
            }
            
            // 交点を求める
            hitpoint->distance = dot(edge1, q) * invDet; // t
            hitpoint->position = ray.org + hitpoint->distance * ray.dir;

            // 法線を求める
            hitpoint->normal = cross((_vertex1 - _vertex0), (_vertex2 - _vertex0)) / ( cross(_vertex1 - _vertex0, _vertex2 - _vertex0).length() );
            return true;
        }
        
    };
    
};


#endif //_TRIANGLE_H_
