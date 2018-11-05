///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: entropy.h
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
//the header file for entropy caculation c code "entropy_streaming ; entropy_real_count ; entropy_countsketch_Usampling"

#include "libtrace.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#include "struct.h" 
#include "hash.h" 
#include "find_med.h" 
#include "sample_add.h" 
#include "estimate_s.h" 
#include "array_reset.h" 
#include "exact_count.h" 

//#define m 32082200		//packet_count of trace
#define estsize 5120		//estimate table size (z)
#define group 4			//numder of group (g)
//count sketch table size
#define bin 32768
#define h 3 			//numder of count sketch
#define bin10k 10000