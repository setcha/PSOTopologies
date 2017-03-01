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
#include "PSO.hpp"
/*
 • which neighborhood topology to test (gl, ri, vn, ra) • the size of the swarm,
 • the number of iterations,
 • which function to optimize (rok, ack, ras), and
 • the dimensionality of the function.
 
 */


float chi = 0.7298;

int main(int argc, const char * argv[]) {
    Info info;
    srand(NULL);
    if(argc != 5) {
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
