#ifndef _SCENE_H_
#define _SCENE_H_

#include "ray.h"
#include "constant.h"
#include "vector3d.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "object.h"

namespace Intersection
{
    class Scene
    {
    private:
        Sphere _sphere;
    public:
        Scene(const Sphere &sphere) : _triangle(sphere){}

        const Sphere* getObject() const
        {
            return &_sphere;
        }

    };
    
    inline const Scene* renderScene(const Ray &ray, Hitpoint *hitpoint)
    {
        Sphere  s1 = Sphere(Vector3d( 0,  0, 10), 1);
//        Plane   p1 = Plane(Vector3d(0, -10, 0), Vector3d(0, -1, 0));
//        Triangle t1 = Triangle(Vector3d(-1, -1, 5), Vector3d(1, -1, 5), Vector3d( 0, 1.5, 10));
        
        static const Scene scene[] =
        {
            Scene(s1),
//            Scene(p1),
//            Scene(t1),
        };
        
        const int n = sizeof(scene) / sizeof(Scene);
        
        // 初期化
        *hitpoint = Hitpoint();
        const Scene *object = NULL;
        
        for(int i = 0 ; i < n ; ++i)
        {
            // TODO : sphere or plane で場合分け
            Hitpoint temp;
            if( scene[i].getObject()->isIntersect(ray, &temp) )
            {
                if( temp.distance < hitpoint->distance )
                {
                    *hitpoint = temp;
                    object = &scene[i];
                }
            }
        }
        return object;
    }
};

#endif // _SCENE_H_
