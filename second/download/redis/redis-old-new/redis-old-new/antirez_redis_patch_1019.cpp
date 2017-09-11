@@ -2522,6 +2522,13 @@ sds genRedisInfoString(char *section) {
             "role:%s\r\n",
             server.masterhost == NULL ? "master" : "slave");
         if (server.masterhost) {
+            long long slave_repl_offset = 1;
+
+            if (server.master)
+                slave_repl_offset = server.master->reploff;
+            else if (server.cached_master)
+                slave_repl_offset = server.cached_master->reploff;
+
             info = sdscatprintf(info,
                 "master_host:%s\r\n"
                 "master_port:%d\r\n"
@@ -2536,7 +2543,7 @@ sds genRedisInfoString(char *section) {
                 server.master ?
                 ((int)(server.unixtime-server.master->lastinteraction)) : -1,
                 server.repl_state == REDIS_REPL_TRANSFER,
-                server.master ? server.master->reploff : -1
+                slave_repl_offset
             );
 
             if (server.repl_state == REDIS_REPL_TRANSFER) {