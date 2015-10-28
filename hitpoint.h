//
//  hitpoint.h
//  RayIntersection
//
//  Created by YOPIo on 2015/10/27.
//  Copyright (c) 2015年 YOPIo. All rights reserved.
//

#ifndef _HITPINT_H_
#define _HITPINT_H_

#include "vector3d.h"

namespace Intersection
{
    
    struct Hitpoint{
        double distance;
        Vector3d position, normal;
        Hitpoint() : distance(INF), position(), normal(){}
    };

};


#endif // _HITPINT_H_
