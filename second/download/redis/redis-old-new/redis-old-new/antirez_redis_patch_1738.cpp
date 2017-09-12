@@ -496,22 +496,23 @@ int rdbSave(char *filename) {
 int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
-    if (server.bgsavechildpid != -1) return REDIS_ERR;
+    if (server.bgsavechildpid != -1 ||
+        server.bgsavethread != (pthread_t) -1) return REDIS_ERR;
 
     server.dirty_before_bgsave = server.dirty;
 
+    if (server.ds_enabled) {
+        cacheForcePointInTime();
+        return dsRdbSave(filename);
+    }
+
     if ((childpid = fork()) == 0) {
         int retval;
 
         /* Child */
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
-        if (server.ds_enabled) {
-            cacheForcePointInTime();
-            dsRdbSave(filename);
-        } else {
-            rdbSave(filename);
-        }
+        retval = rdbSave(filename);
         _exit((retval == REDIS_OK) ? 0 : 1);
     } else {
         /* Parent */
@@ -950,10 +951,7 @@ int rdbLoad(char *filename) {
 }
 
 /* A background saving child (BGSAVE) terminated its work. Handle this. */
-void backgroundSaveDoneHandler(int statloc) {
-    int exitcode = WEXITSTATUS(statloc);
-    int bysignal = WIFSIGNALED(statloc);
-
+void backgroundSaveDoneHandler(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
         redisLog(REDIS_NOTICE,
             "Background saving terminated with success");
@@ -963,11 +961,37 @@ void backgroundSaveDoneHandler(int statloc) {
         redisLog(REDIS_WARNING, "Background saving error");
     } else {
         redisLog(REDIS_WARNING,
-            "Background saving terminated by signal %d", WTERMSIG(statloc));
+            "Background saving terminated by signal %d", bysignal);
         rdbRemoveTempFile(server.bgsavechildpid);
     }
     server.bgsavechildpid = -1;
+    server.bgsavethread = (pthread_t) -1;
+    server.bgsavethread_state = REDIS_BGSAVE_THREAD_UNACTIVE;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
     updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
 }
+
+void saveCommand(redisClient *c) {
+    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
+        addReplyError(c,"Background save already in progress");
+        return;
+    }
+    if (rdbSave(server.dbfilename) == REDIS_OK) {
+        addReply(c,shared.ok);
+    } else {
+        addReply(c,shared.err);
+    }
+}
+
+void bgsaveCommand(redisClient *c) {
+    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
+        addReplyError(c,"Background save already in progress");
+        return;
+    }
+    if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
+        addReplyStatus(c,"Background saving started");
+    } else {
+        addReply(c,shared.err);
+    }
+}