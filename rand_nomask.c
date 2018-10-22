#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

long double ran_produce();

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <output_name> <seed> <size>\n", argv[0]);
        return 1;
    }
    FILE *file_out;
    char *output_name=argv[1];
    uint32_t seed = atol(argv[2]);
    uint32_t size = atol(argv[3]);
    uint32_t mask;
    
    if(size==14) size=1;
    else if(size==15) size=2;
    else if(size==16) size=4;
    else if(size==17) size=8;
    else if(size==18) size=16;
    else if(size==19) size=32;
    else if(size==20) size=64;

    file_out = fopen(output_name, "wb");
    srand(seed);
    int i;
    long double array;
    for(i=0; i<16384*size; i++)
    {
        array = ran_produce();
        fprintf(file_out, "%Lf\n", array);
    }
    fclose(file_out);
}

long double ran_produce()
{
    //int i1,i2;
    unsigned long long int i1, i2;
    long double u1, u2, w1, w2, ran, ran1, ran2;

    while(1)
    {
        i1=rand();
        printf("i1=%llu\n",i1);
        if(i1>0 && i1<RAND_MAX)
        {
            u1=(unsigned long long int)i1/RAND_MAX;
            break;
        }
    }
    while(1)
    {
        i2=rand();
        printf("i2=%llu\n",i2);
        if(i2>0 && i2<RAND_MAX) 
        {
            u2=(unsigned long long int)i2/RAND_MAX;
            break;
        }
    }
    
    //u1 = (double)rand() / (double)RAND_MAX;
    //u2 = (double)rand() / (double)RAND_MAX;
    w1 = M_PI*(u1-0.5);
    w2 = -log(u2);

    ran1 = (tan(w1)*(M_PI_2 - w1));
    ran2 = log( w2*cos(w1) / (M_PI_2-w1) );
    ran = ran1 + ran2;

    return ran;
}