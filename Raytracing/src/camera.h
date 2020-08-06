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
        double aspect;
        vec3 u, v, w;
        double lens_radius;

    public:
        camera(
            point3 lookfrom = vec3(0, 0, 0),
            point3 lookat = vec3(0, 0, -1),
            vec3 vup = vec3(0, 1, 0),
            double fov_y = 45.0, 
            double aspect_ratio = 16.0/9.0,            
            double aperture = 0.0,
            double focus_dist = 1.0
        )
        {
            fov_y = fov_y;
            aspect = aspect_ratio;

            auto theta = degrees_to_radians( fov_y );
            auto h = tan( theta / 2 );

            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            w = normalise(lookfrom - lookat);
            u = normalise(cross( vup, w));
            v = normalise(cross( w, u));

            origin = lookfrom;
            horizontal = focus_dist * u * viewport_width;
            vertical   = focus_dist * v * viewport_height;
            lower_left_corner = origin + ( -horizontal/2  - vertical/2  - focus_dist * w);

            lens_radius = aperture / 2.0;
        }

        ray get_ray( double s, double t ){
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();
            return ray( 
                origin + offset, 
                lower_left_corner + s*horizontal + t*vertical - origin - offset
            );
        }
};
#endif