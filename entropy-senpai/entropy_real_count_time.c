///////////////////////////////////////////////////////////////////////////////
// CNSRL
// Department of Electrical Engineering
// Chung-Yuan Christian University
//
// File Name: entropy_real_count.c
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

#include "entropy.h"
long m; /* m = packet count in trace */

static void distnctpacket(libtrace_packet_t *packet, struct countsource *srccount ,struct countsource *newnode , int interval)
{
	struct timeval ts;
    static uint32_t packet_usec = 0;
	struct sockaddr_storage addr;
	struct sockaddr *addr_ptr;
	int a =1746357;
	int b =5595875;
	int c =3936667;
	int d =7586381;
	static int num_interval=1;
	static unsigned int countpacket = 0;
	struct countsource *node = NULL ;
	struct countsource *q_count = NULL;
	int j=0;
	static uint32_t next_report = 0;
	double entropy_value=0.0;
	double entropy =0.0;
	double value=0.0;
	unsigned int query = 0;
	static unsigned int  querytotal= 0;
	unsigned int key = 0 ;
	unsigned long int hashvalue = 0;

//=========================== interval time ==================================	
	
	ts = trace_get_timeval(packet);
	if (next_report == 0) 
	{
		next_report = ts.tv_sec + interval;
   		packet_usec = ts.tv_usec;
		printf("-------Interval %d done!-------\n",num_interval);
	}
	addr_ptr = trace_get_source_address(packet, (struct sockaddr *)&addr);

	//========================== ping ===================================
	if (addr_ptr == NULL)
		printf("NULL ");
	else{
	struct sockaddr_in *v4 = (struct sockaddr_in *)addr_ptr;
	key =(unsigned int)(v4->sin_addr.s_addr);
	//printf("key is %x\n",key);
	//countpacket += 1;
	
	if(key != 0){
	//countpacket += 1;
	hashvalue = ((unsigned long int) fourwise( a,b,c,d,(unsigned long int) key))% (unsigned long int)bin10k ;
	if(srccount[hashvalue].key == 0)
	{	
		srccount[hashvalue].key = key;
		srccount[hashvalue].counter = 1;
		srccount[hashvalue].next_key = NULL;
	}
	else
	{	
		if(srccount[hashvalue].key == key)
			srccount[hashvalue].counter = srccount[hashvalue].counter + 1;
			
		else
		{
			node = & srccount[hashvalue];
			while(node->key!= key)
			{
				if(node->next_key==NULL)
				{
					newnode = malloc(sizeof(struct countsource));
					newnode->key=key;
					newnode->counter=0;
					newnode->next_key = NULL;
					node->next_key = newnode;
				}
				else	
				{
					node = node->next_key;
				}
			}
			node->counter = node->counter + 1 ;
		}
	}
		
	}

	if ((uint32_t)ts.tv_sec >= next_report && (uint32_t)ts.tv_usec > packet_usec)//
	{

		
		
		for(j=0;j<bin10k;j++)
		{
			q_count = &srccount[j];
			if(q_count->key !=0)
			{
				query = q_count->counter;
				querytotal = querytotal + query;
				value = -((double)query/(double)countpacket)*(log((double)query/(double)countpacket)/log(2));
				entropy_value = value + entropy_value;	
				while(q_count->next_key!=NULL)
				{
					q_count = q_count->next_key;
					query = q_count->counter;
					querytotal = querytotal + query;
					value = -((double)query/(double)countpacket)*(log((double)query/(double)countpacket)/log(2));
					entropy_value = value + entropy_value;
				}//end while(q_count.next_key!=NULL)
			}//end if(query !=0)
		}// end for(j=0;j<bin10k;j++)
		
		entropy = entropy_value/(log((double)countpacket)/log(2)); 
		////printf("entropy value is %lf \n" ,entropy );
		printf("%lf\n" ,entropy );
		array_reset_struct(srccount, (int) bin10k);
		printf("interval PKT =%u\n",countpacket);
		printf("-------Interval %d done!-------\n",num_interval);
		num_interval++;

		querytotal  = 0;
		//next_report = 0;
		countpacket = 0;
		next_report += interval ;
	}// end if ((uint32_t)ts.tv_sec > next_report)
	
	//countpacket += 1; 
	
	}// end else
	countpacket += 1; 
}

	


static void libtrace_cleanup(libtrace_t *trace, libtrace_packet_t *packet) {

        /* It's very important to ensure that we aren't trying to destroy
         * a NULL structure, so each of the destroy calls will only occur
         * if the structure exists */
        if (trace)
                trace_destroy(trace);

        if (packet)
                trace_destroy_packet(packet);

}


int main(int argc, char *argv[])
{
        /* This is essentially the same main function from readdemo.c */

        libtrace_t *trace = NULL;
        libtrace_packet_t *packet = NULL;
	struct countsource src_count[bin10k];
	struct countsource *newnode1 = NULL;
	memset( src_count, 0, bin10k*sizeof(struct countsource ));
	int interval= 0;
	/* Ensure we have at least one argument after the program name */
        if (argc < 3) {
                fprintf(stderr, "Usage: %s  <trace file> <packet count>\n", argv[0]);
                return 1;
        }

        packet = trace_create_packet();

        if (packet == NULL) {
                perror("Creating libtrace packet");
                libtrace_cleanup(trace, packet);
                return 1;
        }
        trace = trace_create(argv[1]);
	interval = atol(argv[2]);
    	printf("time interval = %d seconds\n", interval);

        if (trace_is_err(trace)) {
                trace_perror(trace,"Opening trace file");
                libtrace_cleanup(trace, packet);
                return 1;
        }
        if (trace_start(trace) == -1) {
                trace_perror(trace,"Starting trace");
                libtrace_cleanup(trace, packet);
                return 1;
        }
	while (trace_read_packet(trace,packet)>0) {
                distnctpacket(packet, src_count, newnode1, interval);
		
        }
        if (trace_is_err(trace)) {
                trace_perror(trace,"Reading packets");
                libtrace_cleanup(trace, packet);
                return 1;
        }
        libtrace_cleanup(trace, packet);
        return 0;
}

