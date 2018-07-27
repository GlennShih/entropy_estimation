#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

#define PCG_MAX  ‭4294967295‬
static uint64_t       state      = 0x4d595df4d0f33173;		// Or something seed-dependent
static uint64_t const multiplier = 6364136223846793005u;
static uint64_t const increment  = 1442695040888963407u;	// Or an arbitrary odd constant

double ran_produce();
static uint32_t rotr32(uint32_t x, unsigned r);
uint32_t pcg32(void);
void pcg32_init(uint64_t seed);

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
    pcg32_init(seed);//set the seed

    if(size==14) size=1;
    else if(size==15) size=2;
    else if(size==16) size=4;
    else if(size==17) size=8;
    else if(size==18) size=16;
    else if(size==19) size=32;
    else if(size==20) size=64;
    
    file_out = fopen(output_name, "wb");
    int i;
    double array;
    for(i=0; i<16384*size; i++)
    {
        array = ran_produce();
        fprintf(file_out, "%lf\n", array);
    }
    fclose(file_out);
}

double ran_produce()
{
    int i1,i2;
    double u1, u2, w1, w2, ran, ran1, ran2;
    int i;

    while(1)
    {
        i1=pcg32();
        if(i1>0 && i1<RAND_MAX)
        {
            u1=(double)i1/RAND_MAX;
            break;
        }
    }
    while(1)
    {
        i2=pcg32();
        if(i2>0 && i2<RAND_MAX)
        {
            u2=(double)i2/RAND_MAX;
            break;
        }
    }

    w1 = M_PI*(u1-0.5);
    w2 = -log10(u2);

    ran1 = (tan(w1)*(M_PI_2 - w1));
    ran2 = log10( w2*cos(w1) / (M_PI_2-w1) );
    ran = ran1 + ran2;

    return ran;
}

static uint32_t rotr32(uint32_t x, unsigned r)
{
	return x >> r | x << (-r & 31);
}

uint32_t pcg32(void)
{
	uint64_t x = state;
	unsigned count = (unsigned)(x >> 59);		// 59 = 64 - 5

	state = x * multiplier + increment;
	x ^= x >> 18;								// 18 = (64 - 27)/2
	return rotr32((uint32_t)(x >> 27), count);	// 27 = 32 - 5
}

void pcg32_init(uint64_t seed)
{
	state = seed + increment;
	(void)pcg32();
}