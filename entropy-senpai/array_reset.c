///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: array_reset.c
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
/*reset array
"array_reset_struct" for struct countsource array
"array_reset" for int array
*/
#include <stdio.h>
#include "struct.h" 

void array_reset_struct(struct countsource *array, int array_size)
{
int i;
 	for(i=0;i<array_size;i++)
	{
		array[i].key = 0;
		array[i].counter = 0;
		array[i].next_key = NULL ;
	}
return ;
}

void array_reset(int *array, int array_size)
{
int i;
 	for(i=0;i<array_size;i++)
	{
		array[i] = 0;	
	}
return ;
}
