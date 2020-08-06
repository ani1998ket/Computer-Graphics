#include <iostream>
#include <cmath>

int main(){
    int width = 1100;
    int height = 300;

    std::cout << "P3\n" << width << ' ' << height << '\n' << 255 << '\n';
    
    //What happens due to gamma
    int intensity = 1;
    for( int r = 0; r < 100; r++ ){
        for( int c = 0; c < width; c++ ){
            intensity = c / 100;
            double value = (intensity / 10.0);
            int col = value * 255;
            std::cout << col << ' ' << col << ' ' << col << '\n';
        }
    }
    //What we want( gamma correction )
    intensity = 1;
    for( int r = 0; r < 100; r++ ){
        for( int c = 0; c < width; c++ ){
            intensity = c / 100;
            double value = sqrt(intensity / 10.0);
            int col = value * 255;
            std::cout << col << ' ' << col << ' ' << col << '\n';
        }
    }
    //What we do ( illustration purposes this transformation happens due to gaama correction )
    intensity = 1;
    for( int r = 0; r < 100; r++ ){
        for( int c = 0; c < width; c++ ){
            intensity = c / 100;
            double value = sqrt(intensity / 10.0);
            value = sqrt( value );
            int col = value * 255;
            std::cout << col << ' ' << col << ' ' << col << '\n';
        }
    }

    
    return 0;
}
