@@ -36,6 +36,7 @@
 #include <arpa/inet.h>
 #include <sys/socket.h>
 #include <sys/wait.h>
+#include <fcntl.h>
 
 extern char **environ;
 
@@ -1432,6 +1433,27 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
     dictReleaseIterator(di);
 }
 
+/* This function uses the config rewriting Redis engine in order to persist
+ * the state of the Sentinel in the current configuration file.
+ *
+ * Before returning the function calls fsync() against the generated
+ * configuration file to make sure changes are committed to disk.
+ *
+ * On failure the function logs a warning on the Redis log. */
+void sentinelFlushConfig(void) {
+    int fd;
+
+    if (rewriteConfig(server.configfile) == -1) {
+        redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+        return;
+    }
+    if ((fd = open(server.configfile,O_RDONLY)) != -1) {
+        fsync(fd);
+        close(fd);
+    }
+    return;
+}
+
 /* ====================== hiredis connection handling ======================= */
 
 /* Completely disconnect an hiredis link from an instance. */