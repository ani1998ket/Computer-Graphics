#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color( std::ostream& out, const color pixel_color){
    color final_color = 255 * pixel_color;
    out << (int)final_color.x() << ' ' 
        << (int)final_color.y() << ' ' 
        << (int)final_color.z() << '\n'; 
}
#endif