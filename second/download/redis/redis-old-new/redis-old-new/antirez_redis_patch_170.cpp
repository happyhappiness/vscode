@@ -647,7 +647,7 @@ void syncCommand(client *c) {
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
-            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
+            serverLog(LL_NOTICE,"Can't attach the slave to the current BGSAVE. Waiting for next BGSAVE for SYNC");
         }
 
     /* CASE 2: BGSAVE is in progress, with socket target. */
@@ -657,7 +657,7 @@ void syncCommand(client *c) {
         /* There is an RDB child process but it is writing directly to
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
-        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
+        serverLog(LL_NOTICE,"Current BGSAVE has socket target. Waiting for next BGSAVE for SYNC");
 
     /* CASE 3: There is no BGSAVE is progress. */
     } else {
@@ -671,7 +671,7 @@ void syncCommand(client *c) {
             /* Target is disk (or the slave is not capable of supporting
              * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            if (startBgsaveForReplication(c->slave_capa) != C_OK) return;
+            serverLog(LL_NOTICE,"No BGSAVE in progress. Starting one ASAP");
         }
     }
 
@@ -2307,13 +2307,12 @@ void replicationCron(void) {
         replicationScriptCacheFlush();
     }
 
-    /* If we are using diskless replication and there are slaves waiting
-     * in WAIT_BGSAVE_START state, check if enough seconds elapsed and
-     * start a BGSAVE.
+    /* Start a BGSAVE good for replication if we have slaves in
+     * WAIT_BGSAVE_START state.
      *
-     * This code is also useful to trigger a BGSAVE if the diskless
-     * replication was turned off with CONFIG SET, while there were already
-     * slaves in WAIT_BGSAVE_START state. */
+     * In case of diskless replication, we make sure to wait the specified
+     * number of seconds (according to configuration) so that other slaves
+     * have the time to arrive before we start streaming. */
     if (server.rdb_child_pid == -1 && server.aof_child_pid == -1) {
         time_t idle, max_idle = 0;
         int slaves_waiting = 0;
@@ -2333,9 +2332,13 @@ void replicationCron(void) {
             }
         }
 
-        if (slaves_waiting && max_idle > server.repl_diskless_sync_delay) {
-            /* Start a BGSAVE. Usually with socket target, or with disk target
-             * if there was a recent socket -> disk config change. */
+        if (slaves_waiting &&
+            (!server.repl_diskless_sync ||
+             max_idle > server.repl_diskless_sync_delay))
+        {
+            /* Start the BGSAVE. The called function may start a
+             * BGSAVE with socket target or disk target depending on the
+             * configuration and slaves capabilities. */
             startBgsaveForReplication(mincapa);
         }
     }