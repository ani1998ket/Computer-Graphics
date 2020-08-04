#include <iostream>
#include "ray.h"

int main(){
    ray r( point3(2, 2, 3), vec3( 0, 1, 0) );
    std::cout << r.at( 0 ) << std::endl;
    std::cout << r.at( -1 ) << std::endl;
    std::cout << r.at( 1 ) << std::endl;
}