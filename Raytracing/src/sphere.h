#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
    private:
    point3 m_center;
    double m_radius;
    shared_ptr<material> mat_ptr;   

    public:
    sphere(){}
    sphere(point3 center, double radius, shared_ptr<material> m)
        : m_center( center ), m_radius( radius ), mat_ptr(m)
    {}

    double radius() const {
        return m_radius;
    }
    point3 center() const {
        return m_center;
    }

    virtual bool hit( const ray& r, double tmin, double tmax, hit_record& hit) const override;
};

bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& hit) const {
    vec3 oc = r.origin() - m_center;
    auto a  = r.direction().length_squared();
    auto half_b = dot( oc, r.direction() );
    auto c = oc.length_squared() - m_radius * m_radius;
    auto discriminant = half_b*half_b - a * c;

    if( discriminant > 0 ){
        auto temp = sqrt(discriminant);

        auto root = (-half_b - temp ) / a;
        if( root < tmin || root > tmax ){
            root = (-half_b + temp ) / a;
            if( root < tmin || root > tmax ){
                return false;
            }
        }

        hit.t = root; 
        hit.p = r.at( hit.t );
        hit.set_face_normal(r, (hit.p - m_center) / m_radius);
        hit.mat_ptr = mat_ptr;
        return true;
    } 

    return false;
}
#endif