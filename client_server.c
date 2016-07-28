
/* client and server handleing function */

/* Client reads file path from stdandard input,
 * and pass it to the server process. Waiting for the 
 * server pass file content back to client.
 */
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "header.h"

int client(int pipe1[2], int pipe2[2])
{	
	char	    filePath[MAXLINE]; // file path
	char	    recvBuf[MAXLINE]; // receive buffer
	int	    ret;
	int	    pathLen;
	ssize_t     nBytes;

	close(pipe1[1]);
	close(pipe2[0]);
	if (!fgets(filePath, MAXLINE, stdin)) {
	    return -1; // error
	}
	pathLen = strlen(filePath);
	if (filePath[pathLen - 1] == '\n') { 
	    filePath[pathLen - 1] = '\0'; // delete the last character '\n'
	}
	ret = Write(pipe2[1], filePath, strlen(filePath) + 1); // pass file path to child process
	if (ret < 0) {
	    return -1; // error
	}
	/* why ??????????????????? */
	// close(pipe2[1]); // parent close write end when writing completes
	while (Read(pipe1[0], recvBuf, MAXLINE) > 0) { // read file content
	    fputs(recvBuf, stdout); // print the file
	}

	return 0;

}

int server(int pipe1[2], int pipe2[2])
{
	char        filePath[MAXLINE];
	char	    recvBuf[MAXLINE]; // receive buffer
	int	    fd;
	ssize_t	    nBytes;

	close(pipe1[0]);
	close(pipe2[1]);
	Read(pipe2[0], filePath, MAXLINE); // read file path from parent
	
	if ((fd = open(filePath, O_RDWR)) < 0) {
	    return -1; // error
	}

	while ((nBytes = read(fd, recvBuf, MAXLINE)) > 0) { // read file content, and pass it to the client.
	    Write(pipe1[1], recvBuf, nBytes);
	}
	close(pipe1[1]);

	return 0;
}

