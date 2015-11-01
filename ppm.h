#ifndef _PPM_H_
#define _PPM_H_

#include <cstdlib>
#include <cstdio>
#include "vector3d.h"

namespace Intersection {
    
    inline double clamp(double x)
    {
        if(x < 0.0)
        {
            return 0.0f;
        }
        if(x > 1.0)
        {
            return 1.0f;
        }
        return x;
    }
    
    inline int HDR2LDR(double x)
    {
        // ウィンドウのガンマ値が2.2であることを想定
        return static_cast<int>( pow(clamp(x), 1/2.2) * 255 + 0.5 );
    }
    
    inline void saveImage(const char* filename, const Vector3d *image, const int width, const int height)
    {
        FILE *f = fopen(filename, "wb");
        fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
        for (int i = 0; i < width * height; i++)
        {
            fprintf(f,"%d %d %d ", HDR2LDR(image[i].x), HDR2LDR(image[i].y), HDR2LDR(image[i].z));
        }
        fclose(f);
    }
    

};


#endif //_PPM_H_
