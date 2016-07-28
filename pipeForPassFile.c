
/* using pipe 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "header.h"

int main(void)
{
    int	    ret;
    int	    pipe1[2];
    int	    pipe2[2];
    pid_t   pid;

    if (pipe(pipe1) < 0) {
	exit(-1);
    }
    if (pipe(pipe2) < 0) {
	exit(-1);
    }
    pid = fork();

    if (pid < 0) { // error, process exits.
	exit(-1);
    } else if (pid == 0) { // child, server
	server(pipe1, pipe2);

	return 0; // exit
    }
   
    int			stat; 
    struct sigaction	act;

    /* parent, client */
    client(pipe1, pipe2);

    signalHandler(SIGCHLD, &act); // wait child process to terminate

    return 0;
}
