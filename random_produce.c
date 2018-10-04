#include "random_produce.h"

//y[] is yi=yi+Rj(it)xdt
//normalize is DO normalize or NOT
//Y is packet count

double H_function(double y[], char normalize, int Y)
{
    int i;
    double s=0;
    
    for(i=0;i<20;i++){
      s += exp(y[i]);
    } 
    s = -log10(0.05*s);
    if(normalize) s /= log10(Y);
    return s;
}
