@@ -1490,21 +1490,21 @@ void initServerConfig() {
 }
 
 /* This function will try to raise the max number of open files accordingly to
- * the configured max number of clients. It will also account for 32 additional
- * file descriptors as we need a few more for persistence, listening
- * sockets, log files and so forth.
+ * the configured max number of clients. It also reserves a number of file
+ * descriptors (REDIS_MIN_RESERVED_FDS) for extra operations of
+ * persistence, listening sockets, log files and so forth.
  *
  * If it will not be possible to set the limit accordingly to the configured
  * max number of clients, the function will do the reverse setting
  * server.maxclients to the value that we can actually handle. */
 void adjustOpenFilesLimit(void) {
-    rlim_t maxfiles = server.maxclients+32;
+    rlim_t maxfiles = server.maxclients+REDIS_MIN_RESERVED_FDS;
     struct rlimit limit;
 
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
         redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));
-        server.maxclients = 1024-32;
+        server.maxclients = 1024-REDIS_MIN_RESERVED_FDS;
     } else {
         rlim_t oldlimit = limit.rlim_cur;
 
@@ -1518,16 +1518,46 @@ void adjustOpenFilesLimit(void) {
                 limit.rlim_cur = f;
                 limit.rlim_max = f;
                 if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
-                f -= 128;
+                f -= REDIS_MIN_RESERVED_FDS;
+                if (f > limit.rlim_cur) {
+                    /* Instead of getting smaller, f just got bigger.
+                     * That means it wrapped around its unsigned floor
+                     * and is now closer to 2^64.  We can't help anymore. */
+                    redisLog(REDIS_WARNING,"Failed to set max file limit. "
+                        "You requested maxclients of %d "
+                        "but your 'ulimit -n' is set to %llu. "
+                        "Please increase your 'ulimit -n' to at least %llu.",
+                        server.maxclients, oldlimit, maxfiles);
+                    exit(1);
+                }
             }
             if (f < oldlimit) f = oldlimit;
             if (f != maxfiles) {
-                server.maxclients = f-32;
-                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
-                    (int) maxfiles, strerror(errno), (int) server.maxclients);
+                int old_maxclients = server.maxclients;
+                int original_errno = errno;
+                server.maxclients = f-REDIS_MIN_RESERVED_FDS;
+                if (server.maxclients < 1) {
+                    redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
+                        "of %llu is not enough for Redis to start. "
+                        "Please increase your open file limit to at least "
+                        "%llu. Exiting.", oldlimit, maxfiles);
+                    exit(1);
+                }
+                redisLog(REDIS_WARNING,"You requested maxclients of %d "
+                    "requiring at least %llu max file descriptors.",
+                    old_maxclients, maxfiles);
+                redisLog(REDIS_WARNING,"Redis can't set maximum open files "
+                    "to %llu because of OS error: %s.",
+                    maxfiles, strerror(original_errno));
+                redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
+                    "maxclients has been reduced to %d to compensate for "
+                    "low ulimit. "
+                    "If you need higher maxclients increase 'ulimit -n'.",
+                    oldlimit, server.maxclients);
             } else {
-                redisLog(REDIS_NOTICE,"Max number of open files set to %d",
-                    (int) maxfiles);
+                redisLog(REDIS_NOTICE,"Increased maximum number of open files "
+                    "to %llu (it was originally set to %llu).",
+                    maxfiles, oldlimit);
             }
         }
     }