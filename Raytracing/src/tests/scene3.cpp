#include "utlis.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"

#include <iostream>

color ray_color( const ray& r, const hittable_list& world){
    hit_record rec;

    if( world.hit( r, 0, infinity, rec) ){
        return 0.5 * (rec.normal + color( 1, 1, 1) );
    }

    vec3 direction = normalise(r.direction());
    auto t = 0.5 * ( direction.y() + 1.0 );
    return t * color(0.5, 0.7, 1.0) + ( 1 - t ) * color( 1.0, 1.0, 1.0 );
}

int main(){ 

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    std::cerr << image_width << " * " << image_height << std::endl;
    // World
    hittable_list world;
    world.add_object( make_shared<sphere>( point3( 0, 0, -2), 0.5) );
    world.add_object( make_shared<sphere>( point3( 0, -100.5, -2), 100) );

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
            write_color( std::cout, ray_color( r, world) );
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}