///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: sample_add.c
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
//add new node (struct countsource) for sampled packet (streaming)
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

void sample_add(struct countsource *add_count,struct countsource *newnode_add, unsigned int key_add, long long hashvalue_add)
{
struct countsource *sampleadd={0};
	if(add_count[hashvalue_add].key == 0)
		{
			add_count[hashvalue_add].key = key_add;
			add_count[hashvalue_add].counter = 1;
			add_count[hashvalue_add].next_key = NULL;
		}
	else
		{
			sampleadd = &add_count[hashvalue_add];
			while(sampleadd->next_key!=NULL)
			{
				sampleadd = sampleadd->next_key;
			}
			newnode_add = malloc(sizeof(struct countsource));
			newnode_add->key = key_add;
			newnode_add->counter = 1;
			newnode_add->next_key = NULL;
			sampleadd->next_key = newnode_add;
		}
return;
}