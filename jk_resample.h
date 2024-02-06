#ifndef JACKKNIFE_H
#define JACKKNIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nlopt.h>

// from nlopt minimise
typedef struct {
    double x, y, minf;
} OptimisedOutputs;
typedef double (*ObjFunc)(unsigned, const double*, double*, void*);
OptimisedOutputs optimise(ObjFunc obj, void *params);

// from readCSV
double*** extractData(char *fileName, int n, int T);
void free3dArray(double*** array, int height, int length);
void print3dArray(double*** array, int height, int length, int depth);

#endif