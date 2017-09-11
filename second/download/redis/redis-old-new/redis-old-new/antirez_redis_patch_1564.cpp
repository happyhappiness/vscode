@@ -413,11 +413,6 @@ int rdbSave(char *filename) {
     int j;
     time_t now = time(NULL);
 
-    if (server.ds_enabled) {
-        cacheForcePointInTime();
-        return dsRdbSave(filename);
-    }
-
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
@@ -484,16 +479,10 @@ int rdbSaveBackground(char *filename) {
     pid_t childpid;
     long long start;
 
-    if (server.bgsavechildpid != -1 ||
-        server.bgsavethread != (pthread_t) -1) return REDIS_ERR;
+    if (server.bgsavechildpid != -1) return REDIS_ERR;
 
     server.dirty_before_bgsave = server.dirty;
 
-    if (server.ds_enabled) {
-        cacheForcePointInTime();
-        return dsRdbSaveBackground(filename);
-    }
-
     start = ustime();
     if ((childpid = fork()) == 0) {
         int retval;
@@ -1013,15 +1002,13 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
         rdbRemoveTempFile(server.bgsavechildpid);
     }
     server.bgsavechildpid = -1;
-    server.bgsavethread = (pthread_t) -1;
-    server.bgsavethread_state = REDIS_BGSAVE_THREAD_UNACTIVE;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
     updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
 }
 
 void saveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
+    if (server.bgsavechildpid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
     }
@@ -1033,7 +1020,7 @@ void saveCommand(redisClient *c) {
 }
 
 void bgsaveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
+    if (server.bgsavechildpid != -1) {
         addReplyError(c,"Background save already in progress");
     } else if (server.bgrewritechildpid != -1) {
         addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");