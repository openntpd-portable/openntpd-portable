--- ntpd.orig	2014-12-28 11:51:56.363211155 -0600
+++ ntpd.c	2014-12-28 11:52:00.971211255 -0600
@@ -30,6 +30,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <time.h>
 #include <unistd.h>
 #include <err.h>
 
