#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pcg_basic.h"

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <output_name> <seed1> <seed2> <size>\n", argv[0]);
        return 1;
    }
    FILE *file_out;
    char *output_name=argv[1];
    uint64_t initialState = atol(argv[2]);
    uint64_t sequenceSelectors = atol(argv[3]);
    uint32_t size = atol(argv[4]);
    int i1,i2;
    double u1, u2, w1, w2, ran, ran1, ran2;
    int i;
    double array;

    pcg32_random_t rng;
    
    //set the seed
    pcg32_srandom_r(&rng, initialState, sequenceSelectors);
    //pcg32_srandom_r(&rng, 42u, 54u);

    if(size==14) size=1;
    else if(size==15) size=2;
    else if(size==16) size=4;
    else if(size==17) size=8;
    else if(size==18) size=16;
    else if(size==19) size=32;
    else if(size==20) size=64;
    
    file_out = fopen(output_name, "wb");

    for(i=0; i<16384*size; i++)
    {
        /*
        while(1)
        {
            i1=ldexp(pcg32_random_r(&rng), -32);
            if(i1 != 0.0)
            {
                u1=i1;
                break;
            }
        }
        while(1)
        {
            i2=ldexp(pcg32_random_r(&rng), -32);
            if(i2 != 0.0)
            {
                u2=i2;
                break;
            }
        }
        */
        u1= ldexp(pcg32_random_r(&rng), -32);
        u2= ldexp(pcg32_random_r(&rng), -32);
        //printf("u1=%lf\tu2=%lf\t\n", u1, u2);
        w1 = M_PI*(u1-0.5);
        w2 = -log(u2);
        ran1 = (tan(w1)*(M_PI_2 - w1));
        ran2 = log( w2*cos(w1) / (M_PI_2-w1) );
        ran = ran1 + ran2;
        array = ran;

        fprintf(file_out, "%lf\n", array);
    }
    fclose(file_out);
}