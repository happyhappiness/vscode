@@ -633,14 +633,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
         }
     }
 
-    /* Check if we should connect to a MASTER */
-    if (server.replstate == REDIS_REPL_CONNECT && !(loops % 10)) {
-        redisLog(REDIS_NOTICE,"Connecting to MASTER...");
-        if (syncWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync succeeded");
-            if (server.appendonly) rewriteAppendOnlyFileBackground();
-        }
-    }
+    /* Replication cron function -- used to reconnect to master and
+     * to detect transfer failures. */
+    if (!(loops % 10)) replicationCron();
+
     return 100;
 }
 
@@ -790,6 +786,7 @@ void initServerConfig() {
     server.masterport = 6379;
     server.master = NULL;
     server.replstate = REDIS_REPL_NONE;
+    server.repl_serve_stale_data = 1;
 
     /* Double constants initialization */
     R_Zero = 0.0;
@@ -998,6 +995,17 @@ int processCommand(redisClient *c) {
         return REDIS_OK;
     }
 
+    /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and
+     * we are a slave with a broken link with master. */
+    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
+        server.repl_serve_stale_data == 0 &&
+        cmd->proc != infoCommand && cmd->proc != slaveofCommand)
+    {
+        addReplyError(c,
+            "link with MASTER is down and slave-serve-stale-data is set to no");
+        return REDIS_OK;
+    }
+
     /* Exec the command */
     if (c->flags & REDIS_MULTI &&
         cmd->proc != execCommand && cmd->proc != discardCommand &&
@@ -1187,12 +1195,23 @@ sds genRedisInfoString(void) {
             "master_port:%d\r\n"
             "master_link_status:%s\r\n"
             "master_last_io_seconds_ago:%d\r\n"
+            "master_sync_in_progress:%d\r\n"
             ,server.masterhost,
             server.masterport,
             (server.replstate == REDIS_REPL_CONNECTED) ?
                 "up" : "down",
-            server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1
+            server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1,
+            server.replstate == REDIS_REPL_TRANSFER
         );
+
+        if (server.replstate == REDIS_REPL_TRANSFER) {
+            info = sdscatprintf(info,
+                "master_sync_left_bytes:%ld\r\n"
+                "master_sync_last_io_seconds_ago:%d\r\n"
+                ,(long)server.repl_transfer_left,
+                (int)(time(NULL)-server.repl_transfer_lastio)
+            );
+        }
     }
     if (server.vm_enabled) {
         lockThreadedIO();