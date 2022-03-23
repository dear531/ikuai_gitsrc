#include <stdio.h>

int *status_int_retuen()
{
	static int i = 0;
	i++;
	return &i;
}

int main()
{
	int *pi = status_int_retuen();
	printf("*pi:%d\n", *pi);
	pi = status_int_retuen();
	printf("*pi:%d\n", *pi);
	pi = status_int_retuen();
	printf("*pi:%d\n", *pi);
	return 0;
}
