@@ -1160,6 +1160,7 @@ void initServerConfig() {
     server.repl_serve_stale_data = 1;
     server.repl_slave_ro = 1;
     server.repl_down_since = time(NULL);
+    server.slave_priority = REDIS_DEFAULT_SLAVE_PRIORITY;
 
     /* Client output buffer limits */
     server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_NORMAL].hard_limit_bytes = 0;
@@ -2092,6 +2093,8 @@ sds genRedisInfoString(char *section) {
                     "master_link_down_since_seconds:%ld\r\n",
                     (long)server.unixtime-server.repl_down_since);
             }
+            info = sdscatprintf(info,
+                "slave_priority:%d\r\n", server.slave_priority);
         }
         info = sdscatprintf(info,
             "connected_slaves:%lu\r\n",