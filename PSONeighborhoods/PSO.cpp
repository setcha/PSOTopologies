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
double CONSTRICTION_FACTOR = 0.7298;
double CHI_1 = 2.05;
double CHI_2 = 2.05;

double rosenbrockPos[2] = {15.0,30.0};
double ackleyPos[2] = {16.0,32.0};
double rastriginPos[2] = {2.56,5.12};
double rosenbrockVel[2] = {-2.0,2.0};
double ackleyVel[2] = {-2.0,4.0};
double rastriginVel[2] = {-2.0,4.0};

double GlobalBest = std::numeric_limits<double>::max();


void pso(Info* info) {
    //double swarm[info.nswarm][info.dim];
    info->swarm = new Particle[info->nswarm];
    
    //initialize particles
    for(int i = 0; i < info->nswarm; i++) {
        Particle p;
        p.index = i;
        p.position = new double[info->dim];
        p.velocity = new double[info->dim];
        
        for(int j = 0; j < info->dim; j++) {
            if(info->func == "rok") {
                p.position[j] = RandomDouble(rosenbrockPos[0], rosenbrockPos[1]);
                p.velocity[j] = RandomDouble(rosenbrockVel[0], rosenbrockVel[1]);

            } else if (info->func == "ack") {
                p.position[j] = RandomDouble(ackleyPos[0], ackleyPos[1]);
                p.velocity[j] = RandomDouble(ackleyVel[0], ackleyVel[1]);
            } else if (info->func == "ras") {
                p.position[j] = RandomDouble(rastriginPos[0], rastriginPos[1]);
                p.velocity[j] = RandomDouble(rastriginVel[0], rastriginVel[1]);

            } else {
                printf("The evaluation function input is incorrect \n");
                exit(0);
            }
        }
        setNeighborhood(info, &p);
        p.pBest = evaluate(*info, p);
        info->swarm[i] = p;

    }
    
    //START THE LEARNING!
    long currGen = 0;
    while(currGen < info->iterations) {
        for(int i = 0; i < info->nswarm; i++) {
            
            double currEval = evaluate(*info, info->swarm[i]);
            if (currEval < info->swarm[i].pBest) {
                info->swarm[i].pBest = currEval;
                info->swarm[i].pBest_position = info->swarm[i].position;
                if(currEval < GlobalBest){
                    GlobalBest = currEval;
                }
            }
        }
        for(int i = 0; i < info->nswarm; i++) {
            bestInNeighborhood(*info, &info->swarm[i]);
            for(int k = 0; k < info->dim; k++) {
                std::cout<<info->swarm[i].gBest_position[k]<<" ";
            }
            std::cout<<std::endl;
        }

        for(int i = 0; i < info->nswarm; i++) {
            updateVelocity(*info, &info->swarm[i]);
            updatePosition(*info, &info->swarm[i]);
        }
        currGen++;
        std::cout<<"Generation: "<< currGen<< " "<< (double)currGen/(double)info->iterations<<std::endl;
        std::cout <<GlobalBest<<std::endl;
    }
}

void updateVelocity(Info info, Particle* p) {
    for(int i = 0; i < info.dim; i++) {
        p->velocity[i] = CONSTRICTION_FACTOR * (p->velocity[i] + (RandomDouble(0,CHI_1)*(p->pBest_position[i] - p->position[i])) + (RandomDouble(0,CHI_2) *(p->gBest_position[i]- p->position[i])));
    }
}

void updatePosition(Info info, Particle* p) {
    for(int i = 0; i < info.dim; i++) {
        p->position[i] = p->position[i] + p->velocity[i];
    }
}

void bestInNeighborhood(Info info, Particle* particle) {
    double theBest = std::numeric_limits<double>::max();
    for (int i = 0; i < particle->neighborhoodSize; i++) {
        if(info.swarm[particle->neighbors[i]].pBest < theBest) {
            
            theBest = info.swarm[particle->neighbors[i]].pBest;
            info.swarm[particle->neighbors[i]].gBest_position= info.swarm[particle->neighbors[i]].position;
        }
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
    particle->neighbors = new long[RING_SIZE];
    if(particle->index == 0) {
        particle->neighbors[0] = info.nswarm-1;
    } else {
        particle->neighbors[0] = particle->index - 1;
        
    }
    if(particle->index == info.nswarm-1) {
        particle->neighbors[1] = 0;
    } else {
        particle->neighbors[1] = particle->index + 1;
    }
}

void vonNeumannNeighborhood(Info info, Particle* particle) {
    
    //set neighborhood to particle->neighborhood
}

void randomNeighborhood(Info info, Particle* particle) {
    particle->neighbors = new long[particle->neighborhoodSize];

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
        sum += 100.0 * pow((particle.position[x+1]) - particle.position[x]*particle.position[x], 2.0) + pow(particle.position[x]-1.0, 2.0);
    }
    return sum;
}
//ref: http://www.cs.unm.edu/~neal.holts/dga/benchmarkFunction/ackley.html
//https://www.sfu.ca/~ssurjano/ackley.html
double evalAckley(Info info, Particle particle)  {
    
    double firstSum = 0.0;
    double secondSum = 0.0;
    for(int x = 0; x < info.dim; x++) {
        firstSum += particle.position[x]*particle.position[x];
        secondSum += cos(2.0*M_PI*particle.position[x]);
    }
    return -20.0 * exp(-0.2 * sqrt(firstSum/2.0)) - exp(secondSum/2.0) + 20.0 + M_E;
}
//ref: https://en.wikipedia.org/wiki/Rastrigin_function
double evalRastrigin(Info info, Particle particle)  {
    
    double retVal = 0;
    for(int x = 0; x < info.dim; x++) {
        retVal += particle.position[x]*particle.position[x] - 10.0*cos(2.0*M_PI*x) + 10.0;
    }
    return retVal;
}



//MARK  HELPER FUNCTIONS

long RandomLong(long min, long max) {
    
    long range = max - min;
    long num = rand() % range + min;
    return num;
}

//NEED TO FIX THIS FUNCTION
double RandomDouble(double min, double max) {
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}
                                             
                                             
