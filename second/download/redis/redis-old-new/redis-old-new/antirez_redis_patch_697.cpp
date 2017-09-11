@@ -3404,15 +3404,27 @@ void redisAsciiArt(void) {
     else if (server.sentinel_mode) mode = "sentinel";
     else mode = "standalone";
 
-    snprintf(buf,1024*16,ascii_logo,
-        REDIS_VERSION,
-        redisGitSHA1(),
-        strtol(redisGitDirty(),NULL,10) > 0,
-        (sizeof(long) == 8) ? "64" : "32",
-        mode, server.port,
-        (long) getpid()
-    );
-    redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+    if (server.syslog_enabled) {
+        redisLog(REDIS_NOTICE,
+            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
+            REDIS_VERSION,
+            redisGitSHA1(),
+            strtol(redisGitDirty(),NULL,10) > 0,
+            (sizeof(long) == 8) ? "64" : "32",
+            mode, server.port,
+            (long) getpid()
+        );
+    } else {
+        snprintf(buf,1024*16,ascii_logo,
+            REDIS_VERSION,
+            redisGitSHA1(),
+            strtol(redisGitDirty(),NULL,10) > 0,
+            (sizeof(long) == 8) ? "64" : "32",
+            mode, server.port,
+            (long) getpid()
+        );
+        redisLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+    }
     zfree(buf);
 }
 