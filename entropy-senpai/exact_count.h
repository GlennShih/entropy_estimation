///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: exact_count.h
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
//exact count per sampled packet (streaming)

#ifndef EXACT_COUNT_H
#define EXACT_COUNT_H
#include "struct.h" 
void exact_count(struct countsource *count_e, unsigned int key_e, long long hashvalue_e);

#endif
