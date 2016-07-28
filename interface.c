
/* 1. sig_chld
 * 2. Read
 * 3. Write
 */  

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include "header.h"

void sigChld(int signum)
{
	int	stat;
	pid_t	pid;

	while ((pid=waitpid(-1, &stat, WNOHANG)) > 0) {
	    if (WIFEXITED(stat)) {
		printf("child process exits normal\n");
	    } else if (WIFSIGNALED(stat)) {
		printf("child process exits by a siganl\n");
	    }
	}
}

int Open(const char *pathname, int flags)
{
    int	    ret;

    ret = open(pathname, flags);

    return ret;
}

/* Read file referenced by fd.
 * If it is interrupted by signal, return error.
 */
ssize_t Read(int fd, void *buf, size_t count)
{
    ssize_t	nBytes;

    nBytes = read(fd, buf, count);
    
    return nBytes;
}

/* write count bytes in the file referenced by fd.
 * If it is interrupted by signal, continue.
 */
ssize_t Write(int fd, const void *buf, size_t count)
{
	const char *pstr;
	int	    n;
	size_t	    left;

	pstr = buf;
	left = count;
	while (left > 0) {
		n = write(fd, pstr, count);
		if (n<0 && errno==EINTR) {
			n = 0;
		} else if (n < 0) { // error
			return -1;
		}
		left = count-n;
		pstr = pstr+n;
	}

	return count;
}

