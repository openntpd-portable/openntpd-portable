/*
 * Public domain
 * sys/socket.h compatibility shim
 */

#include_next <sys/socket.h>

#ifndef SA_LEN
#define SA_LEN(X) \
	(((struct sockaddr*)(X))->sa_family == AF_INET ? sizeof(struct sockaddr_in) : \
	 ((struct sockaddr*)(X))->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr))
#endif
