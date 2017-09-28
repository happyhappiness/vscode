             copyClientOutputBuffer(c,slave);
             replicationSetupSlaveForFullResync(c,slave->psync_initial_offset);
             serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
-            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
+            serverLog(LL_NOTICE,"Can't attach the slave to the current BGSAVE. Waiting for next BGSAVE for SYNC");
         }
 
     /* CASE 2: BGSAVE is in progress, with socket target. */
     } else if (server.rdb_child_pid != -1 &&
                server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
     {
         /* There is an RDB child process but it is writing directly to
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
-        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
+        serverLog(LL_NOTICE,"Current BGSAVE has socket target. Waiting for next BGSAVE for SYNC");
 
     /* CASE 3: There is no BGSAVE is progress. */
     } else {
         if (server.repl_diskless_sync && (c->slave_capa & SLAVE_CAPA_EOF)) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
             if (server.repl_diskless_sync_delay)
-                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
+                serverLog(LL_NOTICE,"Delay next BGSAVE for diskless SYNC");
         } else {
             /* Target is disk (or the slave is not capable of supporting
              * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            if (startBgsaveForReplication(c->slave_capa) != C_OK) return;
+            if (server.aof_child_pid != -1) {
+                startBgsaveForReplication(c->slave_capa);
+            } else {
+                serverLog(LL_NOTICE,
+                    "No BGSAVE in progress, but an AOF rewrite is active. "
+                    "BGSAVE for replication delayed");
+            }
         }
     }
 
     if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
         createReplicationBacklog();
     return;
