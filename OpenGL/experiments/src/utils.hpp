#include <iostream>

inline void printE( const char* tag, const char* message ){
    std::cerr << "Error: " << tag << ": " << message << std::endl;
}