--- imsg.orig	2014-12-28 13:24:02.771330936 -0600
+++ imsg.c	2014-12-28 13:24:35.347331642 -0600
@@ -70,6 +70,7 @@
 		return (-1);
 
 again:
+#ifdef HAVE_GETDTABLECOUNT
 	if (getdtablecount() + imsg_fd_overhead +
 	    (CMSG_SPACE(sizeof(int))-CMSG_SPACE(0))/sizeof(int)
 	    >= getdtablesize()) {
@@ -77,7 +78,8 @@
 		free(ifd);
 		return (-1);
 	}
-	
+#endif
+
 	if ((n = recvmsg(ibuf->fd, &msg, 0)) == -1) {
 		if (errno == EMSGSIZE)
 			goto fail;
