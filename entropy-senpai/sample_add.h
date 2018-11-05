///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: sample_add.h
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

#ifndef SAMPLE_ADD_H
#define SAMPLE_ADD_H
#include "struct.h" 

void sample_add(struct countsource *add_count,struct countsource *newnode_add, unsigned int key_add, long long hashvalue_add);

#endif
