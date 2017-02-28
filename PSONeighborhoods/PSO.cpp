//
//  PSO.cpp
//  PSONeighborhoods
//
//  Created by Cory Alini on 2/27/17.
//  Copyright © 2017 PSO.coryalini. All rights reserved.
//

#include "PSO.hpp"



void pso(Info info) {
    double swarm[info.nswarm][info.dim];
    
    //initialize particles
    for(int i = 0; i < info.nswarm; i++) {
        for(int j = 0; j < info.dim; j++) {
            swarm[i][j] = 4;//random num
            
        }
    }
    long currGen = 0;
    while(currGen < info.iterations) {
        
        
        
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
}

//We need Rosenbrock, Ackley, and Rastrigin
//ref:https://www.sfu.ca/~ssurjano/rosen.html
double evalRosenbrock (double* particle, Info info) {
    double sum = 0.0;
    for(int x = 1; x < info.dim-1; x++) {
        sum += 100.0 * pow((particle[x+1]) - particle[x]*particle[x], 2.0) + pow(particle[x]-1.0, 2.0);
    }
    return sum;
}
//ref: http://www.cs.unm.edu/~neal.holts/dga/benchmarkFunction/ackley.html
//https://www.sfu.ca/~ssurjano/ackley.html
double evalAckley (double* particle, Info info)  {
    
    double firstSum = 0.0;
    double secondSum = 0.0;
    for(int x = 0; x < info.dim; x++) {
        firstSum += particle[x]*particle[x];
        secondSum += cos(2.0*M_PI*particle[x]);
    }
    return -20.0 * exp(-0.2 * sqrt(firstSum/2.0)) - exp(secondSum/2.0) + 20.0 + M_E;
}
//ref: https://en.wikipedia.org/wiki/Rastrigin_function
double evalRastrigin (double* particle, Info info)  {
    
    double retVal = 0;
    for(int x = 0; x < info.dim; x++) {
        retVal += particle[x]*particle[x] - 10.0*cos(2.0*M_PI*x) + 10.0;
    }
    return retVal;
}


