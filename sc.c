#include "barrier.h"
#include "qsim_magic.h"
#include <stdatomic.h>
#include <stdlib.h>

#define KB(x) ((x) << 10)
#define MB(x) (KB(x) << 10)

#define size MB(16)

#define QSIM_ENABLE 1
#define CACHE_LINE_SIZE 64

int main()
{
	unsigned long max_idx = size / sizeof(atomic_int);
	atomic_int *array;

	array = (atomic_int*)malloc(size);


#if QSIM_ENABLE
	qsim_magic_enable();
#endif
	for (int i = 0; i < 1; i++) 
		for (unsigned long j = 0; j < max_idx; j+= CACHE_LINE_SIZE / sizeof(atomic_int))
			atomic_store_explicit(array+j, j*i, memory_order_seq_cst);
#if QSIM_ENABLE
	qsim_magic_disable();
#endif
}
