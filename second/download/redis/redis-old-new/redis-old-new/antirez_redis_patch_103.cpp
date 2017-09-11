@@ -1079,7 +1079,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             {
                 serverLog(LL_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, (int)sp->seconds);
-                rdbSaveBackground(server.rdb_filename);
+                rdbSaveBackground(server.rdb_filename,NULL);
                 break;
             }
          }
@@ -1151,7 +1151,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
         (server.unixtime-server.lastbgsave_try > CONFIG_BGSAVE_RETRY_DELAY ||
          server.lastbgsave_status == C_OK))
     {
-        if (rdbSaveBackground(server.rdb_filename) == C_OK)
+        if (rdbSaveBackground(server.rdb_filename,NULL) == C_OK)
             server.rdb_bgsave_scheduled = 0;
     }
 
@@ -1309,10 +1309,11 @@ void initServerConfig(void) {
     int j;
 
     getRandomHexChars(server.runid,CONFIG_RUN_ID_SIZE);
+    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
+    changeReplicationId();
     server.configfile = NULL;
     server.executable = NULL;
     server.hz = CONFIG_DEFAULT_HZ;
-    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
     server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
     server.port = CONFIG_DEFAULT_SERVER_PORT;
     server.tcp_backlog = CONFIG_DEFAULT_TCP_BACKLOG;
@@ -1409,7 +1410,7 @@ void initServerConfig(void) {
     server.masterport = 6379;
     server.master = NULL;
     server.cached_master = NULL;
-    server.repl_master_initial_offset = -1;
+    server.master_initial_offset = -1;
     server.repl_state = REPL_STATE_NONE;
     server.repl_syncio_timeout = CONFIG_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA;
@@ -2471,7 +2472,7 @@ int prepareForShutdown(int flags) {
     if ((server.saveparamslen > 0 && !nosave) || save) {
         serverLog(LL_NOTICE,"Saving the final RDB snapshot before exiting.");
         /* Snapshotting. Perform a SYNC SAVE and exit */
-        if (rdbSave(server.rdb_filename) != C_OK) {
+        if (rdbSave(server.rdb_filename,NULL) != C_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
@@ -3135,12 +3136,18 @@ sds genRedisInfoString(char *section) {
             }
         }
         info = sdscatprintf(info,
+            "master_replid:%s\r\n"
+            "master_replid2:%s\r\n"
             "master_repl_offset:%lld\r\n"
+            "second_repl_offset:%lld\r\n"
             "repl_backlog_active:%d\r\n"
             "repl_backlog_size:%lld\r\n"
             "repl_backlog_first_byte_offset:%lld\r\n"
             "repl_backlog_histlen:%lld\r\n",
+            server.replid,
+            server.replid2,
             server.master_repl_offset,
+            server.second_replid_offset,
             server.repl_backlog != NULL,
             server.repl_backlog_size,
             server.repl_backlog_off,
@@ -3416,7 +3423,7 @@ void loadDataFromDisk(void) {
         if (loadAppendOnlyFile(server.aof_filename) == C_OK)
             serverLog(LL_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {
-        if (rdbLoad(server.rdb_filename) == C_OK) {
+        if (rdbLoad(server.rdb_filename,NULL) == C_OK) {
             serverLog(LL_NOTICE,"DB loaded from disk: %.3f seconds",
                 (float)(ustime()-start)/1000000);
         } else if (errno != ENOENT) {