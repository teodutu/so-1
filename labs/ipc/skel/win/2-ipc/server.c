/**
 * SO
 * Lab IPC
 *
 * Task #2, Windows
 *
 * Generic server implementation
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "common.h"
#include "generic_queue.h"
#include "generic_shm.h"
#include "generic_sem.h"
#include "hashtable.h"

static sema_t sems[BUCKET_COUNT];
static shm_t shmem;
static msgq_t queue;
static struct htable *h;

int main(void)
{
	int i;
	char name[MAX_IPC_NAME];
	message_t msg;

	/* Create semaphores */
	for (i = 0; i < BUCKET_COUNT; i++) {
		snprintf(name, MAX_IPC_NAME, "%s%d", BASE_SEMA_NAME, i);
		sems[i] = sema_create(name, 1);
	}

	/* Create message queue */
	queue = msgq_create(BASE_QUEUE_NAME);

	/* Create shared memory */
	shmem = shmem_create(BASE_SHM_NAME, sizeof(*h));
	h = shmem_attach(shmem, sizeof(*h));

	/* No need for locking here */
	htable_clear(h, NULL);

	/* Satisfy client requests */
	for (;;) {
		memset(&msg, 0, sizeof(msg));

		/* Receive message from client */
		msgq_recv(queue, &msg);

		if (msg.cmd == 'e')
			break;

		switch (msg.cmd) {
		case 'a':
			htable_insert(h, msg.val);
			break;

		case 'r':
			htable_delete(h, msg.val);
			break;

		case 'c':
			htable_clear(h, sems);
			break;
		}
	}

	/* Close shared memory */
	shmem_detach(h, sizeof(*h));
	shmem_destroy(shmem);

	/* Close queue */
	msgq_destroy(queue);

	/* Close semaphores */
	for (i = 0; i < BUCKET_COUNT; i++)
		sema_destroy(sems[i]);

	return EXIT_FAILURE;
}
