#include <stdio.h>
#include "prng.h"

int main()
{
    int i;
    prng_type * prng;
    prng = prng_Init(27751, 2);
    //RanrotAInit(prng,27751);
    for(i=0;i<10;i++)
    {
        printf("prng_float=%f\n",prng_float(prng));
        //printf("prng_normal=%lf\n",prng_normal(prng));
    }
    
    prng_Destroy(prng);
    return 0;
}