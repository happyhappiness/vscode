@@ -483,14 +483,18 @@ int masterTryPartialResynchronization(client *c) {
  * socket target depending on the configuration, and making sure that
  * the script cache is flushed before to start.
  *
+ * The mincapa argument is the bitwise AND among all the slaves capabilities
+ * of the slaves waiting for this BGSAVE, so represents the slave capabilities
+ * all the slaves support. Can be tested via SLAVE_CAPA_* macros.
+ *
  * Returns C_OK on success or C_ERR otherwise. */
-int startBgsaveForReplication(void) {
+int startBgsaveForReplication(int mincapa) {
     int retval;
 
     serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
         server.repl_diskless_sync ? "slaves sockets" : "disk");
 
-    if (server.repl_diskless_sync)
+    if (server.repl_diskless_sync && (mincapa & SLAVE_CAPA_EOF))
         retval = rdbSaveToSlavesSockets();
     else
         retval = rdbSaveBackground(server.rdb_filename);
@@ -560,7 +564,7 @@ void syncCommand(client *c) {
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
 
-    /* CASE 1: BGSAVE is in progress and replication target is disk. */
+    /* CASE 1: BGSAVE is in progress, with disk target. */
     if (server.rdb_child_pid != -1 &&
         server.rdb_child_type == RDB_CHILD_TYPE_DISK)
     {
@@ -576,7 +580,9 @@ void syncCommand(client *c) {
             slave = ln->value;
             if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) break;
         }
-        if (ln) {
+        /* To attach this slave, we check that it has at least all the
+         * capabilities of the slave that triggered the current BGSAVE. */
+        if (ln && ((c->slave_capa & slave->slave_capa) == slave->slave_capa)) {
             /* Perfect, the server is already registering differences for
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
@@ -589,7 +595,7 @@ void syncCommand(client *c) {
             serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
 
-    /* CASE 2: BGSAVE is in progress and replication target is socket. */
+    /* CASE 2: BGSAVE is in progress, with socket target. */
     } else if (server.rdb_child_pid != -1 &&
                server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
     {
@@ -601,17 +607,18 @@ void syncCommand(client *c) {
 
     /* CASE 3: There is no BGSAVE is progress. */
     } else {
-        if (server.repl_diskless_sync) {
+        if (server.repl_diskless_sync && (c->slave_capa & SLAVE_CAPA_EOF)) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
             c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
             if (server.repl_diskless_sync_delay)
                 serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
-            /* Target is disk and we don't have a BGSAVE in progress,
+            /* Target is disk (or the slave is not capable of supporting
+             * diskless replication) and we don't have a BGSAVE in progress,
              * let's start one. */
-            if (startBgsaveForReplication() != C_OK) {
+            if (startBgsaveForReplication(c->slave_capa) != C_OK) {
                 serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");
                 return;
@@ -661,6 +668,10 @@ void replconfCommand(client *c) {
                     &port,NULL) != C_OK))
                 return;
             c->slave_listening_port = port;
+        } else if (!strcasecmp(c->argv[j]->ptr,"capa")) {
+            /* Ignore capabilities not understood by this master. */
+            if (!strcasecmp(c->argv[j+1]->ptr,"eof"))
+                c->slave_capa |= SLAVE_CAPA_EOF;
         } else if (!strcasecmp(c->argv[j]->ptr,"ack")) {
             /* REPLCONF ACK is used by slave to inform the master the amount
              * of replication stream that it processed so far. It is an
@@ -794,6 +805,7 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
 void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     listNode *ln;
     int startbgsave = 0;
+    int mincapa = -1;
     listIter li;
 
     listRewind(server.slaves,&li);
@@ -802,6 +814,8 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
         if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             startbgsave = 1;
+            mincapa = (mincapa == -1) ? slave->slave_capa :
+                                        (mincapa & slave->slave_capa);
             replicationSetupSlaveForFullResync(slave,getPsyncInitialOffset());
         } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
@@ -850,7 +864,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
         }
     }
     if (startbgsave) {
-        if (startBgsaveForReplication() != C_OK) {
+        if (startBgsaveForReplication(mincapa) != C_OK) {
             listIter li;
 
             listRewind(server.slaves,&li);
@@ -1362,7 +1376,24 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF listening-port. */
         if (err[0] == '-') {
-            serverLog(LL_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
+            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
+                                "REPLCONF listening-port: %s", err);
+        }
+        sdsfree(err);
+    }
+
+    /* Inform the master of our capabilities. While we currently send
+     * just one capability, it is possible to chain new capabilities here
+     * in the form of REPLCONF capa X capa Y capa Z ...
+     * The master will ignore capabilities it does not understand. */
+    {
+        err = sendSynchronousCommand(fd,"REPLCONF","capa","eof",NULL);
+
+        /* Ignore the error if any, not all the Redis versions support
+         * REPLCONF capa. */
+        if (err[0] == '-') {
+            serverLog(LL_NOTICE,"(Non critical) Master does not understand "
+                                  "REPLCONF capa: %s", err);
         }
         sdsfree(err);
     }
@@ -2145,6 +2176,7 @@ void replicationCron(void) {
     if (server.rdb_child_pid == -1 && server.aof_child_pid == -1) {
         time_t idle, max_idle = 0;
         int slaves_waiting = 0;
+        int mincapa = -1;
         listNode *ln;
         listIter li;
 
@@ -2155,13 +2187,15 @@ void replicationCron(void) {
                 idle = server.unixtime - slave->lastinteraction;
                 if (idle > max_idle) max_idle = idle;
                 slaves_waiting++;
+                mincapa = (mincapa == -1) ? slave->slave_capa :
+                                            (mincapa & slave->slave_capa);
             }
         }
 
         if (slaves_waiting && max_idle > server.repl_diskless_sync_delay) {
             /* Start a BGSAVE. Usually with socket target, or with disk target
              * if there was a recent socket -> disk config change. */
-            if (startBgsaveForReplication() == C_OK) {
+            if (startBgsaveForReplication(mincapa) == C_OK) {
                 /* It started! We need to change the state of slaves
                  * from WAIT_BGSAVE_START to WAIT_BGSAVE_END in case
                  * the current target is disk. Otherwise it was already done