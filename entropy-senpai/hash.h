///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: hash.h
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
#ifndef HASH_H
#define HASH_H

long hash31(long long a, long long b, long long x);
long fourwise(long long a, long long b, long long c, long long d, long long x);

#endif
