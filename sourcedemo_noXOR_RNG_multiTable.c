/* Libtrace program designed to demonstrate the use of the trace_get_source_*
 * shortcut functions. 
 *
 * This code also contains examples of sockaddr manipulation.
 */
#include "libtrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "random_produce.h"
#define K_VALUE 20

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
        if (argc < 5) {
                fprintf(stderr, "Usage: %s  <trace file> <packet count> <array file1> <array file2>\n", argv[0]);
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

	uint32_t i=0,Y=0,lineA=0, lineB=0;
	long double z[K_VALUE]={0.0}, tmp2=0.0;
    long double lookup_tableA[524288], lookup_tableB[524288];
	uint32_t int_ip,tmp;
	long m = atol(argv[2]);

	//read array table
	FILE *fileinA=NULL;
    FILE *fileinB=NULL;
	fileinA = fopen(argv[3],"r");
  	fileinB = fopen(argv[4],"r");

    //Read the .txt file and count how many lines in the file  
	while(fscanf(fileinA, "%Lf", &lookup_tableA[lineA]) != EOF) lineA++;
    //printf("lineA=%u\n",lineA);
    while(fscanf(fileinB, "%Lf", &lookup_tableB[lineB]) != EOF) lineB++;
    //printf("lineA=%u\n",lineB);

    while (trace_read_packet(trace,packet)>0) {

        struct sockaddr_storage addr;
        struct sockaddr *addr_ptr;
        addr_ptr = trace_get_source_address(packet, (struct sockaddr *)&addr);
        if (addr_ptr == NULL)
            printf("NULL ");
        else{
            /* total packet count ++ */
            Y++;
            int_ip = get_ip_int(addr_ptr);
            //printf("%u\n",int_ip);
            /* seed the rand() */
            srand(int_ip);
            for(i=0;i<10;i++)
            {
                /* size = 14 */
                if(lineA==16384) tmp = rand()%16384;
                /* size = 15 */
                else if(lineA==32768) tmp = rand()%32768;
                /* size = 16 */
                else if(lineA==65536) tmp = rand()%65536;
                /* size = 17 */
                else if(lineA==131072) tmp = rand()%131072;
                /* size = 18 */
                else if(lineA==262144) tmp = rand()%262144;
                /* size = 19 */
                else if(lineA==524288) tmp = rand()%524288;
                /* size = 20 */
                else if(lineA==1048576) tmp = rand()%1048576;
                //else if(line==K_VALUE) tmp &= 0x000fffff;
                tmp2 = lookup_tableA[tmp];
                z[i]+=tmp2;
            }
            
            for(i=11;i<20;i++)
            {
                /* size = 14 */
                if(lineB==16384) tmp = rand()%16384;
                /* size = 15 */
                else if(lineB==32768) tmp = rand()%32768;
                /* size = 16 */
                else if(lineB==65536) tmp = rand()%65536;
                /* size = 17 */
                else if(lineB==131072) tmp = rand()%131072;
                /* size = 18 */
                else if(lineB==262144) tmp = rand()%262144;
                /* size = 19 */
                else if(lineB==524288) tmp = rand()%524288;
                /* size = 20 */
                else if(lineB==1048576) tmp = rand()%1048576;
                //else if(line==K_VALUE) tmp &= 0x000fffff;
                tmp2 = lookup_tableB[tmp];
                z[i]+=tmp2;
            }        
            
            /* Trace ended, print Entropy value and reset array*/
            if(Y==m)
            {
                for(i=0;i<K_VALUE;i++) z[i]/=m;
                printf("%Lf\n",H_function(z,1,m));
                for(i=0;i<K_VALUE;i++) z[i]=0.0;
                break;
            }
            }			
    }

    if (trace_is_err(trace)) {
        trace_perror(trace,"Reading packets");
        libtrace_cleanup(trace, packet);
        return 1;
    }

    libtrace_cleanup(trace, packet);

	printf("Y=%d, size=%lf\n",Y,log(lineA)/log(2));

    return 0;
}
