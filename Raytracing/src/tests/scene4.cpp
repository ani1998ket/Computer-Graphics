#include "utlis.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

#include <iostream>
#include "omp.h"

color ray_color( const ray& r, const hittable_list& world, int depth = 1){
    hit_record rec;

    if( depth <= 0 ){
        return color(0, 0, 0);
    }

    if( world.hit( r, 0.001, infinity, rec) ){
        vec3 scattering;
        // scattering = random_in_unit_sphere();
        // scattering = random_unit_vector();
        scattering = random_in_hemisphere( rec.normal );
        // scattering = random_in_hemisphere( rec.normal ) - rec.normal;
        point3 target = rec.p + rec.normal + scattering;
        return 0.5 * ray_color( ray( rec.p, target - rec.p), world, depth - 1);
    }

    vec3 direction = normalise(r.direction());
    auto t = 0.5 * ( direction.y() + 1.0 );
    return t * color(0.5, 0.7, 1.0) + ( 1 - t ) * color( 1.0, 1.0, 1.0 );
}

int main(){ 

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 1000;
    const int max_depth = 40;

    std::cerr << image_width << " * " << image_height << "\n";
    std::cerr << "SPP : " << samples_per_pixel << "\n";
    // World
    hittable_list world;
    world.add_object( make_shared<sphere>( point3( 0, 0, -2), 0.5) );
    world.add_object( make_shared<sphere>( point3( 0, -100.5, -2), 100) );

    camera cam;
    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for( int row = image_height - 1; row >= 0; --row ){
        std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;
        for( int col = 0; col < image_width; col++ ){
            color pixel_color(0, 0, 0);
            for( int s = 0; s < samples_per_pixel; s++ ){
                auto u = double( col + random_double()) / (image_width - 1);
                auto v = double( row + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);

                pixel_color += ray_color(r, world, max_depth);
            }
            write_color( std::cout, pixel_color, samples_per_pixel );
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}