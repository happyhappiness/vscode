@@ -374,7 +374,10 @@ long long getPsyncInitialOffset(void) {
  * 3) Force the replication stream to re-emit a SELECT statement so
  *    the new slave incremental differences will start selecting the
  *    right database number.
- */
+ *
+ * Normally this function should be called immediately after a successful
+ * BGSAVE for replication was started, or when there is one already in
+ * progress that we attached our slave to. */
 int replicationSetupSlaveForFullResync(client *slave, long long offset) {
     char buf[128];
     int buflen;
@@ -487,10 +490,21 @@ int masterTryPartialResynchronization(client *c) {
  * of the slaves waiting for this BGSAVE, so represents the slave capabilities
  * all the slaves support. Can be tested via SLAVE_CAPA_* macros.
  *
+ * Side effects, other than starting a BGSAVE:
+ *
+ * 1) Handle the slaves in WAIT_START state, by preparing them for a full
+ *    sync if the BGSAVE was succesfully started, or sending them an error
+ *    and dropping them from the list of slaves.
+ *
+ * 2) Flush the Lua scripting script cache if the BGSAVE was actually
+ *    started.
+ *
  * Returns C_OK on success or C_ERR otherwise. */
 int startBgsaveForReplication(int mincapa) {
     int retval;
     int socket_target = server.repl_diskless_sync && (mincapa & SLAVE_CAPA_EOF);
+    listIter li;
+    listNode *ln;
 
     serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
         socket_target ? "slaves sockets" : "disk");
@@ -500,6 +514,40 @@ int startBgsaveForReplication(int mincapa) {
     else
         retval = rdbSaveBackground(server.rdb_filename);
 
+    /* If we failed to BGSAVE, remove the slaves waiting for a full
+     * resynchorinization from the list of salves, inform them with
+     * an error about what happened, close the connection ASAP. */
+    if (retval == C_ERR) {
+        serverLog(LL_WARNING,"BGSAVE for replication failed");
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            client *slave = ln->value;
+
+            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
+                slave->flags &= ~CLIENT_SLAVE;
+                listDelNode(server.slaves,ln);
+                addReplyError(slave,
+                    "BGSAVE failed, replication can't continue");
+                slave->flags |= CLIENT_CLOSE_AFTER_REPLY;
+            }
+        }
+        return retval;
+    }
+
+    /* If the target is socket, rdbSaveToSlavesSockets() already setup
+     * the salves for a full resync. Otherwise for disk target do it now.*/
+    if (!socket_target) {
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            client *slave = ln->value;
+
+            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
+                    replicationSetupSlaveForFullResync(slave,
+                            getPsyncInitialOffset());
+            }
+        }
+    }
+
     /* Flush the script cache, since we need that slave differences are
      * accumulated without requiring slaves to match our cached scripts. */
     if (retval == C_OK) replicationScriptCacheFlush();
@@ -562,8 +610,14 @@ void syncCommand(client *c) {
     /* Full resynchronization. */
     server.stat_sync_full++;
 
-    /* Here we need to check if there is a background saving operation
-     * in progress, or if it is required to start one */
+    /* Setup the slave as one waiting for BGSAVE to start. The following code
+     * paths will change the state if we handle the slave differently. */
+    c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
+    if (server.repl_disable_tcp_nodelay)
+        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
+    c->repldbfd = -1;
+    c->flags |= CLIENT_SLAVE;
+    listAddNodeTail(server.slaves,c);
 
     /* CASE 1: BGSAVE is in progress, with disk target. */
     if (server.rdb_child_pid != -1 &&
@@ -592,7 +646,6 @@ void syncCommand(client *c) {
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
-            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
             serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
 
@@ -603,7 +656,6 @@ void syncCommand(client *c) {
         /* There is an RDB child process but it is writing directly to
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
-        c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
         serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
 
     /* CASE 3: There is no BGSAVE is progress. */
@@ -612,27 +664,16 @@ void syncCommand(client *c) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
-            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
             if (server.repl_diskless_sync_delay)
                 serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
             /* Target is disk (or the slave is not capable of supporting
              * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            if (startBgsaveForReplication(c->slave_capa) != C_OK) {
-                serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
-                addReplyError(c,"Unable to perform background save");
-                return;
-            }
-            replicationSetupSlaveForFullResync(c,getPsyncInitialOffset());
+            if (startBgsaveForReplication(c->slave_capa) != C_OK) return;
         }
     }
 
-    if (server.repl_disable_tcp_nodelay)
-        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
-    c->repldbfd = -1;
-    c->flags |= CLIENT_SLAVE;
-    listAddNodeTail(server.slaves,c);
     if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
         createReplicationBacklog();
     return;
@@ -817,7 +858,6 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             startbgsave = 1;
             mincapa = (mincapa == -1) ? slave->slave_capa :
                                         (mincapa & slave->slave_capa);
-            replicationSetupSlaveForFullResync(slave,getPsyncInitialOffset());
         } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
@@ -864,20 +904,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             }
         }
     }
-    if (startbgsave) {
-        if (startBgsaveForReplication(mincapa) != C_OK) {
-            listIter li;
-
-            listRewind(server.slaves,&li);
-            serverLog(LL_WARNING,"SYNC failed. BGSAVE failed");
-            while((ln = listNext(&li))) {
-                client *slave = ln->value;
-
-                if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START)
-                    freeClient(slave);
-            }
-        }
-    }
+    if (startbgsave) startBgsaveForReplication(mincapa);
 }
 
 /* ----------------------------------- SLAVE -------------------------------- */
@@ -2311,21 +2338,7 @@ void replicationCron(void) {
         if (slaves_waiting && max_idle > server.repl_diskless_sync_delay) {
             /* Start a BGSAVE. Usually with socket target, or with disk target
              * if there was a recent socket -> disk config change. */
-            if (startBgsaveForReplication(mincapa) == C_OK) {
-                /* It started! We need to change the state of slaves
-                 * from WAIT_BGSAVE_START to WAIT_BGSAVE_END in case
-                 * the current target is disk. Otherwise it was already done
-                 * by rdbSaveToSlavesSockets() which is called by
-                 * startBgsaveForReplication(). */
-                listRewind(server.slaves,&li);
-                while((ln = listNext(&li))) {
-                    client *slave = ln->value;
-                    if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
-                        replicationSetupSlaveForFullResync(slave,
-                            getPsyncInitialOffset());
-                    }
-                }
-            }
+            startBgsaveForReplication(mincapa);
         }
     }
 