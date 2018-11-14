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
    uint32_t lineA=0, lineB=0;
	uint32_t i=0,Y=0;
	double z[K_VALUE]={0.0}, lookup_tableA[262144], tmp2=0.0;
	uint32_t int_ip,tmp;
	uint32_t m = atol(argv[2]);
	int size;// = atol(argv[4]);

	//read array table
    /*
	//FILE *filein=NULL;
	//filein = fopen(argv[3],"r");
	//while(fscanf(filein, "%lf", &lookup_table[i]) != EOF) i++;
	*/
    FILE *fileinA=NULL;
    FILE *fileinB=NULL;
	fileinA = fopen(argv[3],"r");

	while(fscanf(fileinA, "%lf", &lookup_tableA[lineA]) != EOF)
    {
        lineA++;
    }
    fclose(fileinA);
    
    double lookup_tableB[262144];
	fileinB = fopen(argv[4],"r");

    while(fscanf(fileinB, "%lf", &lookup_tableB[lineB]) != EOF)
    {
        lineB++;
    } 
    fclose(fileinB);


	if(lineA==16384) size = 14;
	else if(lineA==32768) size = 15;
	else if(lineA==65536) size = 16;
	else if(lineA==131072) size = 17;
	else if(lineA==262144) size = 18;
	else if(lineA==524288) size = 19;
	else if(lineA==1048576) size= 20;
    printf("size=%d\n",size);

    while (trace_read_packet(trace,packet)>0) {

		struct sockaddr_storage addr;
		struct sockaddr *addr_ptr;
		addr_ptr = trace_get_source_address(packet, (struct sockaddr *)&addr);
		if (addr_ptr == NULL)
			printf("NULL ");
		else {
			Y++;
			int_ip = get_ip_int(addr_ptr);
			//printf("%u\n",int_ip);
			srand(int_ip);
			for(i=0;i<10;i++)
			{
				if(size==14) tmp = rand()%16384;
				else if(size==15) tmp = rand()%32768;
				else if(size==16) tmp = rand()%65536;
				else if(size==17) tmp = rand()%131072;
				else if(size==18) tmp = rand()%262144;
				else if(size==19) tmp = rand()%524288;
				else if(size==20) tmp = rand()%1048576;
				//else if(size==K_VALUE) tmp &= 0x000fffff;
                //printf("tmp=%u\n",tmp);
				tmp2 = lookup_tableA[tmp];
				z[i]+=tmp2;
			}
			for(i=10;i<20;i++)
			{
				if(size==14) tmp = rand()%16384;
				else if(size==15) tmp = rand()%32768;
				else if(size==16) tmp = rand()%65536;
				else if(size==17) tmp = rand()%131072;
				else if(size==18) tmp = rand()%262144;
				else if(size==19) tmp = rand()%524288;
				else if(size==20) tmp = rand()%1048576;
				//else if(size==K_VALUE) tmp &= 0x000fffff;
                //printf("tmp=%u\n",tmp);
				tmp2 = lookup_tableB[tmp];
				z[i]+=tmp2;
			}            
			if(Y==m)
			{
				for(i=0;i<K_VALUE;i++)
                {
                    z[i]/=m;
                    //printf("z[i]=%lf\n",z[i]);
                }
                printf("%lf\n", H_function(z,1,m));
				//printf("RAND_MAX=%u\n",RAND_MAX);
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

	printf("Y=%d, size=%d\n",Y,size);

        return 0;
}
