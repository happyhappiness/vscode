@@ -563,7 +563,7 @@ void incrementallyRehash(void) {
  * for dict.c to resize the hash tables accordingly to the fact we have o not
  * running childs. */
 void updateDictResizePolicy(void) {
-    if (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1)
+    if (server.bgsavechildpid == -1 && server.aof_child_pid == -1)
         dictEnableResize();
     else
         dictDisableResize();
@@ -673,7 +673,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * if we resize the HT while there is the saving child at work actually
      * a lot of memory movements in the parent will cause a lot of pages
      * copied. */
-    if (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1) {
+    if (server.bgsavechildpid == -1 && server.aof_child_pid == -1) {
         if (!(loops % 10)) tryResizeHashTables();
         if (server.activerehashing) incrementallyRehash();
     }
@@ -692,14 +692,14 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
 
     /* Start a scheduled AOF rewrite if this was requested by the user while
      * a BGSAVE was in progress. */
-    if (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1 &&
+    if (server.bgsavechildpid == -1 && server.aof_child_pid == -1 &&
         server.aof_rewrite_scheduled)
     {
         rewriteAppendOnlyFileBackground();
     }
 
     /* Check if a background saving or AOF rewrite in progress terminated. */
-    if (server.bgsavechildpid != -1 || server.bgrewritechildpid != -1) {
+    if (server.bgsavechildpid != -1 || server.aof_child_pid != -1) {
         int statloc;
         pid_t pid;
 
@@ -735,7 +735,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
 
          /* Trigger an AOF rewrite if needed */
          if (server.bgsavechildpid == -1 &&
-             server.bgrewritechildpid == -1 &&
+             server.aof_child_pid == -1 &&
              server.aof_rewrite_perc &&
              server.aof_current_size > server.aof_rewrite_min_size)
          {
@@ -880,9 +880,9 @@ void initServerConfig() {
     server.aof_rewrite_min_size = REDIS_AOF_REWRITE_MIN_SIZE;
     server.aof_rewrite_base_size = 0;
     server.aof_rewrite_scheduled = 0;
-    server.lastfsync = time(NULL);
-    server.appendfd = -1;
-    server.appendseldb = -1; /* Make sure the first time will not match */
+    server.aof_last_fsync = time(NULL);
+    server.aof_fd = -1;
+    server.aof_selected_db = -1; /* Make sure the first time will not match */
     server.aof_flush_postponed_start = 0;
     server.pidfile = zstrdup("/var/run/redis.pid");
     server.dbfilename = zstrdup("dump.rdb");
@@ -1045,9 +1045,9 @@ void initServer() {
     listSetMatchMethod(server.pubsub_patterns,listMatchPubsubPattern);
     server.cronloops = 0;
     server.bgsavechildpid = -1;
-    server.bgrewritechildpid = -1;
-    server.bgrewritebuf = sdsempty();
-    server.aofbuf = sdsempty();
+    server.aof_child_pid = -1;
+    server.aof_rewrite_buf = sdsempty();
+    server.aof_buf = sdsempty();
     server.lastsave = time(NULL);
     server.dirty = 0;
     server.stat_numcommands = 0;
@@ -1068,9 +1068,9 @@ void initServer() {
         acceptUnixHandler,NULL) == AE_ERR) oom("creating file event");
 
     if (server.aof_state == REDIS_AOF_ON) {
-        server.appendfd = open(server.aof_filename,
+        server.aof_fd = open(server.aof_filename,
                                O_WRONLY|O_APPEND|O_CREAT,0644);
-        if (server.appendfd == -1) {
+        if (server.aof_fd == -1) {
             redisLog(REDIS_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));
             exit(1);
@@ -1313,14 +1313,14 @@ int prepareForShutdown(int flags) {
     if (server.aof_state != REDIS_AOF_OFF) {
         /* Kill the AOF saving child as the AOF we already have may be longer
          * but contains the full dataset anyway. */
-        if (server.bgrewritechildpid != -1) {
+        if (server.aof_child_pid != -1) {
             redisLog(REDIS_WARNING,
                 "There is a child rewriting the AOF. Killing it!");
-            kill(server.bgrewritechildpid,SIGKILL);
+            kill(server.aof_child_pid,SIGKILL);
         }
         /* Append only file: fsync() the AOF and exit */
         redisLog(REDIS_NOTICE,"Calling fsync() on the AOF file.");
-        aof_fsync(server.appendfd);
+        aof_fsync(server.aof_fd);
     }
     if ((server.saveparamslen > 0 && !nosave) || save) {
         redisLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
@@ -1501,7 +1501,7 @@ sds genRedisInfoString(char *section) {
             server.dirty,
             server.bgsavechildpid != -1,
             server.lastsave,
-            server.bgrewritechildpid != -1);
+            server.aof_child_pid != -1);
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,
@@ -1513,7 +1513,7 @@ sds genRedisInfoString(char *section) {
                 (long long) server.aof_current_size,
                 (long long) server.aof_rewrite_base_size,
                 server.aof_rewrite_scheduled,
-                sdslen(server.aofbuf),
+                sdslen(server.aof_buf),
                 bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC));
         }
 