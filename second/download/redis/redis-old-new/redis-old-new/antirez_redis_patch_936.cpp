@@ -1522,12 +1522,30 @@ void adjustOpenFilesLimit(void) {
             }
             if (f < oldlimit) f = oldlimit;
             if (f != maxfiles) {
+                int old_maxclients = server.maxclients;
                 server.maxclients = f-REDIS_EVENTLOOP_FDSET_INCR;
-                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
-                    (int) maxfiles, strerror(errno), (int) server.maxclients);
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
+                    maxfiles, strerror(errno));
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