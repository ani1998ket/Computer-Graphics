#include <iostream>
#include <cmath>
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "sphere.h"

color ray_color( const ray& r ){
    hit_record hit;
    sphere sp1( vec3( 2, 0.0, -4.5), 1.0 );
    sphere sp2( vec3( -2, 0, -5), 1.0 );

    if( sp1.hit(r, 0.1, 100, hit) ){
        color c;
        vec3 light( 0, 0, 0);
        light = normalise(light - hit.p);
        double d = dot( hit.normal, light );
        if( d < 0 ) d = 0;
        return color( d, d, d);
    }
    if( sp2.hit(r, 0.1, 100, hit) ){
        return (color)(0.5 * ( hit.normal + vec3(1.0, 1.0, 1.0))); 
    }
    vec3 direction = normalise(r.direction());
    double t = 0.5 * ( direction.y() + 1.0 );
    return t * color(0.5, 0.7, 1.0) + ( 1 - t ) * color( 1.0, 1.0, 1.0 );
}
int main(){ 

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 640;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    
    //Camera

    auto fov_y = 45.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1 / std::tan( fov_y * M_PI / 360.0);

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3( viewport_width, 0, 0 );
    auto vertical   = vec3( 0, viewport_height, 0 );
    auto lower_left_corner = origin + ( -horizontal/2  - vertical/2  - vec3( 0, 0, focal_length ));

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for( int row = image_height - 1; row >= 0; --row ){
        std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
        for( int col = 0; col < image_width; col++ ){
            auto u = double( col )/ (image_width - 1);
            auto v = double( row )/ (image_height - 1);
            ray r( origin, lower_left_corner + (u * horizontal) + (v * vertical) - origin);
            write_color( std::cout, ray_color( r ) );
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}