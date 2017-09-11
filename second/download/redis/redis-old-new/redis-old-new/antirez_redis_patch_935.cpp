@@ -1491,20 +1491,20 @@ void initServerConfig() {
 
 /* This function will try to raise the max number of open files accordingly to
  * the configured max number of clients. It also reserves a number of file
- * descriptors (REDIS_EVENTLOOP_FDSET_INCR) for extra operations of
+ * descriptors (REDIS_MIN_RESERVED_FDS) for extra operations of
  * persistence, listening sockets, log files and so forth.
  *
  * If it will not be possible to set the limit accordingly to the configured
  * max number of clients, the function will do the reverse setting
  * server.maxclients to the value that we can actually handle. */
 void adjustOpenFilesLimit(void) {
-    rlim_t maxfiles = server.maxclients+REDIS_EVENTLOOP_FDSET_INCR;
+    rlim_t maxfiles = server.maxclients+REDIS_MIN_RESERVED_FDS;
     struct rlimit limit;
 
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
         redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));
-        server.maxclients = 1024-REDIS_EVENTLOOP_FDSET_INCR;
+        server.maxclients = 1024-REDIS_MIN_RESERVED_FDS;
     } else {
         rlim_t oldlimit = limit.rlim_cur;
 
@@ -1518,7 +1518,7 @@ void adjustOpenFilesLimit(void) {
                 limit.rlim_cur = f;
                 limit.rlim_max = f;
                 if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
-                f -= REDIS_EVENTLOOP_FDSET_INCR;
+                f -= REDIS_MIN_RESERVED_FDS;
                 if (f > limit.rlim_cur) {
                     /* Instead of getting smaller, f just got bigger.
                      * That means it wrapped around its unsigned floor
@@ -1534,7 +1534,7 @@ void adjustOpenFilesLimit(void) {
             if (f < oldlimit) f = oldlimit;
             if (f != maxfiles) {
                 int old_maxclients = server.maxclients;
-                server.maxclients = f-REDIS_EVENTLOOP_FDSET_INCR;
+                server.maxclients = f-REDIS_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
                     redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for Redis to start. "