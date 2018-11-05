#include <stdio.h>
#include <stdlib.h>
#include "dSFMT.h"

int main(int argc, char* argv[]) {
    int i, cnt, seed;
    double x, y, pi;
    const int NUM = 10;
    dsfmt_t dsfmt;

    if (argc >= 2) {
	seed = strtol(argv[1], NULL, 10);
    } else {
	seed = 12345;
    }
    cnt = 0;
    dsfmt_init_gen_rand(&dsfmt, seed);
    for (i = 0; i < NUM; i++) {
	x = dsfmt_genrand_open_open(&dsfmt);
	y = dsfmt_genrand_open_open(&dsfmt);
    printf("x=%f\n",x);
    }

    return 0;
}