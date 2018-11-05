///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: find_med.c
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

/*find_median
"find_med" for double array (estimate S)
"find_med_c" for int array (count sketch)
*/
double find_med_double(int group_g, double *value)
{
int pass = 0;
int j = 0;
double hold = 0.0 ;
double med_value = 0.0 ;
for(pass = 1; pass< group_g; pass++)
{
	for(j=0;j<(group_g-1);j++)
	{
		if(value[j]>value[j+1])
		{
			hold = value[j];
			value[j] = value[j+1];
			value[j+1] = hold;
		}
	}
}
if(group_g & 1) //group_g is odd
	med_value = value[group_g/2];
else
	med_value = (value[((group_g/2)-1)]+value[(group_g/2)])/2 ;
return med_value;
}

int find_med_int(int group_g, int *value)
{

int pass = 0;
int j = 0;
int hold = 0.0 ;
int med_value = 0.0 ;
for(pass = 1; pass< group_g; pass++)
{
	for(j=0;j<(group_g-1);j++)
	{
		if(value[j]>value[j+1])
		{
			hold = value[j];
			value[j] = value[j+1];
			value[j+1] = hold;
		}
	}
}
if(group_g & 1) //group_g is odd
	med_value = value[group_g/2];
else
	med_value = (value[((group_g/2)-1)]+value[(group_g/2)])/2 ;
return med_value;
}
