@@ -1562,19 +1562,22 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
 void sentinelFlushConfig(void) {
     int fd;
     int saved_hz = server.hz;
+    int rewrite_status;
 
     server.hz = REDIS_DEFAULT_HZ;
-    if (rewriteConfig(server.configfile) != -1) {
-        /* Rewrite succeded, fsync it. */
-        if ((fd = open(server.configfile,O_RDONLY)) != -1) {
-            fsync(fd);
-            close(fd);
-        }
-    } else {
-        redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
-    }
+    rewrite_status = rewriteConfig(server.configfile);
     server.hz = saved_hz;
+
+    if (rewrite_status == -1) goto werr;
+    if ((fd = open(server.configfile,O_RDONLY)) == -1) goto werr;
+    if (fsync(fd) == -1) goto werr;
+    if (close(fd) == EOF) goto werr;
+
     return;
+
+werr:
+    if (fd != -1) close(fd);
+    redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
 }
 
 /* ====================== hiredis connection handling ======================= */