@@ -1512,29 +1512,31 @@ void adjustOpenFilesLimit(void) {
          * for our needs. */
         if (oldlimit < maxfiles) {
             rlim_t f;
-            
+            int setrlimit_error = 0;
+
+            /* Try to set the file limit to match 'maxfiles' or at least
+             * to the higher value supported less than maxfiles. */
             f = maxfiles;
             while(f > oldlimit) {
+                int decr_step = 16;
+
                 limit.rlim_cur = f;
                 limit.rlim_max = f;
                 if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
-                f -= REDIS_MIN_RESERVED_FDS;
-                if (f > limit.rlim_cur) {
-                    /* Instead of getting smaller, f just got bigger.
-                     * That means it wrapped around its unsigned floor
-                     * and is now closer to 2^64.  We can't help anymore. */
-                    redisLog(REDIS_WARNING,"Failed to set max file limit. "
-                        "You requested maxclients of %d "
-                        "but your 'ulimit -n' is set to %llu. "
-                        "Please increase your 'ulimit -n' to at least %llu.",
-                        server.maxclients, oldlimit, maxfiles);
-                    exit(1);
-                }
+                setrlimit_error = errno;
+
+                /* We failed to set file limit to 'f'. Try with a
+                 * smaller limit decrementing by a few FDs per iteration. */
+                if (f < decr_step) break;
+                f -= decr_step;
             }
+
+            /* Assume that the limit we get initially is still valid if
+             * our last try was even lower. */
             if (f < oldlimit) f = oldlimit;
+
             if (f != maxfiles) {
                 int old_maxclients = server.maxclients;
-                int original_errno = errno;
                 server.maxclients = f-REDIS_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
                     redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
@@ -1548,7 +1550,7 @@ void adjustOpenFilesLimit(void) {
                     old_maxclients, maxfiles);
                 redisLog(REDIS_WARNING,"Redis can't set maximum open files "
                     "to %llu because of OS error: %s.",
-                    maxfiles, strerror(original_errno));
+                    maxfiles, strerror(setrlimit_error));
                 redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
                     "maxclients has been reduced to %d to compensate for "
                     "low ulimit. "