///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: struct.h
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
#ifndef STRUCT_H
#define STRUCT_H

struct countsource
{
	unsigned int key;
	unsigned int counter;
	struct countsource *next_key;
};

#endif
