/**
 * SO
 * Lab #3
 *
 * Demo
 *
 * Create an `ls -la` process using `posix_spawn`.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#include "utils.h"

extern char **environ;

int main(void)
{
	pid_t pid;
	char *argv[] = {"-la", NULL};
	int status;
	int rc;

	/* Spawn a new process that runs `ls -a`. */
	rc = posix_spawn(&pid, "/bin/ls", NULL, NULL, argv, environ);
	DIE(rc, "posix_spawn");

	printf("[parent] PID = %d; child PID = %d; Waiting...\n", getpid(),
		pid);
	
	rc = waitpid(pid, &status, 0);
	DIE(rc < 0, "waitpid");

	return 0;
}
