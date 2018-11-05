///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: estimate_s.h
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

/*estimate S (entropy norm)
"estimate_s" for struct countsource array (streaming)
"estimate_s_c" for int array (count sketch)
*/
#ifndef ESTIMATE_S_H
#define ESTIMATE_S_H

double estimate_s(struct countsource *count, int packetcount , int estsize_z);
double estimate_s_c(int *count, int packetcount , int estsize_z);

#endif