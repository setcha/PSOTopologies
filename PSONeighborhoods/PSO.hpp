//
//  PSO.hpp
//  PSONeighborhoods
//
//  Created by Cory Alini on 2/27/17.
//  Copyright © 2017 PSO.coryalini. All rights reserved.
//

#ifndef PSO_hpp
#define PSO_hpp

#include <stdio.h>
#include <string>
#include <math.h>

#endif /* PSO_hpp */

typedef struct _particle {
    double* values;
    double pBest;
//    Particle* neighbors;
    
} Particle;

typedef struct _info {
    std::string neighborhood;
    long nswarm;
    long iterations;
    std::string func;
    long dim;
    Particle* swarm;
    
} Info;


void pso(Info info);

double evalRosenbrock (double* particle, Info info);
double evalAckley (double* particle, Info info);
double evalRastrigin (double* particle, Info info);
