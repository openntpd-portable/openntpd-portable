--- parse.orig	2014-12-28 11:59:42.075221249 -0600
+++ parse.y	2014-12-28 11:54:22.799214329 -0600
@@ -313,10 +313,12 @@
 			opts.weight = $2;
 		}
 rtable		: RTABLE NUMBER {
+#ifdef RT_TABLEID_MAX
 			if ($2 < 0 || $2 > RT_TABLEID_MAX) {
 				yyerror("rtable must be between 1 and RT_TABLEID_MAX");
 				YYERROR;
 			}
+#endif
 			opts.rtable = $2;
 		}
 		;
