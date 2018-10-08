#include "random_produce.h"


double H_function(double y[], char normalize, int Y)
{
    int i;
    double s=0.0;
    
    for(i=0;i<20;i++){
    	s += exp(y[i]);
    }
    
    s = -log((1.0/20.0)*s);
    
    if(normalize){
    	s /= log(Y);
    }
    
    return s;
}
