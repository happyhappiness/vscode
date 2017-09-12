@@ -3489,6 +3489,8 @@ static void infoCommand(redisClient *c) {
     
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
+        "uptime_in_seconds:%d\r\n"
+        "uptime_in_days:%d\r\n"
         "connected_clients:%d\r\n"
         "connected_slaves:%d\r\n"
         "used_memory:%zu\r\n"
@@ -3497,9 +3499,10 @@ static void infoCommand(redisClient *c) {
         "last_save_time:%d\r\n"
         "total_connections_received:%lld\r\n"
         "total_commands_processed:%lld\r\n"
-        "uptime_in_seconds:%d\r\n"
-        "uptime_in_days:%d\r\n"
+        "role:%s\r\n"
         ,REDIS_VERSION,
+        uptime,
+        uptime/(3600*24),
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
         server.usedmemory,
@@ -3508,9 +3511,21 @@ static void infoCommand(redisClient *c) {
         server.lastsave,
         server.stat_numconnections,
         server.stat_numcommands,
-        uptime,
-        uptime/(3600*24)
+        server.masterhost == NULL ? "master" : "slave"
     );
+    if (server.masterhost) {
+        info = sdscatprintf(info,
+            "master_host:%s\r\n"
+            "master_port:%d\r\n"
+            "master_link_status:%s\r\n"
+            "master_last_io_seconds_ago:%d\r\n"
+            ,server.masterhost,
+            server.masterport,
+            (server.replstate == REDIS_REPL_CONNECTED) ?
+                "up" : "down",
+            (int)(time(NULL)-server.master->lastinteraction)
+        );
+    }
     addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);