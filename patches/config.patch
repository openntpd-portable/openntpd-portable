--- config.orig	Sun Dec 28 20:17:46 2014
+++ config.c	Sun Dec 28 20:19:48 2014
@@ -75,7 +75,9 @@
 	if ((h = calloc(1, sizeof(struct ntp_addr))) == NULL)
 		fatal(NULL);
 	sa_in = (struct sockaddr_in *)&h->ss;
+#ifdef SIN_LEN
 	sa_in->sin_len = sizeof(struct sockaddr_in);
+#endif
 	sa_in->sin_family = AF_INET;
 	sa_in->sin_addr.s_addr = ina.s_addr;
 
@@ -97,7 +99,9 @@
 		if ((h = calloc(1, sizeof(struct ntp_addr))) == NULL)
 			fatal(NULL);
 		sa_in6 = (struct sockaddr_in6 *)&h->ss;
+#ifdef SIN6_LEN
 		sa_in6->sin6_len = sizeof(struct sockaddr_in6);
+#endif
 		sa_in6->sin6_family = AF_INET6;
 		memcpy(&sa_in6->sin6_addr,
 		    &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr,
@@ -124,8 +128,14 @@
 	hints.ai_family = PF_UNSPEC;
 	hints.ai_socktype = SOCK_DGRAM; /* DUMMY */
 	error = getaddrinfo(s, NULL, &hints, &res0);
-	if (error == EAI_AGAIN || error == EAI_NODATA || error == EAI_NONAME)
-			return (0);
+	switch (error) {
+	case EAI_AGAIN:
+#ifdef EAI_NODATA
+	case EAI_NODATA:
+#endif
+	case EAI_NONAME:
+		return (0);
+	}
 	if (error) {
 		log_warnx("could not parse \"%s\": %s", s,
 		    gai_strerror(error));
@@ -141,12 +151,16 @@
 		h->ss.ss_family = res->ai_family;
 		if (res->ai_family == AF_INET) {
 			sa_in = (struct sockaddr_in *)&h->ss;
+#ifdef SIN_LEN
 			sa_in->sin_len = sizeof(struct sockaddr_in);
+#endif
 			sa_in->sin_addr.s_addr = ((struct sockaddr_in *)
 			    res->ai_addr)->sin_addr.s_addr;
 		} else {
 			sa_in6 = (struct sockaddr_in6 *)&h->ss;
+#ifdef SIN6_LEN
 			sa_in6->sin6_len = sizeof(struct sockaddr_in6);
+#endif
 			memcpy(&sa_in6->sin6_addr, &((struct sockaddr_in6 *)
 			    res->ai_addr)->sin6_addr, sizeof(struct in6_addr));
 		}
