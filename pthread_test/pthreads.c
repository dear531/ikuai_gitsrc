#include <stdio.h>
#include <pthread.h>

int a = 0, b = 0;
int x = 0, y = 0;

void *func_a(void *n)
{
	a = 1;
	x = b;
	return NULL;
}

void *func_b(void *n)
{
	b = 1;
	y = a;
	return NULL;
}

int main(void)
{

#if 0
       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

#endif
	pthread_t thread = 0, thread_2 = 0;
       pthread_create(&thread , NULL,
                         func_a, NULL);
       pthread_create(&thread_2, NULL,
                         func_b, NULL);
	pthread_join(thread, NULL);
	pthread_join(thread_2, NULL);
	printf("x :%d, y:%d\n", x, y);
	return 0;
}
