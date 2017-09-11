@@ -2326,9 +2326,20 @@ sds genRedisInfoString(char *section) {
                 server.slave_priority,
                 server.repl_slave_ro);
         }
+
         info = sdscatprintf(info,
             "connected_slaves:%lu\r\n",
             listLength(server.slaves));
+
+        /* If min-slaves-to-write is active, write the number of slaves
+         * currently considered 'good'. */
+        if (server.repl_min_slaves_to_write &&
+            server.repl_min_slaves_max_lag) {
+            info = sdscatprintf(info,
+                "min_slaves_good_slaves:%d\r\n",
+                server.repl_good_slaves_count);
+        }
+
         if (listLength(server.slaves)) {
             int slaveid = 0;
             listNode *ln;