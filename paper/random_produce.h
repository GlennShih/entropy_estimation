#ifndef RANDOM_PRODUCE_H
#define RANDOM_PRODUCE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include "prng.h"

//long double H_function(long double y[], char normalize, uint32_t Y);
double H_function(double y[], char normalize, uint32_t Y);
#endif
