@@ -1490,21 +1490,21 @@ void initServerConfig() {
 }
 
 /* This function will try to raise the max number of open files accordingly to
- * the configured max number of clients. It will also account for 32 additional
- * file descriptors as we need a few more for persistence, listening
- * sockets, log files and so forth.
+ * the configured max number of clients. It also reserves a number of file
+ * descriptors (REDIS_EVENTLOOP_FDSET_INCR) for extra operations of
+ * persistence, listening sockets, log files and so forth.
  *
  * If it will not be possible to set the limit accordingly to the configured
  * max number of clients, the function will do the reverse setting
  * server.maxclients to the value that we can actually handle. */
 void adjustOpenFilesLimit(void) {
-    rlim_t maxfiles = server.maxclients+32;
+    rlim_t maxfiles = server.maxclients+REDIS_EVENTLOOP_FDSET_INCR;
     struct rlimit limit;
 
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
         redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));
-        server.maxclients = 1024-32;
+        server.maxclients = 1024-REDIS_EVENTLOOP_FDSET_INCR;
     } else {
         rlim_t oldlimit = limit.rlim_cur;
 
@@ -1518,11 +1518,11 @@ void adjustOpenFilesLimit(void) {
                 limit.rlim_cur = f;
                 limit.rlim_max = f;
                 if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
-                f -= 128;
+                f -= REDIS_EVENTLOOP_FDSET_INCR;
             }
             if (f < oldlimit) f = oldlimit;
             if (f != maxfiles) {
-                server.maxclients = f-32;
+                server.maxclients = f-REDIS_EVENTLOOP_FDSET_INCR;
                 redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
                     (int) maxfiles, strerror(errno), (int) server.maxclients);
             } else {