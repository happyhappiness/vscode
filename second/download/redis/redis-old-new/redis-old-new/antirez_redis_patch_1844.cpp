@@ -702,6 +702,8 @@ void createSharedObjects(void) {
         "-ERR source and destination objects are the same\r\n"));
     shared.outofrangeerr = createObject(REDIS_STRING,sdsnew(
         "-ERR index out of range\r\n"));
+    shared.loadingerr = createObject(REDIS_STRING,sdsnew(
+        "-LOADING Redis is loading the dataset in memory\r\n"));
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
     shared.colon = createObject(REDIS_STRING,sdsnew(":"));
     shared.plus = createObject(REDIS_STRING,sdsnew("+"));
@@ -739,6 +741,7 @@ void initServerConfig() {
     server.verbosity = REDIS_VERBOSE;
     server.maxidletime = REDIS_MAXIDLETIME;
     server.saveparams = NULL;
+    server.loading = 0;
     server.logfile = NULL; /* NULL = log on standard output */
     server.glueoutputbuf = 1;
     server.daemonize = 0;
@@ -1006,6 +1009,12 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* Loading DB? Return an error if the command is not INFO */
+    if (server.loading && cmd->proc != infoCommand) {
+        addReply(c, shared.loadingerr);
+        return REDIS_OK;
+    }
+
     /* Exec the command */
     if (c->flags & REDIS_MULTI &&
         cmd->proc != execCommand && cmd->proc != discardCommand &&
@@ -1133,6 +1142,8 @@ sds genRedisInfoString(void) {
         "used_memory_rss:%zu\r\n"
         "mem_fragmentation_ratio:%.2f\r\n"
         "use_tcmalloc:%d\r\n"
+        "loading:%d\r\n"
+        "aof_enabled:%d\r\n"
         "changes_since_last_save:%lld\r\n"
         "bgsave_in_progress:%d\r\n"
         "last_save_time:%ld\r\n"
@@ -1173,6 +1184,8 @@ sds genRedisInfoString(void) {
 #else
         0,
 #endif
+        server.loading,
+        server.appendonly,
         server.dirty,
         server.bgsavechildpid != -1,
         server.lastsave,
@@ -1243,6 +1256,35 @@ sds genRedisInfoString(void) {
         );
         unlockThreadedIO();
     }
+    if (server.loading) {
+        double perc;
+        time_t eta, elapsed;
+        off_t remaining_bytes = server.loading_total_bytes-
+                                server.loading_loaded_bytes;
+
+        perc = ((double)server.loading_loaded_bytes /
+               server.loading_total_bytes) * 100;
+
+        elapsed = time(NULL)-server.loading_start_time;
+        if (elapsed == 0) {
+            eta = 1; /* A fake 1 second figure if we don't have enough info */
+        } else {
+            eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
+        }
+
+        info = sdscatprintf(info,
+            "loading_start_time:%ld\r\n"
+            "loading_total_bytes:%llu\r\n"
+            "loading_loaded_bytes:%llu\r\n"
+            "loading_loaded_perc:%.2f\r\n"
+            "loading_eta_seconds:%ld\r\n"
+            ,(unsigned long) server.loading_start_time,
+            (unsigned long long) server.loading_total_bytes,
+            (unsigned long long) server.loading_loaded_bytes,
+            perc,
+            eta
+        );
+    }
     for (j = 0; j < server.dbnum; j++) {
         long long keys, vkeys;
 