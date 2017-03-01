//
//  main.cpp
//  PSONeighborhoods
//
//  Created by Cory Alini on 2/27/17.
//  Copyright © 2017 PSO.coryalini. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
//#include <time>
#include "PSO.hpp"








int main(int argc, const char * argv[]) {
    Info info;
    srand((uint)time(NULL));
    if(argc != 6) {
        printf("ERROR: Arguments were not included. %d \n", argc);
        return 1;
    }
    
    info.neighborhood = argv[1];
    info.nswarm = atol(argv[2]);
    info.iterations = atol(argv[3]);
    info.func = argv[4];
    info.dim = atol(argv[5]);
    
    
    pso(&info);
    
    
    
    return 0;
}
