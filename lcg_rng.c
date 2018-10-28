/* Linear Congruential Generators */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define M 2147483647
#define A 16807
#define Q ( M / A )
#define R ( M % A )

//static int seed = 1;

/* Single-Phase Linear Congruential Generator */
uint32_t jsw_rand(uint32_t seed)
{
    seed = A * (seed % Q) - R * (seed / Q);

    if (seed <= 0)
    {
        seed += M;
    }

    return seed;
}

double uniform_deviate(uint32_t seed)
{
    return (double)seed * (1.0 / M);
}

int main(void)
{
    int i;
    uint32_t tmp;
    
    tmp = jsw_rand(1);

    for (i = 0; i < 10; i++)
    {
        //tmp = jsw_rand(1);
        printf("seed=%d\t\n", tmp);
        printf("jsw_rand()=%f\t\n", uniform_deviate(tmp));
        //srand(seed);
        //printf("rand()=%lf\t\n",(double)rand()/RAND_MAX);
    }

    printf("\n");

    return 0;
}