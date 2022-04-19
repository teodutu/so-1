/**
 * SO
 * Lab IPC
 *
 * Task #2, Windows
 *
 * Win implementation of semaphore functions
 */
#include "generic_sem.h"
#include "utils.h"

/**
 * Create a semaphore with an initial value
 */
sema_t sema_create(const char *name, int initial)
{
	sema_t sem = INVALID_HANDLE_VALUE;
	char sema_name[255];

	/* Init semaphore name */
	strcpy(sema_name, "Global\\");
	strcat(sema_name, name);

	/* TODO 3 - Create semaphore with initial value 'initial' */

	return sem;
}

/**
 * Open a semaphore
 */
sema_t sema_get(const char *name)
{
	sema_t sem = INVALID_HANDLE_VALUE;
	char sema_name[255];

	/* Init semaphore name */
	strcpy(sema_name, "Global\\");
	strcat(sema_name, name);

	/* TODO 3 - Open existing named semaphore */

	return sem;
}

/**
 * Detach(close) a semaphore - called from client
 */
void sema_detach(sema_t x)
{
	/**
	 * TODO 4 - close the semaphore
	 *
	 * Hint: what is sema_t? check common.h
	 */

}

/**
 * Destroy an existing semaphore - called from server only
 */
void sema_destroy(sema_t x)
{
	/* TODO 4 - delete the semaphore*/
}

/**
 * Decrement (and wait on) a semaphore
 */
void sema_wait(sema_t s)
{
	DWORD dwRet;

	/* TODO 4 - wait indefinitely to get the semaphore */

}

/**
 * Increment (and release) a semaphore
 */
void sema_signal(sema_t s)
{
	BOOL bRet;

	/* TODO 4 */

}
