///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: hash.c
// Project: estimate_entropy
// Author:$Author$       
// Date:2014/05/27
// Dependencies:
// 
// Revision:$LastChangedRevision$ 
// Info:$Id$
// Description: $Source$
// 
//
// Copyright notice:  Copyright (C)2012 CNSRL CYCU
// Change history:
// $LastChangeDate$
// $LastChangedBy$ 
//
//
///////////////////////////////////////////////////////////////////////////////

// Probabilistic Random Number Generators
// Collected from various sources by Graham Cormode, 2000-2003
// 

#define MOD 2147483647
#define HL 31

long hash31(long long a, long long b, long long x)
{

    long long result;
    long lresult;

    // return a hash of x using a and b mod (2^31 - 1)
// may need to do another mod afterwards, or drop high bits
// depending on d, number of bad guys
// 2^31 - 1 = 2147483647

    //  result = ((long long) a)*((long long) x)+((long long) b);
    result = (a * x) + b;
    result = (result >> HL) + (result & MOD);
	if (result > MOD)
	result=result-MOD;
    lresult = (long) result;

    return (lresult);
}

long fourwise(long long a, long long b, long long c, long long d, long long x)
{
    long long result;
    long lresult;

    // returns values that are 4-wise independent by repeated calls
    // to the pairwise indpendent routine. 

    result = hash31(hash31(hash31(x, a, b), x, c), x, d);
    lresult = (long) result;
    return lresult;
}
