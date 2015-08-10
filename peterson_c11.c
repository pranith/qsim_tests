/*
 * A basic peterson lock algorithm
 */

#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define USE_BARRIER 0
#include "barrier.h"
#include "qsim_magic.h"

atomic_int victim, r1, r2, wait;
volatile unsigned long counter;
unsigned long iter = 100;

#define QSIM_ENABLE 1

void *thread1(void *arg)
{
	while(wait == 0);
	for (unsigned long i = 0; i < iter; i++) {
		atomic_store_explicit(&r1, 1, memory_order_release);
		atomic_store_explicit(&victim, 1, memory_order_release);
		while(atomic_load_explicit(&victim, memory_order_acquire) == 1 && atomic_load_explicit(&r2, memory_order_acquire));

		counter++; 	// CS
		atomic_store_explicit(&r1, 0, memory_order_release);
	}

	return NULL;
}

void *thread2(void *arg)
{
	while(wait == 0);
	for (unsigned long i = 0; i < iter; i++) {
		atomic_store_explicit(&r2, 1, memory_order_release);
		atomic_store_explicit(&victim, 2, memory_order_release);
		while(atomic_load_explicit(&victim, memory_order_acquire) == 2 && atomic_load_explicit(&r1, memory_order_acquire));

		counter++; 	// CS
		atomic_store_explicit(&r2, 0, memory_order_release);
	}

	return NULL;
}

int main()
{
	pthread_t tid1, tid2;

#if QSIM_ENABLE
	qsim_magic_enable();
#endif
	for (int i = 0; i < 1; i++) {
		counter = 0;
		pthread_create(&tid1, NULL, thread1, NULL);
		pthread_create(&tid2, NULL, thread2, NULL);
		wait = 1;

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		barrier();
		printf("counter is %lu\n", counter);
	}
#if QSIM_ENABLE
	qsim_magic_disable();
#endif

	return 0;
}
