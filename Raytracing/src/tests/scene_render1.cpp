#include <iostream>
#include "ray.h"
#include "vec3.h"
#include "color.h"

//t^2b⋅b+2tb⋅(A−C)+(A−C)⋅(A−C)−r2=0
double hitsphere( const point3& center, double radius, const ray& r){
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot( oc, r.direction() );
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b*half_b - a * c;

    if( discriminant < 0 ){
        return -1.0;
    }else{
        return (-half_b - sqrt(discriminant) ) / (a);
    }
    return discriminant > 0;  
}
color ray_color( const ray& r ){
    point3 center( 0, 0, -2);
    double radius = 1.0;
    auto t = hitsphere( center, radius, r);
    if( t > 0.0 ){
        vec3 N = normalise(r.at( t ) - center);
        return (color)(0.5 * ( N + vec3(1.0, 1.0, 1.0))); 
    }
    vec3 direction = normalise(r.direction());
    t = 0.5 * ( direction.y() + 1.0 );
    return t * color(0.5, 0.7, 1.0) + ( 1 - t ) * color( 1.0, 1.0, 1.0 );
}
int main(){ 

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 640;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    
    //Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

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