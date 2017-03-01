//
//  PSO.hpp
//  PSONeighborhoods
//
//  Created by Cory Alini on 2/27/17.
//  Copyright © 2017 PSO.coryalini. All rights reserved.
//

#ifndef PSO_hpp
#define PSO_hpp

#include <iostream>
#include <string>
#include <math.h>
#include <random>


#endif /* PSO_hpp */

typedef struct _particle {
    double* position;
    double* velocity;
    double pBest;
    double* pBest_position;
    double gBest;
    double* gBest_position;
    long* neighbors;
    long neighborhoodSize;
    int index;
    
} Particle;

typedef struct _info {
    std::string neighborhood;
    long nswarm;
    long iterations;
    std::string func;
    long dim;
    Particle* swarm;
    
} Info;


void pso(Info* info);

void bestInNeighborhood(Info info, Particle* particle);
void updateVelocity(Info info, Particle* p);
void updatePosition(Info info, Particle* p);


//Neighborhood functions
void setNeighborhood(Info* info, Particle* particle);
void globalNeighborhood(Info info, Particle* particle);
void ringNeighborhood(Info info, Particle* particle);
void vonNeumannNeighborhood(Info info, Particle* particle);
void randomNeighborhood(Info info, Particle* particle);



//Evaluate Functions
double evaluate(Info info, Particle particle);

double evalRosenbrock (Info info, Particle particle);
double evalAckley(Info info, Particle particle);
double evalRastrigin(Info info, Particle particle);

//Helper functions
long RandomLong(long min, long max);
double RandomDouble(double min, double max);
