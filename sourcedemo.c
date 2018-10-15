/* Libtrace program designed to demonstrate the use of the trace_get_source_*
 * shortcut functions. 
 *
 * This code also contains examples of sockaddr manipulation.
 */
#include "libtrace.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "random_produce.h"
/* This is not the nicest way to print a 6 byte MAC address, but it is 
 * effective. Libtrace will have provided us a pointer to the start of the
 * MAC address within the packet, so we can just use array indices to grab
 * each byte of the MAC address in turn */
static inline void print_mac(uint8_t *mac) {

	printf("%02x:%02x:%02x:%02x:%02x:%02x ", mac[0], mac[1], mac[2], mac[3],
		mac[4], mac[5]);

}

uint32_t get_ip_int(struct sockaddr *ip)//ip轉int
{
	struct in_addr source_ip_addr;
	
	if (ip->sa_family == AF_INET) {
		struct sockaddr_in *v4 = (struct sockaddr_in *)ip;
		source_ip_addr=v4->sin_addr;
	}

	return ntohl(source_ip_addr.s_addr);
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

int main(int argc, char **argv)
{
        /* This is essentially the same main function from readdemo.c */

        libtrace_t *trace = NULL;
        libtrace_packet_t *packet = NULL;

	/* Ensure we have at least one argument after the program name */
        if (argc < 4) {
                fprintf(stderr, "Usage: %s  <trace file> <packet count> <array file>\n", argv[0]);
                return 1;
        }

        packet = trace_create_packet();

        if (packet == NULL) {
                perror("Creating libtrace packet");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        trace = trace_create(argv[1]);

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

	int mag3[20][3] = {
        {1, 3,10}, {1,11, 6}, {2, 5,15}, {2, 7, 7}, {2, 7, 9},
        {2, 9,15}, {3, 1,14}, {3,13, 7}, {4, 5,15}, {5, 9, 7},
        {5,13, 6}, {6, 1,11}, {7, 1, 9}, {9, 5, 1}, {11,7,12},
        {14,1,15}, {14,13,15}, {1,5,16},{1,11,16},{11,7,16}
  	};

	
	uint32_t i,Y=0;
	double z[20]={0.0}, lookup_table[524288], tmp2;
	uint32_t int_ip,tmp;
	long m = atol(argv[2]);
	int size;// = atol(argv[4]);

	//read array table
	FILE *filein=NULL;
	filein = fopen(argv[3],"r");
	while(fscanf(filein, "%lf", &lookup_table[i]) != EOF) i++;
	if(i==16384) size = 14;
	else if(i==32768) size = 15;
	else if(i==65536) size = 16;
	else if(i==131072) size = 17;
	else if(i==262144) size = 18;
	else if(i==524288) size = 19;
	//else if(i==1048576) size = 20;

        while (trace_read_packet(trace,packet)>0) {

		struct sockaddr_storage addr;
		struct sockaddr *addr_ptr;
		addr_ptr = trace_get_source_address(packet, (struct sockaddr *)&addr);
		if (addr_ptr == NULL)
			printf("NULL ");
		else {
			Y++;
			int_ip = get_ip_int(addr_ptr);
			for(i=0;i<20;i++)
			{
				/*
				 *	XOR Random number generator
				 *	shift first then do XOR
				 *	here will have 2^32-1 for 32-bit words
				*/
				tmp = int_ip^(int_ip << mag3[i][0]);
				tmp ^= (tmp >> mag3[i][1]);
				tmp ^= (tmp << mag3[i][2]);
				
				if(size==14) tmp &= 0x00003fff;
				else if(size==15) tmp &= 0x00007fff;
				else if(size==16) tmp &= 0x0000ffff;
				else if(size==17) tmp &= 0x0001ffff;
				else if(size==18) tmp &= 0x0003ffff;
				else if(size==19) tmp &= 0x0007ffff;
				//else if(size==20) tmp &= 0x000fffff;
				tmp2 = lookup_table[tmp];
				z[i]+=tmp2;
			}
			if(Y==m)
			{
				for(i=0;i<20;i++) z[i]/=m;
				printf("%lf\n",H_function(z,1,m));
				for(i=0;i<20;i++) z[i]=0.0;
				break;
			}
		}
		
		
		//printf("%lf",ran_produce(int_ip));
		
		//putchar(10);
        }


        if (trace_is_err(trace)) {
                trace_perror(trace,"Reading packets");
                libtrace_cleanup(trace, packet);
                return 1;
        }

        libtrace_cleanup(trace, packet);
	//double p[3]={1,2,3};
	//for(i=0;i<20;i++) y[i]=y[i]/Y;
	printf("Y=%d, size=%d\n",Y,size);
	//printf("H(p) = %lf\n",H_function(y,0,Y));
	//printf("normal H(p) = %lf\n",H_function(y,1,Y));
	/*for(i=0;i<20;i++)
	{
		printf("number %2d :%15lf  %15lf",i,y[i],y[i+20]);
		y[i]+=y[i+20];
		y[i]/=Y;
		printf("%15lf\n",y[i]);
	}
	printf("normal H(p) = %lf\n",H_function(y,1,Y));*/
        return 0;
}
