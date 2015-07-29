#include <stdio.h>
#include <string.h>
#include <omp.h>

#include "qsim_magic.h"

int main()
{
	int array[4];
	memset(array, 0, sizeof(array));
	qsim_magic_enable();
	#pragma omp parallel for
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 100; j++)
			array[i]++;
	}
	qsim_magic_disable();

	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += array[i];
	printf("sum is %d\n", sum);

	return 0;
}
