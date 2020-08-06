#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include "utlis.h"

class vec3{

    double data[3];

    public:
    vec3() : data{0, 0, 0}{}
    vec3( double x, double y, double z ) : data{x, y, z}{}

    double x() const { return data[0];}
    double y() const { return data[1];}
    double z() const { return data[2];}

    vec3 operator-() const { return vec3( -data[0], -data[1], -data[2]); }
    double operator[](int i) const { return data[i]; }
    double& operator[]( int i ) { return data[i]; }

    vec3& operator+=( const vec3& v ){
        data[0] += v[0];
        data[1] += v[1];
        data[2] += v[2];

        return *this;
    } 
    vec3& operator*=( const vec3& v ){
        data[0] *= v[0];
        data[1] *= v[1];
        data[2] *= v[2];

        return *this;
    } 
    vec3& operator*=( const double t ){
        data[0] *= t;
        data[1] *= t;
        data[2] *= t;

        return *this;
    } 
    vec3& operator/=( const double t ){
        return ( *this *= 1 / t);
    } 
    double length() const {
        return sqrt( length_squared() );
    }
    double length_squared() const {
        return data[0]*data[0] + data[1]*data[1] + data[2]*data[2]; 
    }
    inline static vec3 random( double min = 0, double max = 1){
    return vec3( random_double(min, max), random_double(min, max), random_double(min, max) );
    }
};

using point3 = vec3;
using color = vec3;

inline std::ostream& operator<<( std::ostream &out, const vec3& v ){
    return out << v[0] << ' ' << v[1] << ' ' <<  v[2];
}

inline vec3 operator+(const vec3& a, const vec3& b ){
    return vec3( a[0] + b[0], a[1] + b[1], a[2] + b[2] );
}
inline vec3 operator-(const vec3& a, const vec3& b ){
    return vec3( a[0] - b[0], a[1] - b[1], a[2] - b[2] );
}
inline vec3 operator*(const vec3& a, const vec3& b ){
    return vec3( a[0] * b[0], a[1] * b[1], a[2] * b[2] );
}
inline vec3 operator*(double t, const vec3& v ){
    return vec3( t * v[0], t * v[1],  t * v[2] );
}
inline vec3 operator*(const vec3& v, double t){
    return t * v;
}
inline vec3 operator/(const vec3& v, double t){
    return ( 1/t) * v;
}
inline double dot( const vec3& a, const vec3& b ){
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]; 
}
inline vec3 cross( const vec3& a, const vec3& b ){
    return vec3 (   a[1]*b[2] - a[2] * b[1],
                    a[2]*b[0] - a[0] * b[2],
                    a[0]*b[1] - a[1] * b[0]
                );
}
inline vec3 normalise( const vec3 v ){
    return v / v.length();
}
vec3 reflect( const vec3& v, const vec3& n){
    return v - 2 * dot(v, n) * n;
}

vec3 refract( const vec3& uv, const vec3& n, double etai_over_etat){
    auto cos_thetha = dot( -uv, n);
    vec3 r_out_perp = etai_over_etat * ( uv + cos_thetha * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared() )) * n;
    return r_out_parallel + r_out_perp;
}
vec3 random_in_unit_sphere(){
    while( true ){
        auto p = vec3::random(-1, 1);
        if( p.length_squared() >= 1) continue;
        return p;
    }
}
vec3 random_unit_vector(){
    auto a = random_double( 0, 2 * pi );
    auto z = random_double( -1, 1);
    auto r = sqrt( 1 - z * z);

    return vec3( r * cos(a), r * sin(a) , z);
}

vec3 random_in_hemisphere( const vec3& normal){
    vec3 in_unit_sphere = random_in_unit_sphere();
    if( dot( normal, in_unit_sphere ) < 0.0 ){
        return -in_unit_sphere;
    }
    return in_unit_sphere;
}
#endif