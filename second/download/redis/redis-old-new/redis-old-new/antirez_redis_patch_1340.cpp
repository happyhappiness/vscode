@@ -803,9 +803,9 @@ int rewriteAppendOnlyFileBackground(void) {
         if (server.sofd > 0) close(server.sofd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
-            _exit(0);
+            exitFromChild(0);
         } else {
-            _exit(1);
+            exitFromChild(1);
         }
     } else {
         /* Parent */