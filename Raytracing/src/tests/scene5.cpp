#include "utlis.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

#include <iostream>

color ray_color( const ray& r, const hittable_list& world, int depth = 1){
    hit_record rec;

    // Maximum bounces then return black
    if( depth <= 0 ){
        return color(0, 0, 0);
    }

    if( world.hit( r, 0.001, infinity, rec) ){
        ray scattered;
        color attenuation;
        if( rec.mat_ptr->scatter( r, rec, attenuation, scattered) > 0 ){
            return attenuation * ray_color( scattered, world, depth - 1);
        }
        return color(0, 0, 0);
    }

    //Background
    vec3 direction = normalise(r.direction());
    auto t = 0.5 * ( direction.y() + 1.0 );
    return t * color(0.5, 0.7, 1.0) + ( 1 - t ) * color( 1.0, 1.0, 1.0 );
}

int main(){ 

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 30;
    const int max_depth = 100;

    std::cerr << image_width << " * " << image_height << "\n";
    std::cerr << "SPP : " << samples_per_pixel << "\n";

    // World
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
    
    // auto material_glass  = make_shared<dielectric>(1.5);
    // auto material_diamond  = make_shared<dielectric>(1.5);
    // auto material_weird  = make_shared<dielectric>(-1.7);

    double z = -2.0;

    world.add_object(make_shared<sphere>(point3( 0.0, -100.5, z), 100.0, material_ground));
    world.add_object(make_shared<sphere>(point3( -0.0,   0.4, z),   0.5, material_center));
    world.add_object(make_shared<sphere>(point3(-1.0,    0.0, z),   0.5, material_left));
    world.add_object(make_shared<sphere>(point3(-1.0,    0.0, z),  -0.4, material_left));
    world.add_object(make_shared<sphere>(point3( 1.0,    0.0, z),   0.5, material_right));


    camera cam(45, aspect_ratio);
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