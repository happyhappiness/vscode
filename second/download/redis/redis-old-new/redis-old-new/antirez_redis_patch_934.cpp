@@ -1534,6 +1534,7 @@ void adjustOpenFilesLimit(void) {
             if (f < oldlimit) f = oldlimit;
             if (f != maxfiles) {
                 int old_maxclients = server.maxclients;
+                int original_errno = errno;
                 server.maxclients = f-REDIS_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
                     redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
@@ -1547,7 +1548,7 @@ void adjustOpenFilesLimit(void) {
                     old_maxclients, maxfiles);
                 redisLog(REDIS_WARNING,"Redis can't set maximum open files "
                     "to %llu because of OS error: %s.",
-                    maxfiles, strerror(errno));
+                    maxfiles, strerror(original_errno));
                 redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
                     "maxclients has been reduced to %d to compensate for "
                     "low ulimit. "