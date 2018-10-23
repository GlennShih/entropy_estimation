#include "random_produce.h"
#define K_VALUE 20

long double H_function(long double y[], char normalize, int Y)
{
    int i;
    long double s=0.0;
    
    for(i=0;i<K_VALUE;i++){
    	s += exp(y[i]);
    }
    
    s = -log( (1.0/(long double)K_VALUE) * s );
    
    if(normalize){
    	s /= log(Y);
    	//printf("normalize\n");
    }
    
    return s;
}
