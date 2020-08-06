#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians( double degrees ){
    return degrees * ( pi / 180.0 ); 
}

double random_double( double min =  0, double max = 1){
    double r = rand() / (RAND_MAX + 1.0 ); 
    return  r*( max - min ) + min;
}
inline double clamp( double x, double min, double max){
    if( x < min ) return min;
    if( x > max ) return max;
    return x;
}
#include "ray.h"
#include "vec3.h"

#endif