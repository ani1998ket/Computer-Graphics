#include <iostream>
#include "color.h"

int main(){

    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n";
    std::cout << image_width << " " << image_height << "\n";
    std::cout << "255\n";

    for( int row = 0; row < image_height; row++ ){
        for( int col = 0; col < image_width; col++ ){
            
            std::cerr << "\rScanlines remaining: " << image_height - row << std::flush;

            color pixel((double)col / (image_width - 1), (double)row / (image_height - 1), 0.25);
            write_color( std::cout, pixel );
        }
    }
    std::cerr << "\nDone.\n";

    return 0;
}