
/* register signal handler */

#include <signal.h>

#include "header.h"

int signalHandler(int signum, struct sigaction *act)
{

    act->sa_handler = sigChld;
    sigemptyset(&act->sa_mask);
    act->sa_flags = 0;

    sigaction(signum, act, NULL);
}
