@@ -549,7 +549,8 @@ int rewriteAppendOnlyFileBackground(void) {
         char tmpfile[256];
 
         if (server.vm_enabled) vmReopenSwapFile();
-        close(server.fd);
+        if (server.ipfd > 0) close(server.ipfd);
+        if (server.sofd > 0) close(server.sofd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
         if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
             _exit(0);