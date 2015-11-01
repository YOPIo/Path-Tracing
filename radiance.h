#ifndef _RADIANCE_H_
#define _RADIANCE_H_

#include "ray.h"
#include "hitpoint.h"
#include "vector3d.h"
#include "sphere.h"
#include "triangle.h"
#include "material.h"
#include "scene.h"

#include <cstdio>

namespace Intersection {
    
    Vector3d radiance(const Ray &ray, Random random, const int depth)
    {
        // 背景は黒に指定
        const Vector3d backgroundColor = Vector3d(0.0, 0.0, 0.0);
        const int depthLimit = 10;
        // 打ち切り
        if (depth > depthLimit)
        {
            return Vector3d();
        }

        // ここからシーンの交差判定
        Hitpoint hitpoint;
        const Scene *object = renderScene(ray, &hitpoint);
        // 交差していないので背景色を返す
        if(object == NULL)
        {
            return backgroundColor;
        }
        
        const Material *material;
        const Color emission = material->emission();


        return Vector3d(255.0 , 0, 0);
    }

};


#endif //_RADIANCE_H_
