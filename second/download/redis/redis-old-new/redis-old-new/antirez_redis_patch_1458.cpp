@@ -253,7 +253,7 @@ int rdbSaveRawString(rio *rdb, unsigned char *s, size_t len) {
 
     /* Try LZF compression - under 20 bytes it's unable to compress even
      * aaaaaaaaaaaaaaaaaa so skip it */
-    if (server.rdbcompression && len > 20) {
+    if (server.rdb_compression && len > 20) {
         n = rdbSaveLzfStringObject(rdb,s,len);
         if (n == -1) return -1;
         if (n > 0) return n;
@@ -670,7 +670,7 @@ int rdbSaveBackground(char *filename) {
     pid_t childpid;
     long long start;
 
-    if (server.bgsavechildpid != -1) return REDIS_ERR;
+    if (server.rdb_child_pid != -1) return REDIS_ERR;
 
     server.dirty_before_bgsave = server.dirty;
 
@@ -692,7 +692,7 @@ int rdbSaveBackground(char *filename) {
             return REDIS_ERR;
         }
         redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
-        server.bgsavechildpid = childpid;
+        server.rdb_child_pid = childpid;
         updateDictResizePolicy();
         return REDIS_OK;
     }
@@ -1062,32 +1062,32 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
     } else {
         redisLog(REDIS_WARNING,
             "Background saving terminated by signal %d", bysignal);
-        rdbRemoveTempFile(server.bgsavechildpid);
+        rdbRemoveTempFile(server.rdb_child_pid);
     }
-    server.bgsavechildpid = -1;
+    server.rdb_child_pid = -1;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
     updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
 }
 
 void saveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1) {
+    if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
     }
-    if (rdbSave(server.dbfilename) == REDIS_OK) {
+    if (rdbSave(server.rdb_filename) == REDIS_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
     }
 }
 
 void bgsaveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1) {
+    if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
     } else if (server.aof_child_pid != -1) {
         addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
-    } else if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
+    } else if (rdbSaveBackground(server.rdb_filename) == REDIS_OK) {
         addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);