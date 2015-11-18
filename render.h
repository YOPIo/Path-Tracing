#ifndef _RENDER_H_
#define _RENDER_H_

#ifdef _OPENMP
#include <omp.h>
#endif // _OPENMP

#include <iostream>
#include <time.h>

#include "vector3d.h"
#include "constant.h"
#include "hitpoint.h"
#include "ray.h"
#include "scene.h"
#include "radiance.h"
#include "random.h"
#include "ppm.h"

namespace RayTracing
{
    int render(const char* filename, const int width, const int height, const int samplePerSubpixel, const int subpixel, const int thread)
    {
        #ifdef _OPENMP
        omp_set_num_threads(thread);
        #endif //_OPENMP

        // レンダーした結果を格納する
        // RGBの3構成になるのでVector3d型を流用
        Vector3d *image = new Vector3d[height * width];

        // カメラ位置
        const Vector3d cameraPosition = Vector3d(0.0, 0.0, 8.0);
        const Vector3d cameraLookat   = Vector3d(0.0, 0.0, 0.0);
        const Vector3d cameraDir      = normalize(cameraLookat - cameraPosition);
        const Vector3d cameraUp       = Vector3d(0.0, 1.0, 0.0);

        // ワールド座標系でのイメージセンサーの大きさ
        const double sensorWidth  = 30.0 * width / height; // アスヒの調整
        const double sensorHeight = 30.0;
        // イメージセンサーまでの距離
        const double sensorDist = 45.0;
        // イメージセンサーを張るベクトル
        const Vector3d sensorVectorX = normalize(cross(cameraDir, cameraUp)) * sensorWidth;
        const Vector3d sensorVectorY = normalize(cross(sensorVectorX, cameraDir)) * sensorHeight;
        const Vector3d sensorCenter  = cameraPosition + cameraDir * sensorDist;

        std::cout << "start rendering" << std::endl;
        time_t start = time(NULL);


        for(int y = 0 ; y < height ; ++y)
        {
            std::cerr << "Rendering (y = " << y << ", " << (100.0 * y / (height - 1)) << " %)          \r";

            #pragma omp parallel for schedule(static) // OpenMP
            for(int x = 0 ; x < width ; ++x)
            {
                const int index = (height - y - 1) * width + x;
                Random random(y * width + x + 1);

                // subpixel * subpixelのサンプリングをする
                for (int sy = 0; sy < subpixel; ++sy)
                {
                    // subpixelのサンプリング
                    for (int sx = 0; sx < subpixel; ++sx)
                    {
                        Vector3d accumulatedRadiance = Vector3d();
                        // 1つのサブピクセルに対してsample回サンプリングをする
                        for(int s = 0 ; s < samplePerSubpixel ; ++s)
                        {
                            const double rate = (1.0 / subpixel);
                            const double r1 = sx * rate + rate / 2.0;
                            const double r2 = sy * rate + rate / 2.0;
                            // イメージセンサー上の位置
                            const Vector3d OnSensorPosition = sensorCenter + sensorVectorX *((r1 + x) / width - 0.5) + sensorVectorY * ((r2 + y) / height - 0.5);
                            // レイを飛ばす方向ベクトルを決定
                            const Vector3d rayDirection = normalize(OnSensorPosition - cameraPosition);

                            accumulatedRadiance = accumulatedRadiance +
                                radiance(Ray(cameraPosition, rayDirection), random, 0) /
                                static_cast<double>(samplePerSubpixel) /
                                static_cast<double>(subpixel * subpixel);
                        }
                        image[index] = image[index] + accumulatedRadiance;
                    }
                }
            }
        }
        saveImage(filename, image, width, height);
        delete[] image;


        time_t end = time(NULL);
        std::cout << "\nRender finished.\n";
        std::cout << "Time : " << difftime(end, start) << "sec. \n";


        return 0;
    }

};


#endif // _RENDER_H_
