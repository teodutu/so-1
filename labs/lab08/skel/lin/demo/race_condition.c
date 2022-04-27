#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_STEPS	10000000
#define NUM_THREADS	2

#ifdef USE_SPINLOCK
static pthread_spinlock_t lock;
#elif USE_MUTEX
static pthread_mutex_t lock;
#endif

static unsigned long get_current_millis(void)
{
	struct timeval tv;
	int rc = gettimeofday(&tv, NULL);

	return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

static void init_lock(void)
{
#ifdef USE_SPINLOCK
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
#elif USE_MUTEX
	pthread_mutex_init(&lock, NULL);
#endif
}

static void destroy_lock(void)
{
#ifdef USE_SPINLOCK
	pthread_spin_destroy(&lock);
#elif USE_MUTEX
	pthread_mutex_destroy(&lock);
#endif
}

static void acquire_lock(void)
{
#ifdef USE_SPINLOCK
	pthread_spin_lock(&lock);
#elif USE_MUTEX
	pthread_mutex_lock(&lock);
#endif
}

static void release_lock(void)
{
#ifdef USE_SPINLOCK
	pthread_spin_unlock(&lock);
#elif USE_MUTEX
	pthread_mutex_unlock(&lock);
#endif
}

static int var;

static void *increase_var(void *arg)
{
	size_t i;

	for (i = 0; i < NUM_STEPS; ++i) {
		acquire_lock();	/* Begin critical section. */
		++var;
		release_lock();	/* End critical section. */
	}

	return  NULL;
}

int main(void)
{
	size_t i;
	pthread_t tids[NUM_THREADS];
	unsigned long millis_start;
	unsigned long millis_end;

	init_lock();

	millis_start = get_current_millis();

	for (i = 0; i < NUM_THREADS; ++i)
		pthread_create(tids + i, NULL, increase_var, NULL);

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

	millis_end = get_current_millis();

	printf("var = %d; time = %lu ms\n", var, millis_end - millis_start);

	return 0;
}
