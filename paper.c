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

/* Algorithm 1 in paper, simulate the maximally skewed stable distribution
 * F(x;1,-1,pi/2,0)
 */
double ran_produce()
{
//    int i1,i2;
    double u1, u2, w1, w2, ran, ran1, ran2;
/*
    int i;

    while(1)
    {
        i1=rand();
        if(i1>0 && i1<RAND_MAX)
        {
            u1=(double)i1/(double)RAND_MAX;
            break;
        }
    }
    while(1)
    {
        i2=rand();
        if(i2>0 && i2<RAND_MAX) 
        {
            u2=(double)i2/(double)RAND_MAX;
            break;
        }
    }
*/
    u1 = (double)rand() / (double)RAND_MAX;
    u2 = (double)rand() / (double)RAND_MAX;
    w1 = M_PI*(u1-0.5);
    w2 = -log(u2);

    ran1 = (tan(w1)*(M_PI_2 - w1));
    ran2 = log( w2*cos(w1) / (M_PI_2-w1) );
    ran = ran1 + ran2;

    return ran;
}

static inline void print_mac(uint8_t *mac) {

	printf("%02x:%02x:%02x:%02x:%02x:%02x ", mac[0], mac[1], mac[2], mac[3],
		mac[4], mac[5]);

}

/* Given a sockaddr containing an IP address, prints the IP address to stdout
 * using the common string representation for that address type */
static inline void print_ip(struct sockaddr *ip) {

	char str[20];
	
	/* Check the sockaddr family so we can cast it to the appropriate
	 * address type, IPv4 or IPv6 */
	if (ip->sa_family == AF_INET) {
		/* IPv4 - cast the generic sockaddr to a sockaddr_in */
		struct sockaddr_in *v4 = (struct sockaddr_in *)ip;
		/* Use inet_ntop to convert the address into a string using
		 * dotted decimal notation */
		printf("%s\t", inet_ntop(AF_INET, &(v4->sin_addr), str, 20));
	}

	if (ip->sa_family == AF_INET6) {
		/* IPv6 - cast the generic sockaddr to a sockaddr_in6 */
		struct sockaddr_in6 *v6 = (struct sockaddr_in6 *)ip;
		/* Use inet_ntop to convert the address into a string using
		 * IPv6 address notation */
		printf("%s ", inet_ntop(AF_INET6, &(v6->sin6_addr), str, 20));
	}


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



	uint32_t i,Y=0;
	double z[20]={0.0};
	uint32_t uint32_ip;
	long m = atol(argv[2]);
	
	

        while (trace_read_packet(trace,packet)>0) {

		struct sockaddr_storage addr;
		struct sockaddr *addr_ptr;
		addr_ptr = trace_get_source_address(packet, (struct sockaddr *)&addr);
		if (addr_ptr == NULL)
			printf("NULL ");
		else {
			// Update packet counter
			Y++;
			uint32_ip = get_ip_int(addr_ptr);
			//Seed the PRNG with it
			srand(uint32_ip);
			
			for(i=0;i<20;i++)
			{
				z[i]+=ran_produce();
			}
			//observe inteval ended. Packet counter == Trace packet count
			if(Y==m)
			{
				for(i=0;i<20;i++){
					z[i] /= m;
				}
				printf("Entropy = %lf\n",H_function(z,1,m));
				for(i=0;i<20;i++){
					z[i] = 0.0;
				}
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
	printf("Packet Count = %d\n",Y);
        return 0;
}
