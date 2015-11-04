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

    Vector3d radiance(const Ray &ray, Random &random, const int depth)
    {
        // 背景は黒に指定
        const Vector3d backgroundColor = Vector3d(1.0, 1.0, 1.0);
        const int depthLimit = 10;
        // 打ち切り
        if (depth >= depthLimit)
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
        // 当たり判定確認
        // return Vector3d(1.0, 0.0, 0.0);
        
        const Material *material    = object->material();
        const Vector3d emission     = material->emission();
        if(emission.x > 0.0 || emission.y > 0.0 || emission.z > 0.0)
        {
            // 光源にあたった場合
            // 光源の反射率は0に設定している
            return emission;
        }

        // 次の方向をサンプリングする
        double pdf = -1;
        Vector3d brdfValue;
        const Vector3d dirOut = material->sample(random, ray.dir, hitpoint.normal, &pdf, &brdfValue);

        // cos項
        const double cost = dot(hitpoint.normal, dirOut);

        // レンダリング方程式をモンテカルロ積分で解いていく
        const Vector3d L = multiply(brdfValue, radiance(Ray(hitpoint.position, dirOut), random, depth + 1)) * cost / pdf;

        return L;
    }

};
#endif //_RADIANCE_H_
