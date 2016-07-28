
/* header file */

#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <signal.h>

#define MAXLINE 4096

/* interface.c */
void sigChld(int signum);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Write(int fd, const void *buf, size_t count);

/* client-server.c */
int client(int pipe1[2], int pipe2[2]);
int server(int pipe1[2], int pipe2[2]);

/* signalHandler.c */
int signalHandler(int signum, struct sigaction *act);

#endif
