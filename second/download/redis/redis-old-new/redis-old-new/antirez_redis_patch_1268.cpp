@@ -2115,7 +2115,10 @@ sds genRedisInfoString(char *section) {
                     (long)server.unixtime-server.repl_down_since);
             }
             info = sdscatprintf(info,
-                "slave_priority:%d\r\n", server.slave_priority);
+                "slave_priority:%d\r\n"
+                "slave_read_only:%d\r\n",
+                server.slave_priority,
+                server.repl_slave_ro);
         }
         info = sdscatprintf(info,
             "connected_slaves:%lu\r\n",