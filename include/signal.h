/*
 * Public domain
 * signal.h compatibility shim
 */

#include_next <signal.h>

#ifndef SIGINFO
#define SIGINFO SIGUSR1
#endif
