#include "random_produce.h"


double H_function(double y[], char normalize, int Y)
{
    int i;
    double s=0;
    
    for(i=0;i<20;i++) s += exp(y[i]);
    s = -log10(0.05*s);
    if(normalize) s /= log10(Y);
    return s;
}
