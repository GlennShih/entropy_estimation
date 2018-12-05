/* Libtrace program designed to demonstrate the use of the trace_get_source_*
 * shortcut functions. 
 *
 * This code also contains examples of sockaddr manipulation.
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "random_produce.h"
#include "libtrace.h"
#define K_VALUE 20

// 定义MT19937-32的常数
enum
{
    // 假定 W = 32 (此项省略)
    N = 624,
    M = 397,
    R = 31,
    A = 0x9908B0DF,

    F = 1812433253,

    U = 11,
    // 假定 D = 0xFFFFFFFF (此项省略)

    S = 7,
    B = 0x9D2C5680,

    T = 15,
    C = 0xEFC60000,

    L = 18,

    MASK_LOWER = (1ull << R) - 1,
    MASK_UPPER = (1ull << R)
};

static uint32_t  mt[N];
static uint16_t  index;

// 根据给定的seed初始化旋转链
void Initialize(const uint32_t seed)
{
    uint32_t  i;
    mt[0] = seed;
    for ( i = 1; i < N; i++ )
    {
        mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
    }
    index = N;
}

static void Twist()
{
    uint32_t  i, x, xA;
    for ( i = 0; i < N; i++ )
    {
        x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);
        xA = x >> 1;
        if ( x & 0x1 )
        {
            xA ^= A;
        }
        mt[i] = mt[(i + M) % N] ^ xA;
    }

    index = 0;
}

// 产生一个32位随机数
uint32_t ExtractU32()
{
    uint32_t  y;
    int       i = index;
    if ( index >= N )
    {
        Twist();
        i = index;
    }
    y = mt[i];
    index = i + 1;
    y ^= (y >> U);
    y ^= (y << S) & B;
    y ^= (y << T) & C;
    y ^= (y >> L);
    return y;
}

/* Algorithm 1 in paper, simulate the maximally skewed stable distribution
 * F(x;1,-1,pi/2,0)
 */
long double ran_produce()
{
    long long i1,i2;
    long double u1, u2, w1, w2, ran, ran1, ran2;

    u1=(long double)ExtractU32()/4294967295;
    u2=(long double)ExtractU32()/4294967295;
    //printf("u1=%Lf\n",u1);
    //printf("u2=%Lf\n",u2);
    w1 = M_PI*(u1-0.5);
    w2 = -log(u2);

    ran1 = tan(w1) * (M_PI_2 - w1);
    ran2 = log( w2*cos(w1) / (M_PI_2-w1) );
    ran = ran1 + ran2;

    return ran;
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
	long double z[K_VALUE]={0.0};
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
			//srand(uint32_ip);
            Initialize(uint32_ip);
			for(i=0;i<K_VALUE;i++)
			{
 				z[i]+=ran_produce();
			}
			//observe inteval ended. Packet counter == Trace packet count
			if(Y==m)
			{
				for(i=0;i<K_VALUE;i++){
					z[i] /= m;
				}
				printf("Entropy = %Lf\n",H_function(z,1,m));
				for(i=0;i<K_VALUE;i++){
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
