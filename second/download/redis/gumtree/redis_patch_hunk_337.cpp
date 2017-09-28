                 ri->runid ? " " : "",
                 ri->runid ? ri->runid : "");
             rewriteConfigRewriteLine(state,"sentinel",line,1);
         }
         dictReleaseIterator(di2);
     }
+
+    /* sentinel current-epoch is a global state valid for all the masters. */
+    line = sdscatprintf(sdsempty(),
+        "sentinel current-epoch %llu", (unsigned long long) sentinel.current_epoch);
+    rewriteConfigRewriteLine(state,"sentinel",line,1);
+
     dictReleaseIterator(di);
 }
 
 /* This function uses the config rewriting Redis engine in order to persist
  * the state of the Sentinel in the current configuration file.
  *
  * Before returning the function calls fsync() against the generated
  * configuration file to make sure changes are committed to disk.
  *
  * On failure the function logs a warning on the Redis log. */
 void sentinelFlushConfig(void) {
-    int fd;
+    int fd = -1;
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
-        redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
-    }
+    rewrite_status = rewriteConfig(server.configfile);
     server.hz = saved_hz;
+
+    if (rewrite_status == -1) goto werr;
+    if ((fd = open(server.configfile,O_RDONLY)) == -1) goto werr;
+    if (fsync(fd) == -1) goto werr;
+    if (close(fd) == EOF) goto werr;
     return;
+
+werr:
+    if (fd != -1) close(fd);
+    redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
 }
 
 /* ====================== hiredis connection handling ======================= */
 
 /* Completely disconnect a hiredis link from an instance. */
 void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c) {
