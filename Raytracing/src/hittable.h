#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "utlis.h"

class material;
// #include "material.h"

struct hit_record{
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    shared_ptr< material> mat_ptr;

    inline void set_face_normal( const ray& r, const vec3& outward_normal){
        front_face = dot( r.direction(), outward_normal ) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{
    public:
    virtual bool hit( const ray& r, double tmin, double tmax, hit_record& hit) const = 0;
};

#endif