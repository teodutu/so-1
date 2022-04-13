#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
        char c;

	printf("brk before = %p\n", sbrk(0));
        scanf("%c", &c);

        printf("malloc = %p\n", malloc(25 * getpagesize()));
        printf("brk after = %p\n", sbrk(0));

        scanf("%c", &c);	

        return 0;
}
