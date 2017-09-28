     char *mode;
 
     if (server.cluster_enabled) mode = "cluster";
     else if (server.sentinel_mode) mode = "sentinel";
     else mode = "standalone";
 
-    if (server.syslog_enabled) {
+    /* Show the ASCII logo if: log file is stdout AND stdout is a
+     * tty AND syslog logging is disabled. Also show logo if the user
+     * forced us to do so via redis.conf. */
+    int show_logo = ((!server.syslog_enabled &&
+                      server.logfile[0] == '\0' &&
+                      isatty(fileno(stdout))) ||
+                     server.always_show_logo);
+
+    if (!show_logo) {
         serverLog(LL_NOTICE,
-            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
-            REDIS_VERSION,
-            redisGitSHA1(),
-            strtol(redisGitDirty(),NULL,10) > 0,
-            (sizeof(long) == 8) ? "64" : "32",
-            mode, server.port,
-            (long) getpid()
+            "Running mode=%s, port=%d.",
+            mode, server.port
         );
     } else {
         snprintf(buf,1024*16,ascii_logo,
             REDIS_VERSION,
             redisGitSHA1(),
             strtol(redisGitDirty(),NULL,10) > 0,
