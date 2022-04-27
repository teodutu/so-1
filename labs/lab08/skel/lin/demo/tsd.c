#include <stdio.h>
#include <pthread.h>

pthread_key_t key;

static void foo(void)
{
	printf("thread_func: arg = %s\n", (char *)pthread_getspecific(key));
}

static void *thread_func(void *arg)
{
	pthread_key_create(&key, NULL);
	pthread_setspecific(key, arg);

	foo();

	return NULL;
}

void main(void)
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_func, "thread-1");
	pthread_create(&tid2, NULL, thread_func, "thread-2");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
}
