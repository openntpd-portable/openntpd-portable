--- client.orig	2014-12-28 11:10:23.875157132 -0600
+++ client.c	2014-12-28 11:12:46.095160215 -0600
@@ -142,10 +142,12 @@
 		    0)) == -1)
 			fatal("client_query socket");
 
+#ifdef SO_RTABLE
 		if (p->rtable != -1 &&
 		    setsockopt(p->query->fd, SOL_SOCKET, SO_RTABLE,
 		    &p->rtable, sizeof(p->rtable)) == -1)
 			fatal("client_query setsockopt SO_RTABLE");
+#endif
 		if (connect(p->query->fd, sa, SA_LEN(sa)) == -1) {
 			if (errno == ECONNREFUSED || errno == ENETUNREACH ||
 			    errno == EHOSTUNREACH || errno == EADDRNOTAVAIL) {
@@ -248,10 +250,12 @@
 		return (0);
 	}
 
+#ifdef SO_RTABLE
 	if (p->rtable != -1 &&
 	    setsockopt(p->query->fd, SOL_SOCKET, SO_RTABLE, &p->rtable,
 	    sizeof(p->rtable)) == -1)
 		fatal("client_dispatch setsockopt SO_RTABLE");
+#endif
 
 	for (cmsg = CMSG_FIRSTHDR(&somsg); cmsg != NULL;
 	    cmsg = CMSG_NXTHDR(&somsg, cmsg)) {
