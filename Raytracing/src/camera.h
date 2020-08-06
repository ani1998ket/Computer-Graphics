#ifndef CAMERA_H
#define CAMERA_H

#include "utlis.h"

class camera{
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        double fov_y;

    public:
        camera(){
            fov_y = 45.0;

            auto aspect_ratio = 16.0/9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1 / std::tan( fov_y * M_PI / 360.0);

            origin = point3(0, 0, 0);
            horizontal = vec3( viewport_width, 0, 0 );
            vertical   = vec3( 0, viewport_height, 0 );
            lower_left_corner = origin + ( -horizontal/2  - vertical/2  - vec3( 0, 0, focal_length ));
        }

        ray get_ray( double u, double v ){
            return ray( origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }
};
#endif