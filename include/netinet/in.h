/*
 * Public domain
 * netinet/in.h compatibility shim
 */

#include_next <netinet/in.h>

#ifndef SA_LEN
static inline socklen_t sockaddr_len(void *a)
{
	struct sockaddr *sa = a;
	switch (sa->sa_family) {
	case AF_INET:
		return sizeof(struct sockaddr_in);
	case AF_INET6:
		return sizeof(struct sockaddr_in6);
	case AF_UNSPEC:
		return sizeof(struct sockaddr);
	default:
		return 0;
	}
}
#define SA_LEN(X) sockaddr_len(X)
#endif
