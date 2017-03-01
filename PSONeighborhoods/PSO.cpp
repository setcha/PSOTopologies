//
//  PSO.cpp
//  PSONeighborhoods
//
//  Created by Cory Alini on 2/27/17.
//  Copyright © 2017 PSO.coryalini. All rights reserved.
//


#include "PSO.hpp"
long GLOBAL_SIZE = 1;
long RING_SIZE = 2;
long VON_NEUMANN_SIZE = 4;

void pso(Info* info) {
    //double swarm[info.nswarm][info.dim];
    info->swarm = new Particle[info->nswarm];
    //initialize particles
    for(int i = 0; i < info->nswarm; i++) {
        Particle p;
        p.values = new double[info->dim];
        for(int j = 0; j < info->dim; j++) {
            double r = (double) rand() / (RAND_MAX);
            p.values[j] = 1000.0 - r *100.0; // this was pulled from his code. Need to ask if this is correct
        }
        p.pBest = evaluate(*info, p);
        
        setNeighborhood(info, &p);
        info->swarm[i] = p;

    }
    
    //START THE LEARNING!
    long currGen = 0;
    while(currGen < info->iterations) {
        
        
    
        
    
    }

    
}
/* MARK  NEIGHBORHOOD */
void setNeighborhood(Info* info, Particle* particle) {
    if(info->neighborhood == "gl") {
        particle->neighborhoodSize = info->nswarm;
        globalNeighborhood(*info, particle);
    } else if (info->neighborhood == "ri") {
        particle->neighborhoodSize = RING_SIZE;
        ringNeighborhood(*info, particle);

    } else if (info->neighborhood == "vn") {
        particle->neighborhoodSize = VON_NEUMANN_SIZE;
        vonNeumannNeighborhood(*info, particle);
    
    } else if (info->neighborhood == "ra") {
        long r = RandomLong(0, info->nswarm); // will return num btwn 0 and nswarm -1
        particle->neighborhoodSize = r;
        randomNeighborhood(*info, particle);
        
    }else {
        printf("The neighborhood topology input is incorrect \n");
        exit(0);
    }
}

void globalNeighborhood(Info info, Particle* particle) {
    particle->neighbors = new long[info.nswarm];
    for(int i = 0; i < info.nswarm; i++) {
        particle->neighbors[i] = i;
    }
}


void ringNeighborhood(Info info, Particle* particle) {
    
//set neighborhood to particle->neighborhood
}

void vonNeumannNeighborhood(Info info, Particle* particle) {
    
    //set neighborhood to particle->neighborhood
}

void randomNeighborhood(Info info, Particle* particle) {

    for(int i = 0; i < particle->neighborhoodSize-1; i++) {
        particle->neighbors[i] = particle->neighborhoodSize;
    }
    
    for(int i = 0; i <particle->neighborhoodSize-1; i++) {
        bool exists = true;
        while(exists) {
            long r = RandomLong(0, particle->neighborhoodSize-1);
            exists = false;
            for(int j = 0; j < particle->neighborhoodSize-1; j++) {
                if(particle->neighbors[j] == r) {
                    exists = true;
                }
            }
            if(!exists) {
                particle->neighbors[i] = r;
            }
        }
    }
}


/* MARK  EVALUATIONS */

double evaluate(Info info, Particle particle) {
    double answer = 0;
    if(info.func == "rok") {
        answer = evalRosenbrock(info, particle);
    } else if (info.func == "ack") {
        answer = evalAckley(info, particle);
    } else if (info.func == "ras") {
        answer = evalRastrigin(info, particle);
    } else {
        printf("The evaluation function input is incorrect \n");
        exit(0);
    }
    return answer;
}




//We need Rosenbrock, Ackley, and Rastrigin
//ref:https://www.sfu.ca/~ssurjano/rosen.html
double evalRosenbrock(Info info, Particle particle) {
    double sum = 0.0;
    for(int x = 1; x < info.dim-1; x++) {
        sum += 100.0 * pow((particle.values[x+1]) - particle.values[x]*particle.values[x], 2.0) + pow(particle.values[x]-1.0, 2.0);
    }
    return sum;
}
//ref: http://www.cs.unm.edu/~neal.holts/dga/benchmarkFunction/ackley.html
//https://www.sfu.ca/~ssurjano/ackley.html
double evalAckley(Info info, Particle particle)  {
    
    double firstSum = 0.0;
    double secondSum = 0.0;
    for(int x = 0; x < info.dim; x++) {
        firstSum += particle.values[x]*particle.values[x];
        secondSum += cos(2.0*M_PI*particle.values[x]);
    }
    return -20.0 * exp(-0.2 * sqrt(firstSum/2.0)) - exp(secondSum/2.0) + 20.0 + M_E;
}
//ref: https://en.wikipedia.org/wiki/Rastrigin_function
double evalRastrigin(Info info, Particle particle)  {
    
    double retVal = 0;
    for(int x = 0; x < info.dim; x++) {
        retVal += particle.values[x]*particle.values[x] - 10.0*cos(2.0*M_PI*x) + 10.0;
    }
    return retVal;
}



//MARK  HELPER FUNCTIONS

long RandomLong(long min, long max) {
    
    long range = max - min;
    long num = rand() % range + min;
    return num;
}



