#include <stdio.h>

#define TEST_FLAG 1


int main(void)
{
#if (TEST_FLAG == 0)
	int a = 0;
	printf("a:%d\n", a);
#else
	char *s = "abcd";
	printf("s:%s\n", s);
#endif
	return 0;
}
