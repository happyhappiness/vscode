@@ -1673,7 +1673,16 @@ static void initServer() {
         acceptHandler, NULL) == AE_ERR) oom("creating file event");
 
     if (server.appendonly) {
-        server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+        int flags = O_WRONLY|O_APPEND|O_CREAT;
+
+#ifdef HAVE_O_DIRECT
+        if (server.appendfsync == APPENDFSYNC_ALWAYS) {
+            flags |= O_DIRECT;
+            server.appendfsync = APPENDFSYNC_NO;
+        }
+#endif
+
+        server.appendfd = open(server.appendfilename,flags,0644);
         if (server.appendfd == -1) {
             redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));