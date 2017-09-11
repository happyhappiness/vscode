@@ -676,7 +676,7 @@ void syncCommand(client *c) {
             /* Target is disk (or the slave is not capable of supporting
              * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            if (server.aof_child_pid != -1) {
+            if (server.aof_child_pid == -1) {
                 startBgsaveForReplication(c->slave_capa);
             } else {
                 serverLog(LL_NOTICE,