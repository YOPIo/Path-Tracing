//
//  render.h
//  RayIntersection
//
//  Created by YOPIo on 2015/10/27.
//  Copyright (c) 2015年 YOPIo. All rights reserved.
//

#ifndef _RENDER_H_
#define _RENDER_H_

#include "vector3d.h"
#include "constant.h"
#include "hitpoint.h"
#include "ray.h"
#include "scene.h"
#include "radiance.h"
#include "ppm.h"

namespace Intersection
{
    
    
    int render(const char* filename, const int width, const int height)
    {
        // レンダーした結果を格納する
        // RGBの3構成になるのでVector3d型を流用する
        Vector3d *image = new Vector3d[height * width];
        
        // カメラ位置
        const Vector3d cameraPosition = Vector3d(0.0f, 0.0f, -5.0f);
        

        for(int y = 0 ; y < height ; ++y)
        {
            for(int x = 0 ; x < width ; ++x)
            {
                const int index = (height - y - 1) * width + x;
                
                // 2次元スクリーンを3次元に変換する
                const double sx = (2.0 * x / (width - 1)) - 1;
                const double sy = (-2.0 * y / (height - 1)) + 1;
                const double sz = 0.0f;
                Vector3d screenPosition = Vector3d(sx, sy, sz);

                // レイを飛ばす方向ベクトルを決定する
                const Vector3d rayDirection = normalize(screenPosition - cameraPosition);
                
                image[index] = radiance(Ray(cameraPosition, rayDirection));
            }
        }
        saveImage(filename, image, width, height);
        return 0;
    }
    
    
};


#endif // _RENDER_H_
