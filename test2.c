#include <stdio.h>

volatile int i = 0;

int main()
{
	for (i = 0; i<100000;i++)
		i++;

	printf("%d\n", i);

	return 0;
}
