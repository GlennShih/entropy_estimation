# entropy_estimation

"sourcedemo.c"
Entropy calculation by lookup table, with different table size value from 2^14 ~ 2^19.
(You will NEED libtrace libraries to run this file)


"paper.c"
Entropy calculation by paper algorithm.


"random_produce.c"
calculate the H(p) function in the algorithm


"rand_nomask.c" "pcg_nomask.c"
Table generator for "sourcedemo.c", creat table size from 2^14 ~ 2^20.
