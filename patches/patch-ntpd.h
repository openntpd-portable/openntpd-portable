--- ntpd.orig	Sun Dec 28 16:11:35 2014
+++ ntpd.h	Sun Dec 28 16:12:14 2014
@@ -28,7 +28,6 @@
 #include <netdb.h>
 #include <pwd.h>
 #include <stdarg.h>
-#include <event.h>
 #include <poll.h>
 
 #include "ntp.h"
@@ -190,14 +189,6 @@
 	u_int8_t					filters;
 };
 
-struct imsgev {
-	struct imsgbuf		 ibuf;
-	void			(*handler)(int, short, void *);
-	struct event		 ev;
-	void			*data;
-	short			 events;
-};
-
 struct ctl_show_status {
 	u_int		 peercnt;
 	u_int		 sensorcnt;
@@ -240,7 +231,6 @@
 
 struct ctl_conn {
 	TAILQ_ENTRY(ctl_conn)	entry;
-	struct imsgev		iev;
 	struct imsgbuf		ibuf;
 };
 
