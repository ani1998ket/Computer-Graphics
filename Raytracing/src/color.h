#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color( std::ostream& out, color pixel_color, int samples_per_pixel = 1){

    auto scale = 1.0 / samples_per_pixel; 
    pixel_color *= scale;

    auto r = sqrt(pixel_color.x());
    auto g = sqrt(pixel_color.y());
    auto b = sqrt(pixel_color.z());

    out << static_cast<int>( 256 * clamp(r, 0.0, 0.999) ) << ' '
        << static_cast<int>( 256 * clamp(g, 0.0, 0.999) ) << ' '
        << static_cast<int>( 256 * clamp(b, 0.0, 0.999) ) << '\n';
}
#endif