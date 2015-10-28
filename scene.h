//
//  scene.h
//  RayIntersection
//
//  Created by YOPIo on 2015/10/27.
//  Copyright (c) 2015年 YOPIo. All rights reserved.
//

#ifndef _SCENE_H_
#define _SCENE_H_

#include "ray.h"
#include "constant.h"
#include "vector3d.h"
#include "sphere.h"
#include "plane.h"

namespace Intersection
{
    class Scene
    {
    private:
        Sphere _sphere;
        
    public:
        Scene(const Sphere &sphere) : _sphere(sphere){}
        
        const Sphere* getSphere() const
        {
            return &_sphere;
        }
        /*
        const Plane* getPlane() const
        {
            return &_plane;
        }
         */
    };
    
    inline const Scene* renderScene(const Ray &ray, Hitpoint *hitpoint)
    {
        Sphere  s1 = Sphere(Vector3d( 0,  0, 15), 1);
        Plane   p1 = Plane(Vector3d(0, -1, 0), Vector3d(0, 1, 0));
        static const Scene scene[] =
        {
            Scene(s1),
            //Scene(p1),
        };
        
        const int n = sizeof(scene) / sizeof(Scene);
        
        // 初期化
        *hitpoint = Hitpoint();
        const Scene *object = NULL;
        
        for(int i = 0 ; i < n ; ++i)
        {
            // TODO : sphere or plane で場合分け
            Hitpoint temp;
            if( scene[i].getSphere()->isIntersect(ray, &temp) )
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
