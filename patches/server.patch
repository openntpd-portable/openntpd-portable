--- server.orig	2014-12-28 12:16:48.203243490 -0600
+++ server.c	2014-12-28 12:18:07.907245217 -0600
@@ -39,7 +39,10 @@
 	u_int8_t		*a6;
 	size_t			 sa6len = sizeof(struct in6_addr);
 	u_int			 new_cnt = 0;
-	int			 tos = IPTOS_LOWDELAY, rdomain, fd;
+	int			 tos = IPTOS_LOWDELAY;
+#ifdef SO_RTABLE
+	int 		 rdomain, fd;
+#endif
 
 	TAILQ_FOREACH(lap, &lconf->listen_addrs, entry) {
 		switch (lap->sa.ss_family) {
@@ -59,6 +62,7 @@
 				strlcpy(ifr.ifr_name, ifap->ifa_name,
 				    sizeof(ifr.ifr_name));
 
+#ifdef SO_RTABLE
 				fd = socket(AF_INET, SOCK_DGRAM, 0);
 				if (ioctl(fd, SIOCGIFRDOMAIN,
 				    (caddr_t)&ifr) == -1)
@@ -69,6 +73,7 @@
 
 				if (lap->rtable != -1 && rdomain != lap->rtable)
 					continue;
+#endif
 
 				if (sa->sa_family == AF_INET &&
 				    ((struct sockaddr_in *)sa)->sin_addr.s_addr ==
@@ -87,7 +92,9 @@
 					fatal("setup_listeners calloc");
 
 				memcpy(&la->sa, sa, SA_LEN(sa));
+#ifdef SO_RTABLE
 				la->rtable = rdomain;
+#endif
 
 				TAILQ_INSERT_TAIL(&lconf->listen_addrs, la, entry);
 			}
@@ -132,10 +139,12 @@
 		    IPPROTO_IP, IP_TOS, &tos, sizeof(tos)) == -1)
 			log_warn("setsockopt IPTOS_LOWDELAY");
 
+#ifdef SO_RTABLE
 		if (la->rtable != -1 &&
 		    setsockopt(la->fd, SOL_SOCKET, SO_RTABLE, &la->rtable,
 		    sizeof(la->rtable)) == -1)
 			fatal("setup_listeners setsockopt SO_RTABLE");
+#endif
 
 		if (bind(la->fd, (struct sockaddr *)&la->sa,
 		    SA_LEN((struct sockaddr *)&la->sa)) == -1) {
