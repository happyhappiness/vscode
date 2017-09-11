@@ -1472,15 +1472,19 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
  * On failure the function logs a warning on the Redis log. */
 void sentinelFlushConfig(void) {
     int fd;
-
-    if (rewriteConfig(server.configfile) == -1) {
+    int saved_hz = server.hz;
+
+    server.hz = REDIS_DEFAULT_HZ;
+    if (rewriteConfig(server.configfile) != -1) {
+        /* Rewrite succeded, fsync it. */
+        if ((fd = open(server.configfile,O_RDONLY)) != -1) {
+            fsync(fd);
+            close(fd);
+        }
+    } else {
         redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
-        return;
-    }
-    if ((fd = open(server.configfile,O_RDONLY)) != -1) {
-        fsync(fd);
-        close(fd);
     }
+    server.hz = saved_hz;
     return;
 }
 