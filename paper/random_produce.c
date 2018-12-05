#include "random_produce.h"
#define K_VALUE 20

//long double H_function(long double y[], char normalize, uint32_t Y)
double H_function(double y[], char normalize, uint32_t Y)
{
    int i;
    //long double s=0.0;
    double s=0.0;
    
    for(i=0;i<K_VALUE;i++){
    	s += exp(y[i]);
    }
    
    //s = -log( (1.0/(long double)K_VALUE) * s );
    s = -log( (1.0/(double)K_VALUE) * s );
    
    if(normalize){
    	s /= log(Y);
    	//printf("normalize\n");
    }
    
    return s;
}
