@@ -666,12 +666,18 @@ void syncCommand(client *c) {
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
             if (server.repl_diskless_sync_delay)
-                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
+                serverLog(LL_NOTICE,"Delay next BGSAVE for diskless SYNC");
         } else {
             /* Target is disk (or the slave is not capable of supporting
              * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            serverLog(LL_NOTICE,"No BGSAVE in progress. Starting one ASAP");
+            if (server.aof_child_pid != -1) {
+                startBgsaveForReplication(c->slave_capa);
+            } else {
+                serverLog(LL_NOTICE,
+                    "No BGSAVE in progress, but an AOF rewrite is active. "
+                    "BGSAVE for replication delayed");
+            }
         }
     }
 