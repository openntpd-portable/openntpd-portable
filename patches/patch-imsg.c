--- imsg.c.orig	2015-07-17 23:57:48.000000000 +0000
+++ imsg.c	2015-07-17 23:58:57.000000000 +0000
@@ -71,6 +71,7 @@
 		return (-1);
 
 again:
+#ifdef HAVE_GETDTABLECOUNT
 	if (getdtablecount() + imsg_fd_overhead +
 	    (CMSG_SPACE(sizeof(int))-CMSG_SPACE(0))/sizeof(int)
 	    >= getdtablesize()) {
@@ -78,6 +79,7 @@
 		free(ifd);
 		return (-1);
 	}
+#endif
 
 	if ((n = recvmsg(ibuf->fd, &msg, 0)) == -1) {
 		if (errno == EMSGSIZE)
