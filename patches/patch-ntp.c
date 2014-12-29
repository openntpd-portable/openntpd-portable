--- ntp.orig	2014-12-28 11:48:24.731206568 -0600
+++ ntp.c	2014-12-28 11:49:42.107208245 -0600
@@ -79,7 +79,7 @@
 	u_int			 pfd_elms = 0, idx2peer_elms = 0;
 	u_int			 listener_cnt, new_cnt, sent_cnt, trial_cnt;
 	u_int			 ctl_cnt;
-	pid_t			 pid, dns_pid;
+	pid_t			 pid;
 	struct pollfd		*pfd = NULL;
 	struct servent		*se;
 	struct listen_addr	*la;
@@ -118,7 +118,7 @@
 	close(pipe_prnt[0]);
 	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_dns) == -1)
 		fatal("socketpair");
-	dns_pid = ntp_dns(pipe_dns, nconf, pw);
+	ntp_dns(pipe_dns, nconf, pw);
 	close(pipe_dns[1]);
 
 	if (stat(pw->pw_dir, &stb) == -1)
