#ifndef _SCENE_H_
#define _SCENE_H_

#include "ray.h"
#include "constant.h"
#include "vector3d.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "object.h"
#include "material.h"
#include "light.h"
#include "lambertsimplematerial.h"

namespace Intersection
{
    class Scene
    {
    private:
        Sphere _sphere;
        const Material *_material;

    public:
    Scene(const Sphere &sphere, const Material *material) : _sphere(sphere), _material(material){}

        const Sphere* object() const
        {
            return &_sphere;
        }

        const Material* material() const
        {
            return _material;
        }

    };

    inline const Scene* renderScene(const Ray &ray, Hitpoint *hitpoint)
    {
//        Sphere  s1 = Sphere(Vector3d( 0,  0, 10), 1);
//        Plane   p1 = Plane(Vector3d(0, -10, 0), Vector3d(0, -1, 0));
//        Triangle t1 = Triangle(Vector3d(-1, -1, 5), Vector3d(1, -1, 5), Vector3d( 0, 1.5, 10));

        static const Scene scene[] =
            {
            Scene(Sphere(Vector3d( 0.0, -100000.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(Sphere(Vector3d( 0.0,  100004.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(Sphere(Vector3d(-100003.0,  0.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.1, 0.1))),
            Scene(Sphere(Vector3d( 100009.0,  0.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(Sphere(Vector3d(0.0,        0.0, -100003.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.1, 0.7, 0.1))),
            Scene(Sphere(Vector3d( 0.0,    103.99,       0.0), 100.0),      new Light                (Vector3d(8.0, 8.0, 8.0))),
            Scene(Sphere(Vector3d(-2.0,       1.0,       0.0), 1.0),        new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(Sphere(Vector3d( 2.0,       1.0,       0.0), 1.0),        new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.7))),
//            Scene(s1, new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7)))
//            Scene(p1, new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
//            Scene(t1, new LmabertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            };

        const int n = sizeof(scene) / sizeof(Scene);

        // 初期化
        *hitpoint = Hitpoint();
        const Scene *object = NULL;

        for(int i = 0 ; i < n ; ++i)
        {
            // TODO : sphere or plane で場合分け
            Hitpoint temp;
            if( scene[i].object()->isIntersect(ray, &temp) )
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
