#include "libtrace.h"
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <getopt.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "dSFMT.h"
#include <time.h>
#define K_VALUE 20

/*
 *   Random number generator by Mersenne twister
 *   from dSFMT-src-2.2.3 howto-compile.html sample3.c
 *   return a double float random number between (0,1)
 */
 double dsfmt_rand(uint32_t seed){
    int seed_cnt;
    double x;
    uint32_t seeds[100];
    dsfmt_t dsfmt;

    seeds[0] = seed;
    //printf("seed=%u\n",seed);
    seed_cnt = 1;
    dsfmt_init_by_array(&dsfmt, seeds, seed_cnt);
    x = dsfmt_genrand_open_open(&dsfmt);
    
    return x;
 } 

/*
 *   Random number generator by Mersenne twister
 *   from dSFMT-src-2.2.3 howto-compile.html sample2.c
 *   return a double float random number between (0,1)
 */
double dsfmt_rand_sample2(uint32_t seed){
    int i,j=0;
    double x, y;
    const int NUM = 1;
    const int R_SIZE = 2 * NUM;
    int size;
    double *array;
    dsfmt_t dsfmt;

    size = dsfmt_get_min_array_size();
    if (size < R_SIZE) {
	   size = R_SIZE;
    }

#if defined(__APPLE__) || \
    (defined(__FreeBSD__) && __FreeBSD__ >= 3 && __FreeBSD__ <= 6)
    printf("malloc used\n");
    array = malloc(sizeof(double) * size);
    if (array == NULL) {
	printf("can't allocate memory.\n");
	return 1;
    }
#elif defined(_POSIX_C_SOURCE)
    //printf("posix_memalign used\n");
    if (posix_memalign((void **)&array, 16, sizeof(double) * size) != 0) {
	printf("can't allocate memory.\n");
	return 1;
    }
#elif defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
    //printf("memalign used\n");
    array = memalign(16, sizeof(double) * size);
    if (array == NULL) {
	printf("can't allocate memory.\n");
	return 1;
    }
#else /* in this case, gcc doesn't suppport SSE2 */
    array = malloc(sizeof(double) * size);
    if (array == NULL) {
	printf("can't allocate memory.\n");
	return 1;
    }
#endif

    dsfmt_init_gen_rand(&dsfmt, seed);
    dsfmt_fill_array_open_open(&dsfmt, array, size);

    /*
    for(i=0;i<NUM;i++){
        printf("%lf\n",array[j++]);
    }
    */

    x = array[0];

    printf("%lf\n",array[0]);
    printf("%lf\n",array[1]);

    free(array);

    return x;
}

void main(){
    int i;
    //printf("%lf\n",dsfmt_rand(uint32_t seed));
    //dsfmt_rand_sample2(4294967295);
    //srand(time(NULL));
    //for(i=0;i<10000;i++){
    //    printf("%lf\n",dsfmt_rand_sample2(rand()));
    //}
    dsfmt_rand_sample2(1);
}