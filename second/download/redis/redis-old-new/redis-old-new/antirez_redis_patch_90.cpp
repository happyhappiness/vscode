@@ -79,11 +79,6 @@ void createReplicationBacklog(void) {
     server.repl_backlog = zmalloc(server.repl_backlog_size);
     server.repl_backlog_histlen = 0;
     server.repl_backlog_idx = 0;
-    /* When a new backlog buffer is created, we increment the replication
-     * offset by one to make sure we'll not be able to PSYNC with any
-     * previous slave. This is needed because we avoid incrementing the
-     * master_repl_offset if no backlog exists nor slaves are attached. */
-    server.master_repl_offset++;
 
     /* We don't have any data inside our buffer, but virtually the first
      * byte we have is the next byte that will be generated for the
@@ -153,6 +148,22 @@ void feedReplicationBacklog(void *ptr, size_t len) {
                               server.repl_backlog_histlen + 1;
 }
 
+/* Remove the last byte from the replication backlog. This
+ * is useful when we receive an out of band "\n" to keep the connection
+ * alive but don't want to count it as replication stream.
+ *
+ * As a side effect this function adjusts the master replication offset
+ * of this instance to account for the missing byte. */
+void chopReplicationBacklog(void) {
+    if (!server.repl_backlog || !server.repl_backlog_histlen) return;
+    if (server.repl_backlog_idx == 0)
+        server.repl_backlog_idx = server.repl_backlog_size-1;
+    else
+        server.repl_backlog_idx--;
+    server.master_repl_offset--;
+    server.repl_backlog_histlen--;
+}
+
 /* Wrapper for feedReplicationBacklog() that takes Redis string objects
  * as input. */
 void feedReplicationBacklogWithObject(robj *o) {
@@ -170,12 +181,24 @@ void feedReplicationBacklogWithObject(robj *o) {
     feedReplicationBacklog(p,len);
 }
 
+/* Propagate write commands to slaves, and populate the replication backlog
+ * as well. This function is used if the instance is a master: we use
+ * the commands received by our clients in order to create the replication
+ * stream. Instead if the instance is a slave and has sub-slaves attached,
+ * we use replicationFeedSlavesFromMaster() */
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
     int j, len;
     char llstr[LONG_STR_SIZE];
 
+    /* If the instance is not a top level master, return ASAP: we'll just proxy
+     * the stream of data we receive from our master instead, in order to
+     * propagate *identical* replication stream. In this way this slave can
+     * advertise the same replication ID as the master (since it shares the
+     * master replication history and has the same backlog and offsets). */
+    if (server.masterhost != NULL) return;
+
     /* If there aren't slaves, and there is no backlog buffer to populate,
      * we can return ASAP. */
     if (server.repl_backlog == NULL && listLength(slaves) == 0) return;
@@ -265,6 +288,34 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     }
 }
 
+/* This function is used in order to proxy what we receive from our master
+ * to our sub-slaves. */
+#include <ctype.h>
+void replicationFeedSlavesFromMasterStream(list *slaves, char *buf, size_t buflen) {
+    listNode *ln;
+    listIter li;
+
+    /* Debugging: this is handy to see the stream sent from master
+     * to slaves. Disabled with if(0). */
+    if (0) {
+        printf("%zu:",buflen);
+        for (size_t j = 0; j < buflen; j++) {
+            printf("%c", isprint(buf[j]) ? buf[j] : '.');
+        }
+        printf("\n");
+    }
+
+    if (server.repl_backlog) feedReplicationBacklog(buf,buflen);
+    listRewind(slaves,&li);
+    while((ln = listNext(&li))) {
+        client *slave = ln->value;
+
+        /* Don't feed slaves that are still waiting for BGSAVE to start */
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) continue;
+        addReplyString(slave,buf,buflen);
+    }
+}
+
 void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
@@ -329,7 +380,7 @@ long long addReplyReplicationBacklog(client *c, long long offset) {
     skip = offset - server.repl_backlog_off;
     serverLog(LL_DEBUG, "[PSYNC] Skipping: %lld", skip);
 
-    /* Point j to the oldest byte, that is actaully our
+    /* Point j to the oldest byte, that is actually our
      * server.repl_backlog_off byte. */
     j = (server.repl_backlog_idx +
         (server.repl_backlog_size-server.repl_backlog_histlen)) %
@@ -361,18 +412,14 @@ long long addReplyReplicationBacklog(client *c, long long offset) {
  * the BGSAVE process started and before executing any other command
  * from clients. */
 long long getPsyncInitialOffset(void) {
-    long long psync_offset = server.master_repl_offset;
-    /* Add 1 to psync_offset if it the replication backlog does not exists
-     * as when it will be created later we'll increment the offset by one. */
-    if (server.repl_backlog == NULL) psync_offset++;
-    return psync_offset;
+    return server.master_repl_offset;
 }
 
 /* Send a FULLRESYNC reply in the specific case of a full resynchronization,
  * as a side effect setup the slave for a full sync in different ways:
  *
- * 1) Remember, into the slave client structure, the offset we sent
- *    here, so that if new slaves will later attach to the same
+ * 1) Remember, into the slave client structure, the replication offset
+ *    we sent here, so that if new slaves will later attach to the same
  *    background RDB saving process (by duplicating this client output
  *    buffer), we can get the right offset from this slave.
  * 2) Set the replication state of the slave to WAIT_BGSAVE_END so that
@@ -392,14 +439,14 @@ int replicationSetupSlaveForFullResync(client *slave, long long offset) {
     slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
     /* We are going to accumulate the incremental changes for this
      * slave as well. Set slaveseldb to -1 in order to force to re-emit
-     * a SLEECT statement in the replication stream. */
+     * a SELECT statement in the replication stream. */
     server.slaveseldb = -1;
 
     /* Don't send this reply to slaves that approached us with
      * the old SYNC command. */
     if (!(slave->flags & CLIENT_PRE_PSYNC)) {
         buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
-                          server.runid,offset);
+                          server.replid,offset);
         if (write(slave->fd,buf,buflen) != buflen) {
             freeClientAsync(slave);
             return C_ERR;
@@ -415,19 +462,32 @@ int replicationSetupSlaveForFullResync(client *slave, long long offset) {
  * with the usual full resync. */
 int masterTryPartialResynchronization(client *c) {
     long long psync_offset, psync_len;
-    char *master_runid = c->argv[1]->ptr;
+    char *master_replid = c->argv[1]->ptr;
     char buf[128];
     int buflen;
 
-    /* Is the runid of this master the same advertised by the wannabe slave
-     * via PSYNC? If runid changed this master is a different instance and
-     * there is no way to continue. */
-    if (strcasecmp(master_runid, server.runid)) {
+    /* Parse the replication offset asked by the slave. Go to full sync
+     * on parse error: this should never happen but we try to handle
+     * it in a robust way compared to aborting. */
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
+       C_OK) goto need_full_resync;
+
+    /* Is the replication ID of this master the same advertised by the wannabe
+     * slave via PSYNC? If the replication ID changed this master has a
+     * different replication history, and there is no way to continue.
+     *
+     * Note that there are two potentially valid replication IDs: the ID1
+     * and the ID2. The ID2 however is only valid up to a specific offset. */
+    if (strcasecmp(master_replid, server.replid) &&
+        (strcasecmp(master_replid, server.replid2) ||
+         psync_offset > server.second_replid_offset))
+    {
         /* Run id "?" is used by slaves that want to force a full resync. */
-        if (master_runid[0] != '?') {
+        if (master_replid[0] != '?') {
             serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
-                "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
-                master_runid, server.runid);
+                "Replication ID mismatch (Slave asked for '%s', my replication "
+                "ID is '%s')",
+                master_replid, server.replid);
         } else {
             serverLog(LL_NOTICE,"Full resync requested by slave %s",
                 replicationGetSlaveName(c));
@@ -436,8 +496,6 @@ int masterTryPartialResynchronization(client *c) {
     }
 
     /* We still have the data our slave is asking for? */
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
-       C_OK) goto need_full_resync;
     if (!server.repl_backlog ||
         psync_offset < server.repl_backlog_off ||
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
@@ -463,7 +521,11 @@ int masterTryPartialResynchronization(client *c) {
     /* We can't use the connection buffers since they are used to accumulate
      * new commands at this stage. But we are sure the socket send buffer is
      * empty so this write will never fail actually. */
-    buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
+    if (c->slave_capa & SLAVE_CAPA_PSYNC2) {
+        buflen = snprintf(buf,sizeof(buf),"+CONTINUE %s\r\n", server.replid);
+    } else {
+        buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
+    }
     if (write(c->fd,buf,buflen) != buflen) {
         freeClientAsync(c);
         return C_OK;
@@ -515,10 +577,18 @@ int startBgsaveForReplication(int mincapa) {
     serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
         socket_target ? "slaves sockets" : "disk");
 
+    rdbSaveInfo rsi = RDB_SAVE_INFO_INIT;
+    /* If we are saving for a chained slave (that is, if we are,
+     * in turn, a slave of another instance), make sure after
+     * loadig the RDB, our slaves select the right DB: we'll just
+     * send the replication stream we receive from our master, so
+     * no way to send SELECT commands. */
+    if (server.master) rsi.repl_stream_db = server.master->db->id;
+
     if (socket_target)
-        retval = rdbSaveToSlavesSockets();
+        retval = rdbSaveToSlavesSockets(&rsi);
     else
-        retval = rdbSaveBackground(server.rdb_filename);
+        retval = rdbSaveBackground(server.rdb_filename,&rsi);
 
     /* If we failed to BGSAVE, remove the slaves waiting for a full
      * resynchorinization from the list of salves, inform them with
@@ -589,22 +659,22 @@ void syncCommand(client *c) {
      * when this happens masterTryPartialResynchronization() already
      * replied with:
      *
-     * +FULLRESYNC <runid> <offset>
+     * +FULLRESYNC <replid> <offset>
      *
-     * So the slave knows the new runid and offset to try a PSYNC later
+     * So the slave knows the new replid and offset to try a PSYNC later
      * if the connection with the master is lost. */
     if (!strcasecmp(c->argv[0]->ptr,"psync")) {
         if (masterTryPartialResynchronization(c) == C_OK) {
             server.stat_sync_partial_ok++;
             return; /* No full resync needed, return. */
         } else {
-            char *master_runid = c->argv[1]->ptr;
+            char *master_replid = c->argv[1]->ptr;
 
             /* Increment stats for failed PSYNCs, but only if the
-             * runid is not "?", as this is used by slaves to force a full
+             * replid is not "?", as this is used by slaves to force a full
              * resync on purpose when they are not albe to partially
              * resync. */
-            if (master_runid[0] != '?') server.stat_sync_partial_err++;
+            if (master_replid[0] != '?') server.stat_sync_partial_err++;
         }
     } else {
         /* If a slave uses SYNC, we are dealing with an old implementation
@@ -625,6 +695,16 @@ void syncCommand(client *c) {
     c->flags |= CLIENT_SLAVE;
     listAddNodeTail(server.slaves,c);
 
+    /* Create the replication backlog if needed. */
+    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL) {
+        /* When we create the backlog from scratch, we always use a new
+         * replication ID and clear the ID2, since there is no valid
+         * past history. */
+        changeReplicationId();
+        clearReplicationId2();
+        createReplicationBacklog();
+    }
+
     /* CASE 1: BGSAVE is in progress, with disk target. */
     if (server.rdb_child_pid != -1 &&
         server.rdb_child_type == RDB_CHILD_TYPE_DISK)
@@ -685,9 +765,6 @@ void syncCommand(client *c) {
             }
         }
     }
-
-    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
-        createReplicationBacklog();
     return;
 }
 
@@ -735,6 +812,8 @@ void replconfCommand(client *c) {
             /* Ignore capabilities not understood by this master. */
             if (!strcasecmp(c->argv[j+1]->ptr,"eof"))
                 c->slave_capa |= SLAVE_CAPA_EOF;
+            else if (!strcasecmp(c->argv[j+1]->ptr,"psync2"))
+                c->slave_capa |= SLAVE_CAPA_PSYNC2;
         } else if (!strcasecmp(c->argv[j]->ptr,"ack")) {
             /* REPLCONF ACK is used by slave to inform the master the amount
              * of replication stream that it processed so far. It is an
@@ -928,6 +1007,43 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     if (startbgsave) startBgsaveForReplication(mincapa);
 }
 
+/* Change the current instance replication ID with a new, random one.
+ * This will prevent successful PSYNCs between this master and other
+ * slaves, so the command should be called when something happens that
+ * alters the current story of the dataset. */
+void changeReplicationId(void) {
+    getRandomHexChars(server.replid,CONFIG_RUN_ID_SIZE);
+    server.replid[CONFIG_RUN_ID_SIZE] = '\0';
+}
+
+/* Clear (invalidate) the secondary replication ID. This happens, for
+ * example, after a full resynchronization, when we start a new replication
+ * history. */
+void clearReplicationId2(void) {
+    memset(server.replid2,'0',sizeof(server.replid));
+    server.replid2[CONFIG_RUN_ID_SIZE] = '\0';
+    server.second_replid_offset = -1;
+}
+
+/* Use the current replication ID / offset as secondary replication
+ * ID, and change the current one in order to start a new history.
+ * This should be used when an instance is switched from slave to master
+ * so that it can serve PSYNC requests performed using the master
+ * replication ID. */
+void shiftReplicationId(void) {
+    memcpy(server.replid2,server.replid,sizeof(server.replid));
+    /* We set the second replid offset to the master offset + 1, since
+     * the slave will ask for the first byte it has not yet received, so
+     * we need to add one to the offset: for example if, as a slave, we are
+     * sure we have the same history as the master for 50 bytes, after we
+     * are turned into a master, we can accept a PSYNC request with offset
+     * 51, since the slave asking has the same history up to the 50th
+     * byte, and is asking for the new bytes starting at offset 51. */
+    server.second_replid_offset = server.master_repl_offset+1;
+    changeReplicationId();
+    serverLog(LL_WARNING,"Setting secondary replication ID to %s, valid up to offset: %lld. New replication ID is %s", server.replid2, server.second_replid_offset, server.replid);
+}
+
 /* ----------------------------------- SLAVE -------------------------------- */
 
 /* Returns 1 if the given replication state is a handshake state,
@@ -965,18 +1081,18 @@ void replicationEmptyDbCallback(void *privdata) {
 /* Once we have a link with the master and the synchroniziation was
  * performed, this function materializes the master client we store
  * at server.master, starting from the specified file descriptor. */
-void replicationCreateMasterClient(int fd) {
+void replicationCreateMasterClient(int fd, int dbid) {
     server.master = createClient(fd);
     server.master->flags |= CLIENT_MASTER;
     server.master->authenticated = 1;
-    server.repl_state = REPL_STATE_CONNECTED;
-    server.master->reploff = server.repl_master_initial_offset;
-    memcpy(server.master->replrunid, server.repl_master_runid,
-        sizeof(server.repl_master_runid));
+    server.master->reploff = server.master_initial_offset;
+    memcpy(server.master->replid, server.master_replid,
+        sizeof(server.master_replid));
     /* If master offset is set to -1, this master is old and is not
      * PSYNC capable, so we flag it accordingly. */
     if (server.master->reploff == -1)
         server.master->flags |= CLIENT_PRE_PSYNC;
+    if (dbid != -1) selectDb(server.master,dbid);
 }
 
 /* Asynchronously read the SYNC payload we receive from a master */
@@ -1137,15 +1253,29 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
-        if (rdbLoad(server.rdb_filename) != C_OK) {
+        rdbSaveInfo rsi = RDB_SAVE_INFO_INIT;
+        if (rdbLoad(server.rdb_filename,&rsi) != C_OK) {
             serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             cancelReplicationHandshake();
             return;
         }
         /* Final setup of the connected slave <- master link */
         zfree(server.repl_transfer_tmpfile);
         close(server.repl_transfer_fd);
-        replicationCreateMasterClient(server.repl_transfer_s);
+        replicationCreateMasterClient(server.repl_transfer_s,rsi.repl_stream_db);
+        server.repl_state = REPL_STATE_CONNECTED;
+        /* After a full resynchroniziation we use the replication ID and
+         * offset of the master. The secondary ID / offset are cleared since
+         * we are starting a new history. */
+        memcpy(server.replid,server.master->replid,sizeof(server.replid));
+        server.master_repl_offset = server.master->reploff;
+        clearReplicationId2();
+        /* Let's create the replication backlog if needed. Slaves need to
+         * accumulate the backlog regardless of the fact they have sub-slaves
+         * or not, in order to behave correctly if they are promoted to
+         * masters after a failover. */
+        if (server.repl_backlog == NULL) createReplicationBacklog();
+
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
@@ -1270,7 +1400,7 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
  *
  * 1) As a side effect of the function call the function removes the readable
  *    event handler from "fd", unless the return value is PSYNC_WAIT_REPLY.
- * 2) server.repl_master_initial_offset is set to the right value according
+ * 2) server.master_initial_offset is set to the right value according
  *    to the master reply. This will be used to populate the 'server.master'
  *    structure replication offset.
  */
@@ -1281,31 +1411,31 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
 #define PSYNC_FULLRESYNC 3
 #define PSYNC_NOT_SUPPORTED 4
 int slaveTryPartialResynchronization(int fd, int read_reply) {
-    char *psync_runid;
+    char *psync_replid;
     char psync_offset[32];
     sds reply;
 
     /* Writing half */
     if (!read_reply) {
-        /* Initially set repl_master_initial_offset to -1 to mark the current
+        /* Initially set master_initial_offset to -1 to mark the current
          * master run_id and offset as not valid. Later if we'll be able to do
          * a FULL resync using the PSYNC command we'll set the offset at the
          * right value, so that this information will be propagated to the
          * client structure representing the master into server.master. */
-        server.repl_master_initial_offset = -1;
+        server.master_initial_offset = -1;
 
         if (server.cached_master) {
-            psync_runid = server.cached_master->replrunid;
+            psync_replid = server.cached_master->replid;
             snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
-            serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+            serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_replid, psync_offset);
         } else {
             serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
-            psync_runid = "?";
+            psync_replid = "?";
             memcpy(psync_offset,"-1",3);
         }
 
         /* Issue the PSYNC command */
-        reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_runid,psync_offset,NULL);
+        reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_replid,psync_offset,NULL);
         if (reply != NULL) {
             serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
             sdsfree(reply);
@@ -1327,31 +1457,31 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
     aeDeleteFileEvent(server.el,fd,AE_READABLE);
 
     if (!strncmp(reply,"+FULLRESYNC",11)) {
-        char *runid = NULL, *offset = NULL;
+        char *replid = NULL, *offset = NULL;
 
         /* FULL RESYNC, parse the reply in order to extract the run id
          * and the replication offset. */
-        runid = strchr(reply,' ');
-        if (runid) {
-            runid++;
-            offset = strchr(runid,' ');
+        replid = strchr(reply,' ');
+        if (replid) {
+            replid++;
+            offset = strchr(replid,' ');
             if (offset) offset++;
         }
-        if (!runid || !offset || (offset-runid-1) != CONFIG_RUN_ID_SIZE) {
+        if (!replid || !offset || (offset-replid-1) != CONFIG_RUN_ID_SIZE) {
             serverLog(LL_WARNING,
                 "Master replied with wrong +FULLRESYNC syntax.");
             /* This is an unexpected condition, actually the +FULLRESYNC
              * reply means that the master supports PSYNC, but the reply
              * format seems wrong. To stay safe we blank the master
-             * runid to make sure next PSYNCs will fail. */
-            memset(server.repl_master_runid,0,CONFIG_RUN_ID_SIZE+1);
+             * replid to make sure next PSYNCs will fail. */
+            memset(server.master_replid,0,CONFIG_RUN_ID_SIZE+1);
         } else {
-            memcpy(server.repl_master_runid, runid, offset-runid-1);
-            server.repl_master_runid[CONFIG_RUN_ID_SIZE] = '\0';
-            server.repl_master_initial_offset = strtoll(offset,NULL,10);
+            memcpy(server.master_replid, replid, offset-replid-1);
+            server.master_replid[CONFIG_RUN_ID_SIZE] = '\0';
+            server.master_initial_offset = strtoll(offset,NULL,10);
             serverLog(LL_NOTICE,"Full resync from master: %s:%lld",
-                server.repl_master_runid,
-                server.repl_master_initial_offset);
+                server.master_replid,
+                server.master_initial_offset);
         }
         /* We are going to full resync, discard the cached master structure. */
         replicationDiscardCachedMaster();
@@ -1360,9 +1490,40 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
     }
 
     if (!strncmp(reply,"+CONTINUE",9)) {
-        /* Partial resync was accepted, set the replication state accordingly */
+        /* Partial resync was accepted. */
         serverLog(LL_NOTICE,
             "Successful partial resynchronization with master.");
+
+        /* Check the new replication ID advertised by the master. If it
+         * changed, we need to set the new ID as primary ID, and set or
+         * secondary ID as the old master ID up to the current offset, so
+         * that our sub-slaves will be able to PSYNC with us after a
+         * disconnection. */
+        char *start = reply+10;
+        char *end = reply+9;
+        while(end[0] != '\r' && end[0] != '\n' && end[0] != '\0') end++;
+        if (end-start == CONFIG_RUN_ID_SIZE) {
+            char new[CONFIG_RUN_ID_SIZE+1];
+            memcpy(new,start,CONFIG_RUN_ID_SIZE);
+            new[CONFIG_RUN_ID_SIZE] = '\0';
+
+            if (strcmp(new,server.cached_master->replid)) {
+                /* Master ID changed. */
+                serverLog(LL_WARNING,"Master replication ID changed to %s",new);
+
+                /* Set the old ID as our ID2, up to the current offset+1. */
+                memcpy(server.replid2,server.cached_master->replid,
+                    sizeof(server.replid2));
+                server.second_replid_offset = server.master_repl_offset+1;
+
+                /* Update the cached master ID and our own primary ID to the
+                 * new one. */
+                memcpy(server.replid,new,sizeof(server.replid));
+                memcpy(server.cached_master->replid,new,sizeof(server.replid));
+            }
+        }
+
+        /* Setup the replication to continue. */
         sdsfree(reply);
         replicationResurrectCachedMaster(fd);
         return PSYNC_CONTINUE;
@@ -1386,6 +1547,8 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
     return PSYNC_NOT_SUPPORTED;
 }
 
+/* This handler fires when the non blocking connect was able to
+ * establish a connection with the master. */
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     char tmpfile[256], *err = NULL;
     int dfd, maxtries = 5;
@@ -1402,7 +1565,8 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
 
-    /* Check for errors in the socket. */
+    /* Check for errors in the socket: after a non blocking connect() we
+     * may find that the socket is in error state. */
     if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
         sockerr = errno;
     if (sockerr) {
@@ -1531,13 +1695,15 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.repl_state = REPL_STATE_SEND_CAPA;
     }
 
-    /* Inform the master of our capabilities. While we currently send
-     * just one capability, it is possible to chain new capabilities here
-     * in the form of REPLCONF capa X capa Y capa Z ...
+    /* Inform the master of our (slave) capabilities.
+     *
+     * EOF: supports EOF-style RDB transfer for diskless replication.
+     * PSYNC2: supports PSYNC v2, so understands +CONTINUE <new repl ID>.
+     *
      * The master will ignore capabilities it does not understand. */
     if (server.repl_state == REPL_STATE_SEND_CAPA) {
         err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"REPLCONF",
-                "capa","eof",NULL);
+                "capa","eof","capa","psync2",NULL);
         if (err) goto write_error;
         sdsfree(err);
         server.repl_state = REPL_STATE_RECEIVE_CAPA;
@@ -1591,14 +1757,14 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     /* PSYNC failed or is not supported: we want our slaves to resync with us
-     * as well, if we have any (chained replication case). The mater may
-     * transfer us an entirely different data set and we have no way to
-     * incrementally feed our slaves after that. */
+     * as well, if we have any sub-slaves. The mater may transfer us an
+     * entirely different data set and we have no way to incrementally feed
+     * our slaves after that. */
     disconnectSlaves(); /* Force our slaves to resync with us as well. */
     freeReplicationBacklog(); /* Don't allow our chained slaves to PSYNC. */
 
     /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
-     * and the server.repl_master_runid and repl_master_initial_offset are
+     * and the server.master_replid and master_initial_offset are
      * already populated. */
     if (psync_result == PSYNC_NOT_SUPPORTED) {
         serverLog(LL_NOTICE,"Retrying with SYNC...");
@@ -1727,15 +1893,23 @@ int cancelReplicationHandshake(void) {
 
 /* Set replication to the specified master address and port. */
 void replicationSetMaster(char *ip, int port) {
+    int was_master = server.masterhost == NULL;
+
     sdsfree(server.masterhost);
     server.masterhost = sdsnew(ip);
     server.masterport = port;
-    if (server.master) freeClient(server.master);
+    if (server.master) {
+        freeClient(server.master);
+    }
     disconnectAllBlockedClients(); /* Clients blocked in master, now slave. */
-    disconnectSlaves(); /* Force our slaves to resync with us as well. */
-    replicationDiscardCachedMaster(); /* Don't try a PSYNC. */
-    freeReplicationBacklog(); /* Don't allow our chained slaves to PSYNC. */
+
+    /* Force our slaves to resync with us as well. They may hopefully be able
+     * to partially resync with us, but we can notify the replid change. */
+    disconnectSlaves();
     cancelReplicationHandshake();
+    /* Before destroying our master state, create a cached master using
+     * our own parameters, to later PSYNC with the new master. */
+    if (was_master) replicationCacheMasterUsingMyself();
     server.repl_state = REPL_STATE_CONNECT;
     server.master_repl_offset = 0;
     server.repl_down_since = 0;
@@ -1746,20 +1920,26 @@ void replicationUnsetMaster(void) {
     if (server.masterhost == NULL) return; /* Nothing to do. */
     sdsfree(server.masterhost);
     server.masterhost = NULL;
-    if (server.master) {
-        if (listLength(server.slaves) == 0) {
-            /* If this instance is turned into a master and there are no
-             * slaves, it inherits the replication offset from the master.
-             * Under certain conditions this makes replicas comparable by
-             * replication offset to understand what is the most updated. */
-            server.master_repl_offset = server.master->reploff;
-            freeReplicationBacklog();
-        }
-        freeClient(server.master);
-    }
+    /* When a slave is turned into a master, the current replication ID
+     * (that was inherited from the master at synchronization time) is
+     * used as secondary ID up to the current offset, and a new replication
+     * ID is created to continue with a new replication history. */
+    shiftReplicationId();
+    if (server.master) freeClient(server.master);
     replicationDiscardCachedMaster();
     cancelReplicationHandshake();
+    /* Disconnecting all the slaves is required: we need to inform slaves
+     * of the replication ID change (see shiftReplicationId() call). However
+     * the slaves will be able to partially resync with us, so it will be
+     * a very fast reconnection. */
+    disconnectSlaves();
     server.repl_state = REPL_STATE_NONE;
+
+    /* We need to make sure the new master will start the replication stream
+     * with a SELECT statement. This is forced after a full resync, but
+     * with PSYNC version 2, there is no need for full resync after a
+     * master switch. */
+    server.slaveseldb = -1;
 }
 
 /* This function is called when the slave lose the connection with the
@@ -1931,6 +2111,31 @@ void replicationCacheMaster(client *c) {
     replicationHandleMasterDisconnection();
 }
 
+/* This function is called when a master is turend into a slave, in order to
+ * create from scratch a cached master for the new client, that will allow
+ * to PSYNC with the slave that was promoted as the new master after a
+ * failover.
+ *
+ * Assuming this instance was previously the master instance of the new master,
+ * the new master will accept its replication ID, and potentiall also the
+ * current offset if no data was lost during the failover. So we use our
+ * current replication ID and offset in order to synthesize a cached master. */
+void replicationCacheMasterUsingMyself(void) {
+    /* The master client we create can be set to any DBID, because
+     * the new master will start its replication stream with SELECT. */
+    server.master_initial_offset = server.master_repl_offset;
+    replicationCreateMasterClient(-1,-1);
+
+    /* Use our own ID / offset. */
+    memcpy(server.master->replid, server.replid, sizeof(server.replid));
+
+    /* Set as cached master. */
+    unlinkClient(server.master);
+    server.cached_master = server.master;
+    server.master = NULL;
+    serverLog(LL_NOTICE,"Before turning into a slave, using my master parameters to synthesize a cached master: I may be able to synchronize with the new master with just a partial transfer.");
+}
+
 /* Free a cached master, called when there are no longer the conditions for
  * a partial resync on reconnection. */
 void replicationDiscardCachedMaster(void) {
@@ -2290,7 +2495,9 @@ void replicationCron(void) {
     robj *ping_argv[1];
 
     /* First, send PING according to ping_slave_period. */
-    if ((replication_cron_loops % server.repl_ping_slave_period) == 0) {
+    if ((replication_cron_loops % server.repl_ping_slave_period) == 0 &&
+        listLength(server.slaves))
+    {
         ping_argv[0] = createStringObject("PING",4);
         replicationFeedSlaves(server.slaves, server.slaveseldb,
             ping_argv, 1);
@@ -2299,20 +2506,32 @@ void replicationCron(void) {
 
     /* Second, send a newline to all the slaves in pre-synchronization
      * stage, that is, slaves waiting for the master to create the RDB file.
+     *
+     * Also send the a newline to all the chained slaves we have, if we lost
+     * connection from our master, to keep the slaves aware that their
+     * master is online. This is needed since sub-slaves only receive proxied
+     * data from top-level masters, so there is no explicit pinging in order
+     * to avoid altering the replication offsets. This special out of band
+     * pings (newlines) can be sent, they will have no effect in the offset.
+     *
      * The newline will be ignored by the slave but will refresh the
-     * last-io timer preventing a timeout. In this case we ignore the
+     * last interaction timer preventing a timeout. In this case we ignore the
      * ping period and refresh the connection once per second since certain
      * timeouts are set at a few seconds (example: PSYNC response). */
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
         client *slave = ln->value;
 
-        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START ||
+        int is_presync =
+            (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START ||
             (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END &&
-             server.rdb_child_type != RDB_CHILD_TYPE_SOCKET))
-        {
+             server.rdb_child_type != RDB_CHILD_TYPE_SOCKET));
+        int is_subslave = server.masterhost && server.master == NULL &&
+                          slave->replstate == SLAVE_STATE_ONLINE;
+
+        if (is_presync || is_subslave) {
             if (write(slave->fd, "\n", 1) == -1) {
-                /* Don't worry, it's just a ping. */
+                /* Don't worry about socket errors, it's just a ping. */
             }
         }
     }
@@ -2337,10 +2556,14 @@ void replicationCron(void) {
         }
     }
 
-    /* If we have no attached slaves and there is a replication backlog
-     * using memory, free it after some (configured) time. */
+    /* If this is a master without attached slaves and there is a replication
+     * backlog active, in order to reclaim memory we can free it after some
+     * (configured) time. Note that this cannot be done for slaves: slaves
+     * without sub-slaves attached should still accumulate data into the
+     * backlog, in order to reply to PSYNC queries if they are turned into
+     * masters after a failover. */
     if (listLength(server.slaves) == 0 && server.repl_backlog_time_limit &&
-        server.repl_backlog)
+        server.repl_backlog && server.masterhost == NULL)
     {
         time_t idle = server.unixtime - server.repl_no_slaves_since;
 