LIBINCLUDE = -ltrace -lm -Wall

all: realcount streaming countsketchU countsketchRV

realcount: entropy_real_count.c
	gcc -o real entropy_real_count.c hash.c  array_reset.c $(LIBINCLUDE)

realcount_time: entropy_real_count.c
	gcc -o real_time entropy_real_count_time.c hash.c  array_reset.c $(LIBINCLUDE)

streaming: entropy_streaming.c
	gcc -o streaming entropy_streaming.c hash.c array_reset.c sample_add.c estimate_s.c exact_count.c find_med.c $(LIBINCLUDE)

countsketchU: entropy_countsketch_Usampling.c
	gcc -o countsketch_U entropy_countsketch_Usampling.c find_med.c array_reset.c hash.c estimate_s.c   $(LIBINCLUDE)

countsketchRV: entropy_countsketch_RVsampling.c
	gcc -o countsketch_RV entropy_countsketch_RVsampling.c find_med.c array_reset.c hash.c estimate_s.c  $(LIBINCLUDE)

clean:
	rm -f streaming countsketch_RV real countsketch_U

