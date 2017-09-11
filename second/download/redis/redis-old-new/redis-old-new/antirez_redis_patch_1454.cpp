@@ -923,7 +923,7 @@ void initServerConfig() {
     server.masterhost = NULL;
     server.masterport = 6379;
     server.master = NULL;
-    server.replstate = REDIS_REPL_NONE;
+    server.repl_state = REDIS_REPL_NONE;
     server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
     server.repl_down_since = -1;
@@ -1254,7 +1254,7 @@ int processCommand(redisClient *c) {
 
     /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and
      * we are a slave with a broken link with master. */
-    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED &&
+    if (server.masterhost && server.repl_state != REDIS_REPL_CONNECTED &&
         server.repl_serve_stale_data == 0 &&
         c->cmd->proc != infoCommand && c->cmd->proc != slaveofCommand)
     {
@@ -1592,14 +1592,14 @@ sds genRedisInfoString(char *section) {
                 "master_sync_in_progress:%d\r\n"
                 ,server.masterhost,
                 server.masterport,
-                (server.replstate == REDIS_REPL_CONNECTED) ?
+                (server.repl_state == REDIS_REPL_CONNECTED) ?
                     "up" : "down",
                 server.master ?
                 ((int)(time(NULL)-server.master->lastinteraction)) : -1,
-                server.replstate == REDIS_REPL_TRANSFER
+                server.repl_state == REDIS_REPL_TRANSFER
             );
 
-            if (server.replstate == REDIS_REPL_TRANSFER) {
+            if (server.repl_state == REDIS_REPL_TRANSFER) {
                 info = sdscatprintf(info,
                     "master_sync_left_bytes:%ld\r\n"
                     "master_sync_last_io_seconds_ago:%d\r\n"
@@ -1608,7 +1608,7 @@ sds genRedisInfoString(char *section) {
                 );
             }
 
-            if (server.replstate != REDIS_REPL_CONNECTED) {
+            if (server.repl_state != REDIS_REPL_CONNECTED) {
                 info = sdscatprintf(info,
                     "master_link_down_since_seconds:%ld\r\n",
                     (long)time(NULL)-server.repl_down_since);