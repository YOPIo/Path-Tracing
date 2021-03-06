#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_

#include <cmath>
#include "constant.h"

namespace RayTracing
{

    struct Vector3d
    {
        double x, y, z;

        Vector3d(const double x = 0, const double y = 0, const double z = 0) : x(x), y(y), z(z) {}

        inline Vector3d operator + (const Vector3d &v) const
        {
            return Vector3d(x + v.x, y + v.y, z + v.z);
        }
        inline Vector3d operator - (const Vector3d &v) const
        {
            return Vector3d(x - v.x, y - v.y, z - v.z);
        }
        inline Vector3d operator * (const double a) const
        {
            return Vector3d(x * a, y * a, z * a);
        }
        inline Vector3d operator / (const double a) const
        {
            return Vector3d(x / a, y / a, z / a);
        }
        inline const double length_squared() const
        {
            return x*x + y*y + z*z;
        }
        inline Vector3d operator - () const
        {
            return Vector3d(-x, -y, -z);
        }
        inline const double length() const
        {
            return sqrt(length_squared());
        }
    };

    inline Vector3d operator * (const double a, const Vector3d &v)
    {
        return v * a;
    }

    inline Vector3d normalize(const Vector3d &v)
    {
        return v * (1.0 / v.length());
    }

    inline Vector3d multiply(const Vector3d &v1, const Vector3d &v2)
    {
        return Vector3d(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    inline double dot(const Vector3d &v1, const Vector3d &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    inline Vector3d cross(const Vector3d &v1, const Vector3d &v2)
    {
        return Vector3d(
                        (v1.y * v2.z) - (v1.z * v2.y),
                        (v1.z * v2.x) - (v1.x * v2.z),
                        (v1.x * v2.y) - (v1.y * v2.x));
    }

    
    inline Vector3d reflect(const Vector3d &in, const Vector3d &normal)
    {
        return normalize(in - normal * 2.0 * dot(normal, in));
    }

    // 正規直交基底
    inline void orthoNormalBasis(const Vector3d &normal, Vector3d *tangent, Vector3d *binormal)
    {
        // tangent(接線ベクトル)
        if (std::abs(normal.x) > std::abs(normal.y))
        {
            *tangent = normalize(cross(Vector3d(0, 1, 0), normal));
        }
        else
        {
            *tangent = normalize(cross(Vector3d(1, 0, 0), normal));
        }
        // binormal(従法線ベクトル)
        
        *binormal = normalize(cross(normal, *tangent));
    }

};
#endif // _VECTOR3D_H_
