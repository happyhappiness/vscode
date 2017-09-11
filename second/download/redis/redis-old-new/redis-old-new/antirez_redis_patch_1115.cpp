@@ -962,8 +962,7 @@ int rewriteAppendOnlyFileBackground(void) {
         char tmpfile[256];
 
         /* Child */
-        if (server.ipfd > 0) close(server.ipfd);
-        if (server.sofd > 0) close(server.sofd);
+        closeListeningSockets(0);
         redisSetProcTitle("redis-aof-rewrite");
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {