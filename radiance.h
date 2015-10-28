//
//  radiance.h
//  RayIntersection
//
//  Created by YOPIo on 2015/10/27.
//  Copyright (c) 2015年 YOPIo. All rights reserved.
//

#ifndef _RADIANCE_H_
#define _RADIANCE_H_

#include "ray.h"
#include "hitpoint.h"
#include "vector3d.h"
#include "sphere.h"
#include "scene.h"

namespace Intersection {
    
    Vector3d radiance(const Ray &ray)
    {
        Hitpoint hitpoint;
        const Scene *scene = renderScene(ray, &hitpoint);
        
        if(scene == NULL) // 交差していない
        {
            return Vector3d(0, 0, 0);
        }
        
        return Vector3d(255, 0, 0);
    }

};


#endif //_RADIANCE_H_
