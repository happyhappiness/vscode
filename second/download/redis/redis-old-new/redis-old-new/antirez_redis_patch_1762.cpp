@@ -298,7 +298,7 @@ void dsFlushOneDir(char *path, int dbid) {
             id[len] = '\0';
             if (atoi(id) != dbid) continue; /* skip this file */
         }
-        if (unlink(path) == -1) {
+        if (unlink(dp->d_name) == -1) {
             redisLog(REDIS_WARNING,
                 "Can't unlink %s: %s", path, strerror(errno));
             redisPanic("Unrecoverable Disk store errore. Existing.");