#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *a, *b, *c, *d, *e;

	a = malloc(1);
	b = malloc(2);
	c = malloc(10);
	d = malloc(50);
	e = malloc(100);

	printf("a = %p; header = 0x%lX\n", a, *(long *)(a - 8));
	printf("b = %p; header = 0x%lX\n", b, *(long *)(b - 8));
	printf("c = %p; header = 0x%lX\n", c, *(long *)(c - 8));
	printf("d = %p; header = 0x%lX\n", d, *(long *)(d - 8));
	printf("e = %p; header = 0x%lX\n", e, *(long *)(e - 8));

        return 0;
}
