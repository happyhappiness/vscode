 
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
             slave = ln->value;
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) break;
         }
-        /* To attach this slave, we check that it has at least all the
-         * capabilities of the slave that triggered the current BGSAVE. */
-        if (ln && ((c->slave_capa & slave->slave_capa) == slave->slave_capa)) {
+        if (ln) {
             /* Perfect, the server is already registering differences for
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
-            replicationSetupSlaveForFullResync(c,slave->psync_initial_offset);
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
             redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
-
-    /* CASE 2: BGSAVE is in progress, with socket target. */
     } else if (server.rdb_child_pid != -1 &&
                server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
     {
         /* There is an RDB child process but it is writing directly to
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
+        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
         redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
-
-    /* CASE 3: There is no BGSAVE is progress. */
     } else {
-        if (server.repl_diskless_sync && (c->slave_capa & SLAVE_CAPA_EOF)) {
+        if (server.repl_diskless_sync) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             if (server.repl_diskless_sync_delay)
                 redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
-            /* Target is disk (or the slave is not capable of supporting
-             * diskless replication) and we don't have a BGSAVE in progress,
-             * let's start one. */
-            if (startBgsaveForReplication(c->slave_capa) != REDIS_OK) return;
+            /* Ok we don't have a BGSAVE in progress, let's start one. */
+            if (startBgsaveForReplication() != REDIS_OK) {
+                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                addReplyError(c,"Unable to perform background save");
+                return;
+            }
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         }
     }
 
+    if (server.repl_disable_tcp_nodelay)
+        anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
+    c->repldbfd = -1;
+    c->flags |= REDIS_SLAVE;
+    server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
+    listAddNodeTail(server.slaves,c);
     if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
         createReplicationBacklog();
     return;
 }
 
 /* REPLCONF <option> <value> <option> <value> ...
