#include <iostream>
#include "omp.h"

int main(){ 
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        std::cout << "Hello" << id;
        std::cout << "World" << id << std::endl;
    }
    return 0;
}