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
    protected:
        const Material *_material;
        const Object *_object;

    public:
    Scene(const Object *object, const Material *material) : _object(object), _material(material){}
        
        const Object* object() const
        {
            return _object;
        }

        const Material* material() const
        {
            return _material;
        }
    };

    inline const Scene* renderScene(const Ray &ray, Hitpoint *hitpoint)
    {

        static const Scene scene[] =
        {
            Scene(new Sphere(Vector3d( 0.0, -100000.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(new Sphere(Vector3d( 0.0,  100004.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(new Sphere(Vector3d(-100003.0,  0.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.1, 0.1))),
            Scene(new Sphere(Vector3d( 100009.0,  0.0,       0.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(new Sphere(Vector3d(0.0,        0.0, -100003.0), 100000.0),   new LambertSimpleMaterial(Vector3d(0.1, 0.7, 0.1))),
            Scene(new Sphere(Vector3d( 0.0,    103.99,       0.0), 100.0),      new Light                (Vector3d(8.0, 8.0, 8.0))),
            Scene(new Sphere(Vector3d(-2.0,       1.0,       0.0), 1.0),        new LambertSimpleMaterial(Vector3d(0.7, 0.7, 0.7))),
            Scene(new Sphere(Vector3d( 2.0,       1.0,       0.0), 1.0),        new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.7))),
        };
        
        static const Scene cornellBox[] =
        {
            // Light
            Scene(new Sphere    ( Vector3d( 0.0, 103.99, 0.0), 100.0), new Light(Vector3d(8.0, 8.0, 8.0)) ),
            
            // Sphere
            Scene(new Sphere    ( Vector3d( 1.0,  -1.0,  1.1), 0.8), new LambertSimpleMaterial (Vector3d(0.1, 0.7, 0.1)) ),
            Scene(new Sphere    ( Vector3d(-1.0,  -1.0, -0.8), 0.8), new LambertSimpleMaterial (Vector3d(0.7, 0.1, 0.1)) ),
            
            // Box 反時計回りに頂点を置く
            // left side
            Scene(new Triangle  ( Vector3d(-2.0,  2.0, -2.0), Vector3d(-2.0,  2.0,  2.0), Vector3d(-2.0, -2.0, -2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.7, 0.1)) ),
            Scene(new Triangle  ( Vector3d(-2.0, -2.0, -2.0), Vector3d(-2.0,  2.0,  2.0), Vector3d(-2.0, -2.0,  2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.7, 0.1)) ),
            
            // right side
            /*
            Scene(new Triangle  ( Vector3d( 2.0, 2.0,  2.0), Vector3d( 2.0,  2.0, -2.0), Vector3d( 2.0, -2.0, -2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.7, 0.1, 0.1)) ),
             */
            Scene(new Triangle  ( Vector3d( 2.0, 2.0,  2.0), Vector3d( 2.0, -2.0, -2.0), Vector3d( 2.0, -2.0,  2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.7, 0.1, 0.1)) ),

            /*
            // top
            Scene(new Triangle  ( Vector3d( 2.0, 2.0, 2.0), Vector3d(-2.0, 2.0, 2.0), Vector3d(-2.0, 2.0, -2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),
            Scene(new Triangle  ( Vector3d( 2.0, 2.0, 2.0), Vector3d(-2.0, 2.0, -2.0), Vector3d(2.0, 2.0, -2.0) ),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),
            */
            
            // center
            Scene(new Triangle(Vector3d(2.0, 2.0, -2.0), Vector3d(-2.0, 2.0, -2.0), Vector3d(-2.0, -2.0, -2.0)),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),
            Scene(new Triangle(Vector3d(2.0, 2.0, -2.0), Vector3d(-2.0, -2.0, -2.0), Vector3d(2.0, -2.0, -2.0)),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),

            /*
            // bottom
            Scene(new Triangle(Vector3d( 2.0, -2.0, -2.0), Vector3d(-2.0, -2.0, -2.0), Vector3d(-2.0, -2.0, 2.0)),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),
            Scene(new Triangle(Vector3d( 2.0, -2.0, -2.0), Vector3d(-2.0, -2.0, 2.0), Vector3d(2.0, -2.0,  2.0)),
                  new LambertSimpleMaterial(Vector3d(0.1, 0.1, 0.1)) ),
            */
        };
        
        const int n = sizeof(cornellBox) / sizeof(Scene);

        // 初期化
        *hitpoint = Hitpoint();
        const Scene *object = NULL;

        for(int i = 0 ; i < n ; ++i)
        {
            Hitpoint temp;
            if( cornellBox[i].object()->isIntersect(ray, &temp) )
            {
                if( temp.distance < hitpoint->distance )
                {
                    *hitpoint = temp;
                    object = &cornellBox[i];
                }
            }
        }
        return object;
    }
};

#endif // _SCENE_H_
