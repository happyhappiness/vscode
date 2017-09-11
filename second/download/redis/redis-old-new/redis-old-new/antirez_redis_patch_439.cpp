@@ -49,8 +49,8 @@ void putSlaveOnline(client *slave);
  * IP address and it's listening port which is more clear for the user, for
  * example: "Closing connection with slave 10.1.2.3:6380". */
 char *replicationGetSlaveName(client *c) {
-    static char buf[REDIS_PEER_ID_LEN];
-    char ip[REDIS_IP_STR_LEN];
+    static char buf[NET_PEER_ID_LEN];
+    char ip[NET_IP_STR_LEN];
 
     ip[0] = '\0';
     buf[0] = '\0';
@@ -92,8 +92,8 @@ void createReplicationBacklog(void) {
  * the most recent bytes, or the same data and more free space in case the
  * buffer is enlarged). */
 void resizeReplicationBacklog(long long newsize) {
-    if (newsize < REDIS_REPL_BACKLOG_MIN_SIZE)
-        newsize = REDIS_REPL_BACKLOG_MIN_SIZE;
+    if (newsize < CONFIG_REPL_BACKLOG_MIN_SIZE)
+        newsize = CONFIG_REPL_BACKLOG_MIN_SIZE;
     if (server.repl_backlog_size == newsize) return;
 
     server.repl_backlog_size = newsize;
@@ -150,7 +150,7 @@ void feedReplicationBacklog(void *ptr, size_t len) {
 /* Wrapper for feedReplicationBacklog() that takes Redis string objects
  * as input. */
 void feedReplicationBacklogWithObject(robj *o) {
-    char llstr[REDIS_LONGSTR_SIZE];
+    char llstr[LONG_STR_SIZE];
     void *p;
     size_t len;
 
@@ -168,7 +168,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
     int j, len;
-    char llstr[REDIS_LONGSTR_SIZE];
+    char llstr[LONG_STR_SIZE];
 
     /* If there aren't slaves, and there is no backlog buffer to populate,
      * we can return ASAP. */
@@ -182,7 +182,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
         robj *selectcmd;
 
         /* For a few DBs we have pre-computed SELECT command. */
-        if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
+        if (dictid >= 0 && dictid < PROTO_SHARED_SELECT_CMDS) {
             selectcmd = shared.select[dictid];
         } else {
             int dictid_len;
@@ -204,14 +204,14 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
             addReply(slave,selectcmd);
         }
 
-        if (dictid < 0 || dictid >= REDIS_SHARED_SELECT_CMDS)
+        if (dictid < 0 || dictid >= PROTO_SHARED_SELECT_CMDS)
             decrRefCount(selectcmd);
     }
     server.slaveseldb = dictid;
 
     /* Write the command to the replication backlog if any. */
     if (server.repl_backlog) {
-        char aux[REDIS_LONGSTR_SIZE+3];
+        char aux[LONG_STR_SIZE+3];
 
         /* Add the multi bulk reply length. */
         aux[0] = '*';
@@ -242,7 +242,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
         client *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) continue;
 
         /* Feed slaves that are waiting for the initial SYNC (so these commands
          * are queued in the output buffer until the initial SYNC completes),
@@ -268,9 +268,9 @@ void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv,
 
     gettimeofday(&tv,NULL);
     cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
-    if (c->flags & REDIS_LUA_CLIENT) {
+    if (c->flags & CLIENT_LUA) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d lua] ",dictid);
-    } else if (c->flags & REDIS_UNIX_SOCKET) {
+    } else if (c->flags & CLIENT_UNIX_SOCKET) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
     } else {
         cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,getClientPeerId(c));
@@ -302,46 +302,46 @@ void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv,
 long long addReplyReplicationBacklog(client *c, long long offset) {
     long long j, skip, len;
 
-    serverLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
+    serverLog(LL_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
 
     if (server.repl_backlog_histlen == 0) {
-        serverLog(REDIS_DEBUG, "[PSYNC] Backlog history len is zero");
+        serverLog(LL_DEBUG, "[PSYNC] Backlog history len is zero");
         return 0;
     }
 
-    serverLog(REDIS_DEBUG, "[PSYNC] Backlog size: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] Backlog size: %lld",
              server.repl_backlog_size);
-    serverLog(REDIS_DEBUG, "[PSYNC] First byte: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] First byte: %lld",
              server.repl_backlog_off);
-    serverLog(REDIS_DEBUG, "[PSYNC] History len: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] History len: %lld",
              server.repl_backlog_histlen);
-    serverLog(REDIS_DEBUG, "[PSYNC] Current index: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] Current index: %lld",
              server.repl_backlog_idx);
 
     /* Compute the amount of bytes we need to discard. */
     skip = offset - server.repl_backlog_off;
-    serverLog(REDIS_DEBUG, "[PSYNC] Skipping: %lld", skip);
+    serverLog(LL_DEBUG, "[PSYNC] Skipping: %lld", skip);
 
     /* Point j to the oldest byte, that is actaully our
      * server.repl_backlog_off byte. */
     j = (server.repl_backlog_idx +
         (server.repl_backlog_size-server.repl_backlog_histlen)) %
         server.repl_backlog_size;
-    serverLog(REDIS_DEBUG, "[PSYNC] Index of first byte: %lld", j);
+    serverLog(LL_DEBUG, "[PSYNC] Index of first byte: %lld", j);
 
     /* Discard the amount of data to seek to the specified 'offset'. */
     j = (j + skip) % server.repl_backlog_size;
 
     /* Feed slave with data. Since it is a circular buffer we have to
      * split the reply in two parts if we are cross-boundary. */
     len = server.repl_backlog_histlen - skip;
-    serverLog(REDIS_DEBUG, "[PSYNC] Reply total length: %lld", len);
+    serverLog(LL_DEBUG, "[PSYNC] Reply total length: %lld", len);
     while(len) {
         long long thislen =
             ((server.repl_backlog_size - j) < len) ?
             (server.repl_backlog_size - j) : len;
 
-        serverLog(REDIS_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
+        serverLog(LL_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
         addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
         len -= thislen;
         j = 0;
@@ -366,11 +366,11 @@ int masterTryPartialResynchronization(client *c) {
     if (strcasecmp(master_runid, server.runid)) {
         /* Run id "?" is used by slaves that want to force a full resync. */
         if (master_runid[0] != '?') {
-            serverLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
+            serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                 "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
                 master_runid, server.runid);
         } else {
-            serverLog(REDIS_NOTICE,"Full resync requested by slave %s",
+            serverLog(LL_NOTICE,"Full resync requested by slave %s",
                 replicationGetSlaveName(c));
         }
         goto need_full_resync;
@@ -383,10 +383,10 @@ int masterTryPartialResynchronization(client *c) {
         psync_offset < server.repl_backlog_off ||
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
     {
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Unable to partial resync with slave %s for lack of backlog (Slave request was: %lld).", replicationGetSlaveName(c), psync_offset);
         if (psync_offset > server.master_repl_offset) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Warning: slave %s tried to PSYNC with an offset that is greater than the master replication offset.", replicationGetSlaveName(c));
         }
         goto need_full_resync;
@@ -396,8 +396,8 @@ int masterTryPartialResynchronization(client *c) {
      * 1) Set client state to make it a slave.
      * 2) Inform the client we can continue with +CONTINUE
      * 3) Send the backlog data (from the offset to the end) to the slave. */
-    c->flags |= REDIS_SLAVE;
-    c->replstate = REDIS_REPL_ONLINE;
+    c->flags |= CLIENT_SLAVE;
+    c->replstate = SLAVE_STATE_ONLINE;
     c->repl_ack_time = server.unixtime;
     c->repl_put_online_on_ack = 0;
     listAddNodeTail(server.slaves,c);
@@ -410,7 +410,7 @@ int masterTryPartialResynchronization(client *c) {
         return C_OK;
     }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
-    serverLog(REDIS_NOTICE,
+    serverLog(LL_NOTICE,
         "Partial resynchronization request from %s accepted. Sending %lld bytes of backlog starting from offset %lld.",
             replicationGetSlaveName(c),
             psync_len, psync_offset);
@@ -445,7 +445,7 @@ int masterTryPartialResynchronization(client *c) {
 int startBgsaveForReplication(void) {
     int retval;
 
-    serverLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
+    serverLog(LL_NOTICE,"Starting BGSAVE for SYNC with target: %s",
         server.repl_diskless_sync ? "slaves sockets" : "disk");
 
     if (server.repl_diskless_sync)
@@ -462,11 +462,11 @@ int startBgsaveForReplication(void) {
 /* SYNC and PSYNC command implemenation. */
 void syncCommand(client *c) {
     /* ignore SYNC if already slave or in monitor mode */
-    if (c->flags & REDIS_SLAVE) return;
+    if (c->flags & CLIENT_SLAVE) return;
 
     /* Refuse SYNC requests if we are a slave but the link with our master
      * is not ok... */
-    if (server.masterhost && server.repl_state != REDIS_REPL_CONNECTED) {
+    if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED) {
         addReplyError(c,"Can't SYNC while not connected with my master");
         return;
     }
@@ -480,7 +480,7 @@ void syncCommand(client *c) {
         return;
     }
 
-    serverLog(REDIS_NOTICE,"Slave %s asks for synchronization",
+    serverLog(LL_NOTICE,"Slave %s asks for synchronization",
         replicationGetSlaveName(c));
 
     /* Try a partial resynchronization if this is a PSYNC command.
@@ -509,7 +509,7 @@ void syncCommand(client *c) {
         /* If a slave uses SYNC, we are dealing with an old implementation
          * of the replication protocol (like redis-cli --slave). Flag the client
          * so that we don't expect to receive REPLCONF ACK feedbacks. */
-        c->flags |= REDIS_PRE_PSYNC;
+        c->flags |= CLIENT_PRE_PSYNC;
     }
 
     /* Full resynchronization. */
@@ -518,7 +518,7 @@ void syncCommand(client *c) {
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
     if (server.rdb_child_pid != -1 &&
-        server.rdb_child_type == REDIS_RDB_CHILD_TYPE_DISK)
+        server.rdb_child_type == RDB_CHILD_TYPE_DISK)
     {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
@@ -530,51 +530,51 @@ void syncCommand(client *c) {
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
             slave = ln->value;
-            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) break;
+            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) break;
         }
         if (ln) {
             /* Perfect, the server is already registering differences for
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
-            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-            serverLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
+            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+            serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
-            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
-            serverLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
+            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
+            serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
     } else if (server.rdb_child_pid != -1 &&
-               server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
+               server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
     {
         /* There is an RDB child process but it is writing directly to
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
-        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
-        serverLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
+        c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
+        serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
     } else {
         if (server.repl_diskless_sync) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
-            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+            c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
             if (server.repl_diskless_sync_delay)
-                serverLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
+                serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
             /* Ok we don't have a BGSAVE in progress, let's start one. */
             if (startBgsaveForReplication() != C_OK) {
-                serverLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");
                 return;
             }
-            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
         }
     }
 
     if (server.repl_disable_tcp_nodelay)
         anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
     c->repldbfd = -1;
-    c->flags |= REDIS_SLAVE;
+    c->flags |= CLIENT_SLAVE;
     server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
     listAddNodeTail(server.slaves,c);
     if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
@@ -619,7 +619,7 @@ void replconfCommand(client *c) {
              * internal only command that normal clients should never use. */
             long long offset;
 
-            if (!(c->flags & REDIS_SLAVE)) return;
+            if (!(c->flags & CLIENT_SLAVE)) return;
             if ((getLongLongFromObject(c->argv[j+1], &offset) != C_OK))
                 return;
             if (offset > c->repl_ack_off)
@@ -628,7 +628,7 @@ void replconfCommand(client *c) {
             /* If this was a diskless replication, we need to really put
              * the slave online when the first ACK is received (which
              * confirms slave is online and ready to get more data). */
-            if (c->repl_put_online_on_ack && c->replstate == REDIS_REPL_ONLINE)
+            if (c->repl_put_online_on_ack && c->replstate == SLAVE_STATE_ONLINE)
                 putSlaveOnline(c);
             /* Note: this command does not reply anything! */
             return;
@@ -659,25 +659,25 @@ void replconfCommand(client *c) {
  *    sending it to the slave.
  * 3) Update the count of good slaves. */
 void putSlaveOnline(client *slave) {
-    slave->replstate = REDIS_REPL_ONLINE;
+    slave->replstate = SLAVE_STATE_ONLINE;
     slave->repl_put_online_on_ack = 0;
     slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
     if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
         sendReplyToClient, slave) == AE_ERR) {
-        serverLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
+        serverLog(LL_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
         freeClient(slave);
         return;
     }
     refreshGoodSlavesCount();
-    serverLog(REDIS_NOTICE,"Synchronization with slave %s succeeded",
+    serverLog(LL_NOTICE,"Synchronization with slave %s succeeded",
         replicationGetSlaveName(slave));
 }
 
 void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     client *slave = privdata;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
-    char buf[REDIS_IOBUF_LEN];
+    UNUSED(el);
+    UNUSED(mask);
+    char buf[PROTO_IOBUF_LEN];
     ssize_t nwritten, buflen;
 
     /* Before sending the RDB file, we send the preamble as configured by the
@@ -686,7 +686,7 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (slave->replpreamble) {
         nwritten = write(fd,slave->replpreamble,sdslen(slave->replpreamble));
         if (nwritten == -1) {
-            serverLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
+            serverLog(LL_VERBOSE,"Write error sending RDB preamble to slave: %s",
                 strerror(errno));
             freeClient(slave);
             return;
@@ -704,16 +704,16 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     /* If the preamble was already transfered, send the RDB bulk data. */
     lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
-    buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
+    buflen = read(slave->repldbfd,buf,PROTO_IOBUF_LEN);
     if (buflen <= 0) {
-        serverLog(REDIS_WARNING,"Read error sending DB to slave: %s",
+        serverLog(LL_WARNING,"Read error sending DB to slave: %s",
             (buflen == 0) ? "premature EOF" : strerror(errno));
         freeClient(slave);
         return;
     }
     if ((nwritten = write(fd,buf,buflen)) == -1) {
         if (errno != EAGAIN) {
-            serverLog(REDIS_WARNING,"Write error sending DB to slave: %s",
+            serverLog(LL_WARNING,"Write error sending DB to slave: %s",
                 strerror(errno));
             freeClient(slave);
         }
@@ -752,44 +752,44 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     while((ln = listNext(&li))) {
         client *slave = ln->value;
 
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+        if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             startbgsave = 1;
-            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-        } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+            slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+        } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
             /* If this was an RDB on disk save, we have to prepare to send
              * the RDB from disk to the slave socket. Otherwise if this was
              * already an RDB -> Slaves socket transfer, used in the case of
              * diskless replication, our work is trivial, we can just put
              * the slave online. */
-            if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
-                serverLog(REDIS_NOTICE,
+            if (type == RDB_CHILD_TYPE_SOCKET) {
+                serverLog(LL_NOTICE,
                     "Streamed RDB transfer with slave %s succeeded (socket). Waiting for REPLCONF ACK from slave to enable streaming",
                         replicationGetSlaveName(slave));
                 /* Note: we wait for a REPLCONF ACK message from slave in
                  * order to really put it online (install the write handler
                  * so that the accumulated data can be transfered). However
                  * we change the replication state ASAP, since our slave
                  * is technically online now. */
-                slave->replstate = REDIS_REPL_ONLINE;
+                slave->replstate = SLAVE_STATE_ONLINE;
                 slave->repl_put_online_on_ack = 1;
                 slave->repl_ack_time = server.unixtime; /* Timeout otherwise. */
             } else {
                 if (bgsaveerr != C_OK) {
                     freeClient(slave);
-                    serverLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                    serverLog(LL_WARNING,"SYNC failed. BGSAVE child returned an error");
                     continue;
                 }
                 if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                     redis_fstat(slave->repldbfd,&buf) == -1) {
                     freeClient(slave);
-                    serverLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                    serverLog(LL_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                     continue;
                 }
                 slave->repldboff = 0;
                 slave->repldbsize = buf.st_size;
-                slave->replstate = REDIS_REPL_SEND_BULK;
+                slave->replstate = SLAVE_STATE_SEND_BULK;
                 slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
                     (unsigned long long) slave->repldbsize);
 
@@ -806,11 +806,11 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             listIter li;
 
             listRewind(server.slaves,&li);
-            serverLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
+            serverLog(LL_WARNING,"SYNC failed. BGSAVE failed");
             while((ln = listNext(&li))) {
                 client *slave = ln->value;
 
-                if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
+                if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START)
                     freeClient(slave);
             }
         }
@@ -821,14 +821,14 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
 /* Abort the async download of the bulk dataset while SYNC-ing with master */
 void replicationAbortSyncTransfer(void) {
-    serverAssert(server.repl_state == REDIS_REPL_TRANSFER);
+    serverAssert(server.repl_state == REPL_STATE_TRANSFER);
 
     aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
     close(server.repl_transfer_s);
     close(server.repl_transfer_fd);
     unlink(server.repl_transfer_tmpfile);
     zfree(server.repl_transfer_tmpfile);
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
 }
 
 /* Avoid the master to detect the slave is timing out while loading the
@@ -852,7 +852,7 @@ void replicationSendNewlineToMaster(void) {
 /* Callback used by emptyDb() while flushing away old data to load
  * the new dataset received by the master. */
 void replicationEmptyDbCallback(void *privdata) {
-    REDIS_NOTUSED(privdata);
+    UNUSED(privdata);
     replicationSendNewlineToMaster();
 }
 
@@ -861,16 +861,16 @@ void replicationEmptyDbCallback(void *privdata) {
  * at server.master, starting from the specified file descriptor. */
 void replicationCreateMasterClient(int fd) {
     server.master = createClient(fd);
-    server.master->flags |= REDIS_MASTER;
+    server.master->flags |= CLIENT_MASTER;
     server.master->authenticated = 1;
-    server.repl_state = REDIS_REPL_CONNECTED;
+    server.repl_state = REPL_STATE_CONNECTED;
     server.master->reploff = server.repl_master_initial_offset;
     memcpy(server.master->replrunid, server.repl_master_runid,
         sizeof(server.repl_master_runid));
     /* If master offset is set to -1, this master is old and is not
      * PSYNC capable, so we flag it accordingly. */
     if (server.master->reploff == -1)
-        server.master->flags |= REDIS_PRE_PSYNC;
+        server.master->flags |= CLIENT_PRE_PSYNC;
 }
 
 /* Asynchronously read the SYNC payload we receive from a master */
@@ -879,28 +879,28 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     char buf[4096];
     ssize_t nread, readlen;
     off_t left;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(privdata);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(privdata);
+    UNUSED(mask);
 
     /* Static vars used to hold the EOF mark, and the last bytes received
      * form the server: when they match, we reached the end of the transfer. */
-    static char eofmark[REDIS_RUN_ID_SIZE];
-    static char lastbytes[REDIS_RUN_ID_SIZE];
+    static char eofmark[CONFIG_RUN_ID_SIZE];
+    static char lastbytes[CONFIG_RUN_ID_SIZE];
     static int usemark = 0;
 
     /* If repl_transfer_size == -1 we still have to read the bulk length
      * from the master reply. */
     if (server.repl_transfer_size == -1) {
         if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
                 strerror(errno));
             goto error;
         }
 
         if (buf[0] == '-') {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "MASTER aborted replication with an error: %s",
                 buf+1);
             goto error;
@@ -911,7 +911,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             server.repl_transfer_lastio = server.unixtime;
             return;
         } else if (buf[0] != '$') {
-            serverLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$' (we received '%s'), are you sure the host and port are right?", buf);
+            serverLog(LL_WARNING,"Bad protocol from MASTER, the first byte is not '$' (we received '%s'), are you sure the host and port are right?", buf);
             goto error;
         }
 
@@ -925,19 +925,19 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
          * At the end of the file the announced delimiter is transmitted. The
          * delimiter is long and random enough that the probability of a
          * collision with the actual file content can be ignored. */
-        if (strncmp(buf+1,"EOF:",4) == 0 && strlen(buf+5) >= REDIS_RUN_ID_SIZE) {
+        if (strncmp(buf+1,"EOF:",4) == 0 && strlen(buf+5) >= CONFIG_RUN_ID_SIZE) {
             usemark = 1;
-            memcpy(eofmark,buf+5,REDIS_RUN_ID_SIZE);
-            memset(lastbytes,0,REDIS_RUN_ID_SIZE);
+            memcpy(eofmark,buf+5,CONFIG_RUN_ID_SIZE);
+            memset(lastbytes,0,CONFIG_RUN_ID_SIZE);
             /* Set any repl_transfer_size to avoid entering this code path
              * at the next call. */
             server.repl_transfer_size = 0;
-            serverLog(REDIS_NOTICE,
+            serverLog(LL_NOTICE,
                 "MASTER <-> SLAVE sync: receiving streamed RDB from master");
         } else {
             usemark = 0;
             server.repl_transfer_size = strtol(buf+1,NULL,10);
-            serverLog(REDIS_NOTICE,
+            serverLog(LL_NOTICE,
                 "MASTER <-> SLAVE sync: receiving %lld bytes from master",
                 (long long) server.repl_transfer_size);
         }
@@ -954,7 +954,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     nread = read(fd,buf,readlen);
     if (nread <= 0) {
-        serverLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
+        serverLog(LL_WARNING,"I/O error trying to sync with MASTER: %s",
             (nread == -1) ? strerror(errno) : "connection lost");
         replicationAbortSyncTransfer();
         return;
@@ -967,29 +967,29 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (usemark) {
         /* Update the last bytes array, and check if it matches our delimiter.*/
-        if (nread >= REDIS_RUN_ID_SIZE) {
-            memcpy(lastbytes,buf+nread-REDIS_RUN_ID_SIZE,REDIS_RUN_ID_SIZE);
+        if (nread >= CONFIG_RUN_ID_SIZE) {
+            memcpy(lastbytes,buf+nread-CONFIG_RUN_ID_SIZE,CONFIG_RUN_ID_SIZE);
         } else {
-            int rem = REDIS_RUN_ID_SIZE-nread;
+            int rem = CONFIG_RUN_ID_SIZE-nread;
             memmove(lastbytes,lastbytes+nread,rem);
             memcpy(lastbytes+rem,buf,nread);
         }
-        if (memcmp(lastbytes,eofmark,REDIS_RUN_ID_SIZE) == 0) eof_reached = 1;
+        if (memcmp(lastbytes,eofmark,CONFIG_RUN_ID_SIZE) == 0) eof_reached = 1;
     }
 
     server.repl_transfer_lastio = server.unixtime;
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
-        serverLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
+        serverLog(LL_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
         goto error;
     }
     server.repl_transfer_read += nread;
 
     /* Delete the last 40 bytes from the file if we reached EOF. */
     if (usemark && eof_reached) {
         if (ftruncate(server.repl_transfer_fd,
-            server.repl_transfer_read - REDIS_RUN_ID_SIZE) == -1)
+            server.repl_transfer_read - CONFIG_RUN_ID_SIZE) == -1)
         {
-            serverLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
+            serverLog(LL_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
             goto error;
         }
     }
@@ -1015,42 +1015,42 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (eof_reached) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
-            serverLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
+            serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             replicationAbortSyncTransfer();
             return;
         }
-        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
         signalFlushedDb(-1);
         emptyDb(replicationEmptyDbCallback);
         /* Before loading the DB into memory we need to delete the readable
          * handler, otherwise it will get called recursively since
          * rdbLoad() will call the event loop to process events from time to
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
-        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
         if (rdbLoad(server.rdb_filename) != C_OK) {
-            serverLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
+            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             replicationAbortSyncTransfer();
             return;
         }
         /* Final setup of the connected slave <- master link */
         zfree(server.repl_transfer_tmpfile);
         close(server.repl_transfer_fd);
         replicationCreateMasterClient(server.repl_transfer_s);
-        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
-        if (server.aof_state != REDIS_AOF_OFF) {
+        if (server.aof_state != AOF_OFF) {
             int retry = 10;
 
             stopAppendOnly();
             while (retry-- && startAppendOnly() == C_ERR) {
-                serverLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
+                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                 sleep(1);
             }
             if (!retry) {
-                serverLog(REDIS_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
+                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                 exit(1);
             }
         }
@@ -1145,9 +1145,9 @@ int slaveTryPartialResynchronization(int fd) {
     if (server.cached_master) {
         psync_runid = server.cached_master->replrunid;
         snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
-        serverLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+        serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
     } else {
-        serverLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
+        serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
         psync_runid = "?";
         memcpy(psync_offset,"-1",3);
     }
@@ -1166,19 +1166,19 @@ int slaveTryPartialResynchronization(int fd) {
             offset = strchr(runid,' ');
             if (offset) offset++;
         }
-        if (!runid || !offset || (offset-runid-1) != REDIS_RUN_ID_SIZE) {
-            serverLog(REDIS_WARNING,
+        if (!runid || !offset || (offset-runid-1) != CONFIG_RUN_ID_SIZE) {
+            serverLog(LL_WARNING,
                 "Master replied with wrong +FULLRESYNC syntax.");
             /* This is an unexpected condition, actually the +FULLRESYNC
              * reply means that the master supports PSYNC, but the reply
              * format seems wrong. To stay safe we blank the master
              * runid to make sure next PSYNCs will fail. */
-            memset(server.repl_master_runid,0,REDIS_RUN_ID_SIZE+1);
+            memset(server.repl_master_runid,0,CONFIG_RUN_ID_SIZE+1);
         } else {
             memcpy(server.repl_master_runid, runid, offset-runid-1);
-            server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
+            server.repl_master_runid[CONFIG_RUN_ID_SIZE] = '\0';
             server.repl_master_initial_offset = strtoll(offset,NULL,10);
-            serverLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
+            serverLog(LL_NOTICE,"Full resync from master: %s:%lld",
                 server.repl_master_runid,
                 server.repl_master_initial_offset);
         }
@@ -1190,7 +1190,7 @@ int slaveTryPartialResynchronization(int fd) {
 
     if (!strncmp(reply,"+CONTINUE",9)) {
         /* Partial resync was accepted, set the replication state accordingly */
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Successful partial resynchronization with master.");
         sdsfree(reply);
         replicationResurrectCachedMaster(fd);
@@ -1203,10 +1203,10 @@ int slaveTryPartialResynchronization(int fd) {
 
     if (strncmp(reply,"-ERR",4)) {
         /* If it's not an error, log the unexpected event. */
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Unexpected reply to PSYNC from master: %s", reply);
     } else {
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Master does not support PSYNC or is in "
             "error state (reply: %s)", reply);
     }
@@ -1220,13 +1220,13 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     int dfd, maxtries = 5;
     int sockerr = 0, psync_result;
     socklen_t errlen = sizeof(sockerr);
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(privdata);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(privdata);
+    UNUSED(mask);
 
     /* If this event fired after the user turned the instance into a master
      * with SLAVEOF NO ONE we must just return ASAP. */
-    if (server.repl_state == REDIS_REPL_NONE) {
+    if (server.repl_state == REPL_STATE_NONE) {
         close(fd);
         return;
     }
@@ -1236,7 +1236,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         sockerr = errno;
     if (sockerr) {
         aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
-        serverLog(REDIS_WARNING,"Error condition on socket for SYNC: %s",
+        serverLog(LL_WARNING,"Error condition on socket for SYNC: %s",
             strerror(sockerr));
         goto error;
     }
@@ -1245,20 +1245,20 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
      * make sure the master is able to reply before going into the actual
      * replication process where we have long timeouts in the order of
      * seconds (in the meantime the slave would block). */
-    if (server.repl_state == REDIS_REPL_CONNECTING) {
-        serverLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
+    if (server.repl_state == REPL_STATE_CONNECTING) {
+        serverLog(LL_NOTICE,"Non blocking connect for SYNC fired the event.");
         /* Delete the writable event so that the readable event remains
          * registered and we can wait for the PONG reply. */
         aeDeleteFileEvent(server.el,fd,AE_WRITABLE);
-        server.repl_state = REDIS_REPL_RECEIVE_PONG;
+        server.repl_state = REPL_STATE_RECEIVE_PONG;
         /* Send the PING, don't check for errors at all, we have the timeout
          * that will take care about this. */
         syncWrite(fd,"PING\r\n",6,100);
         return;
     }
 
     /* Receive the PONG command. */
-    if (server.repl_state == REDIS_REPL_RECEIVE_PONG) {
+    if (server.repl_state == REPL_STATE_RECEIVE_PONG) {
         char buf[1024];
 
         /* Delete the readable event, we no longer need it now that there is
@@ -1270,7 +1270,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (syncReadLine(fd,buf,sizeof(buf),
             server.repl_syncio_timeout*1000) == -1)
         {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "I/O error reading PING reply from master: %s",
                 strerror(errno));
             goto error;
@@ -1285,10 +1285,10 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
             strncmp(buf,"-NOAUTH",7) != 0 &&
             strncmp(buf,"-ERR operation not permitted",28) != 0)
         {
-            serverLog(REDIS_WARNING,"Error reply to PING from master: '%s'",buf);
+            serverLog(LL_WARNING,"Error reply to PING from master: '%s'",buf);
             goto error;
         } else {
-            serverLog(REDIS_NOTICE,
+            serverLog(LL_NOTICE,
                 "Master replied to PING, replication can continue...");
         }
     }
@@ -1297,7 +1297,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     if(server.masterauth) {
         err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
         if (err[0] == '-') {
-            serverLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
+            serverLog(LL_WARNING,"Unable to AUTH to MASTER: %s",err);
             sdsfree(err);
             goto error;
         }
@@ -1314,7 +1314,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF listening-port. */
         if (err[0] == '-') {
-            serverLog(REDIS_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
+            serverLog(LL_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
         }
         sdsfree(err);
     }
@@ -1326,17 +1326,17 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
      * reconnection attempt. */
     psync_result = slaveTryPartialResynchronization(fd);
     if (psync_result == PSYNC_CONTINUE) {
-        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
         return;
     }
 
     /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
      * and the server.repl_master_runid and repl_master_initial_offset are
      * already populated. */
     if (psync_result == PSYNC_NOT_SUPPORTED) {
-        serverLog(REDIS_NOTICE,"Retrying with SYNC...");
+        serverLog(LL_NOTICE,"Retrying with SYNC...");
         if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
-            serverLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
+            serverLog(LL_WARNING,"I/O error writing to MASTER: %s",
                 strerror(errno));
             goto error;
         }
@@ -1351,21 +1351,21 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         sleep(1);
     }
     if (dfd == -1) {
-        serverLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
+        serverLog(LL_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
         goto error;
     }
 
     /* Setup the non blocking download of the bulk file. */
     if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
             == AE_ERR)
     {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Can't create readable event for SYNC: %s (fd=%d)",
             strerror(errno),fd);
         goto error;
     }
 
-    server.repl_state = REDIS_REPL_TRANSFER;
+    server.repl_state = REPL_STATE_TRANSFER;
     server.repl_transfer_size = -1;
     server.repl_transfer_read = 0;
     server.repl_transfer_last_fsync_off = 0;
@@ -1377,17 +1377,17 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
 error:
     close(fd);
     server.repl_transfer_s = -1;
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
     return;
 }
 
 int connectWithMaster(void) {
     int fd;
 
     fd = anetTcpNonBlockBestEffortBindConnect(NULL,
-        server.masterhost,server.masterport,REDIS_BIND_ADDR);
+        server.masterhost,server.masterport,NET_FIRST_BIND_ADDR);
     if (fd == -1) {
-        serverLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
+        serverLog(LL_WARNING,"Unable to connect to MASTER: %s",
             strerror(errno));
         return C_ERR;
     }
@@ -1396,13 +1396,13 @@ int connectWithMaster(void) {
             AE_ERR)
     {
         close(fd);
-        serverLog(REDIS_WARNING,"Can't create readable event for SYNC");
+        serverLog(LL_WARNING,"Can't create readable event for SYNC");
         return C_ERR;
     }
 
     server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_s = fd;
-    server.repl_state = REDIS_REPL_CONNECTING;
+    server.repl_state = REPL_STATE_CONNECTING;
     return C_OK;
 }
 
@@ -1411,27 +1411,27 @@ int connectWithMaster(void) {
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    serverAssert(server.repl_state == REDIS_REPL_CONNECTING ||
-                server.repl_state == REDIS_REPL_RECEIVE_PONG);
+    serverAssert(server.repl_state == REPL_STATE_CONNECTING ||
+                server.repl_state == REPL_STATE_RECEIVE_PONG);
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
 }
 
 /* This function aborts a non blocking replication attempt if there is one
  * in progress, by canceling the non-blocking connect attempt or
  * the initial bulk transfer.
  *
  * If there was a replication handshake in progress 1 is returned and
- * the replication state (server.repl_state) set to REDIS_REPL_CONNECT.
+ * the replication state (server.repl_state) set to REPL_STATE_CONNECT.
  *
  * Otherwise zero is returned and no operation is perforemd at all. */
 int cancelReplicationHandshake(void) {
-    if (server.repl_state == REDIS_REPL_TRANSFER) {
+    if (server.repl_state == REPL_STATE_TRANSFER) {
         replicationAbortSyncTransfer();
-    } else if (server.repl_state == REDIS_REPL_CONNECTING ||
-             server.repl_state == REDIS_REPL_RECEIVE_PONG)
+    } else if (server.repl_state == REPL_STATE_CONNECTING ||
+             server.repl_state == REPL_STATE_RECEIVE_PONG)
     {
         undoConnectWithMaster();
     } else {
@@ -1451,7 +1451,7 @@ void replicationSetMaster(char *ip, int port) {
     replicationDiscardCachedMaster(); /* Don't try a PSYNC. */
     freeReplicationBacklog(); /* Don't allow our chained slaves to PSYNC. */
     cancelReplicationHandshake();
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
     server.master_repl_offset = 0;
     server.repl_down_since = 0;
 }
@@ -1474,7 +1474,7 @@ void replicationUnsetMaster(void) {
     }
     replicationDiscardCachedMaster();
     cancelReplicationHandshake();
-    server.repl_state = REDIS_REPL_NONE;
+    server.repl_state = REPL_STATE_NONE;
 }
 
 void slaveofCommand(client *c) {
@@ -1491,7 +1491,7 @@ void slaveofCommand(client *c) {
         !strcasecmp(c->argv[2]->ptr,"one")) {
         if (server.masterhost) {
             replicationUnsetMaster();
-            serverLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
+            serverLog(LL_NOTICE,"MASTER MODE enabled (user request)");
         }
     } else {
         long port;
@@ -1502,14 +1502,14 @@ void slaveofCommand(client *c) {
         /* Check if we are already attached to the specified slave */
         if (server.masterhost && !strcasecmp(server.masterhost,c->argv[1]->ptr)
             && server.masterport == port) {
-            serverLog(REDIS_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
+            serverLog(LL_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
             addReplySds(c,sdsnew("+OK Already connected to specified master\r\n"));
             return;
         }
         /* There was no previous master or the user specified a different one,
          * we can continue. */
         replicationSetMaster(c->argv[1]->ptr, port);
-        serverLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
+        serverLog(LL_NOTICE,"SLAVE OF %s:%d enabled (user request)",
             server.masterhost, server.masterport);
     }
     addReply(c,shared.ok);
@@ -1532,10 +1532,10 @@ void roleCommand(client *c) {
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
             client *slave = ln->value;
-            char ip[REDIS_IP_STR_LEN];
+            char ip[NET_IP_STR_LEN];
 
             if (anetPeerToString(slave->fd,ip,sizeof(ip),NULL) == -1) continue;
-            if (slave->replstate != REDIS_REPL_ONLINE) continue;
+            if (slave->replstate != SLAVE_STATE_ONLINE) continue;
             addReplyMultiBulkLen(c,3);
             addReplyBulkCString(c,ip);
             addReplyBulkLongLong(c,slave->slave_listening_port);
@@ -1551,12 +1551,12 @@ void roleCommand(client *c) {
         addReplyBulkCString(c,server.masterhost);
         addReplyLongLong(c,server.masterport);
         switch(server.repl_state) {
-        case REDIS_REPL_NONE: slavestate = "none"; break;
-        case REDIS_REPL_CONNECT: slavestate = "connect"; break;
-        case REDIS_REPL_CONNECTING: slavestate = "connecting"; break;
-        case REDIS_REPL_RECEIVE_PONG: /* see next */
-        case REDIS_REPL_TRANSFER: slavestate = "sync"; break;
-        case REDIS_REPL_CONNECTED: slavestate = "connected"; break;
+        case REPL_STATE_NONE: slavestate = "none"; break;
+        case REPL_STATE_CONNECT: slavestate = "connect"; break;
+        case REPL_STATE_CONNECTING: slavestate = "connecting"; break;
+        case REPL_STATE_RECEIVE_PONG: /* see next */
+        case REPL_STATE_TRANSFER: slavestate = "sync"; break;
+        case REPL_STATE_CONNECTED: slavestate = "connected"; break;
         default: slavestate = "unknown"; break;
         }
         addReplyBulkCString(c,slavestate);
@@ -1571,12 +1571,12 @@ void replicationSendAck(void) {
     client *c = server.master;
 
     if (c != NULL) {
-        c->flags |= REDIS_MASTER_FORCE_REPLY;
+        c->flags |= CLIENT_MASTER_FORCE_REPLY;
         addReplyMultiBulkLen(c,3);
         addReplyBulkCString(c,"REPLCONF");
         addReplyBulkCString(c,"ACK");
         addReplyBulkLongLong(c,c->reploff);
-        c->flags &= ~REDIS_MASTER_FORCE_REPLY;
+        c->flags &= ~CLIENT_MASTER_FORCE_REPLY;
     }
 }
 
@@ -1604,7 +1604,7 @@ void replicationCacheMaster(client *c) {
     listNode *ln;
 
     serverAssert(server.master != NULL && server.cached_master == NULL);
-    serverLog(REDIS_NOTICE,"Caching the disconnected master state.");
+    serverLog(LL_NOTICE,"Caching the disconnected master state.");
 
     /* Remove from the list of clients, we don't want this client to be
      * listed by CLIENT LIST or processed in any way by batch operations. */
@@ -1642,8 +1642,8 @@ void replicationCacheMaster(client *c) {
 void replicationDiscardCachedMaster(void) {
     if (server.cached_master == NULL) return;
 
-    serverLog(REDIS_NOTICE,"Discarding previously cached master state.");
-    server.cached_master->flags &= ~REDIS_MASTER;
+    serverLog(LL_NOTICE,"Discarding previously cached master state.");
+    server.cached_master->flags &= ~CLIENT_MASTER;
     freeClient(server.cached_master);
     server.cached_master = NULL;
 }
@@ -1658,16 +1658,16 @@ void replicationResurrectCachedMaster(int newfd) {
     server.master = server.cached_master;
     server.cached_master = NULL;
     server.master->fd = newfd;
-    server.master->flags &= ~(REDIS_CLOSE_AFTER_REPLY|REDIS_CLOSE_ASAP);
+    server.master->flags &= ~(CLIENT_CLOSE_AFTER_REPLY|CLIENT_CLOSE_ASAP);
     server.master->authenticated = 1;
     server.master->lastinteraction = server.unixtime;
-    server.repl_state = REDIS_REPL_CONNECTED;
+    server.repl_state = REPL_STATE_CONNECTED;
 
     /* Re-add to the list of clients. */
     listAddNodeTail(server.clients,server.master);
     if (aeCreateFileEvent(server.el, newfd, AE_READABLE,
                           readQueryFromClient, server.master)) {
-        serverLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
+        serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
         freeClientAsync(server.master); /* Close ASAP. */
     }
 
@@ -1676,7 +1676,7 @@ void replicationResurrectCachedMaster(int newfd) {
     if (server.master->bufpos || listLength(server.master->reply)) {
         if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
                           sendReplyToClient, server.master)) {
-            serverLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
+            serverLog(LL_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
             freeClientAsync(server.master); /* Close ASAP. */
         }
     }
@@ -1700,7 +1700,7 @@ void refreshGoodSlavesCount(void) {
         client *slave = ln->value;
         time_t lag = server.unixtime - slave->repl_ack_time;
 
-        if (slave->replstate == REDIS_REPL_ONLINE &&
+        if (slave->replstate == SLAVE_STATE_ONLINE &&
             lag <= server.repl_min_slaves_max_lag) good++;
     }
     server.repl_good_slaves_count = good;
@@ -1835,7 +1835,7 @@ int replicationCountAcksByOffset(long long offset) {
     while((ln = listNext(&li))) {
         client *slave = ln->value;
 
-        if (slave->replstate != REDIS_REPL_ONLINE) continue;
+        if (slave->replstate != SLAVE_STATE_ONLINE) continue;
         if (slave->repl_ack_off >= offset) count++;
     }
     return count;
@@ -1856,7 +1856,7 @@ void waitCommand(client *c) {
 
     /* First try without blocking at all. */
     ackreplicas = replicationCountAcksByOffset(c->woff);
-    if (ackreplicas >= numreplicas || c->flags & REDIS_MULTI) {
+    if (ackreplicas >= numreplicas || c->flags & CLIENT_MULTI) {
         addReplyLongLong(c,ackreplicas);
         return;
     }
@@ -1867,7 +1867,7 @@ void waitCommand(client *c) {
     c->bpop.reploffset = offset;
     c->bpop.numreplicas = numreplicas;
     listAddNodeTail(server.clients_waiting_acks,c);
-    blockClient(c,REDIS_BLOCKED_WAIT);
+    blockClient(c,BLOCKED_WAIT);
 
     /* Make sure that the server will send an ACK request to all the slaves
      * before returning to the event loop. */
@@ -1945,44 +1945,44 @@ long long replicationGetSlaveOffset(void) {
 void replicationCron(void) {
     /* Non blocking connection timeout? */
     if (server.masterhost &&
-        (server.repl_state == REDIS_REPL_CONNECTING ||
-         server.repl_state == REDIS_REPL_RECEIVE_PONG) &&
+        (server.repl_state == REPL_STATE_CONNECTING ||
+         server.repl_state == REPL_STATE_RECEIVE_PONG) &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        serverLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
+        serverLog(LL_WARNING,"Timeout connecting to the MASTER...");
         undoConnectWithMaster();
     }
 
     /* Bulk transfer I/O timeout? */
-    if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER &&
+    if (server.masterhost && server.repl_state == REPL_STATE_TRANSFER &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        serverLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
+        serverLog(LL_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
         replicationAbortSyncTransfer();
     }
 
     /* Timed out master when we are an already connected slave? */
-    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTED &&
+    if (server.masterhost && server.repl_state == REPL_STATE_CONNECTED &&
         (time(NULL)-server.master->lastinteraction) > server.repl_timeout)
     {
-        serverLog(REDIS_WARNING,"MASTER timeout: no data nor PING received...");
+        serverLog(LL_WARNING,"MASTER timeout: no data nor PING received...");
         freeClient(server.master);
     }
 
     /* Check if we should connect to a MASTER */
-    if (server.repl_state == REDIS_REPL_CONNECT) {
-        serverLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
+    if (server.repl_state == REPL_STATE_CONNECT) {
+        serverLog(LL_NOTICE,"Connecting to MASTER %s:%d",
             server.masterhost, server.masterport);
         if (connectWithMaster() == C_OK) {
-            serverLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
+            serverLog(LL_NOTICE,"MASTER <-> SLAVE sync started");
         }
     }
 
     /* Send ACK to master from time to time.
      * Note that we do not send periodic acks to masters that don't
      * support PSYNC and replication offsets. */
     if (server.masterhost && server.master &&
-        !(server.master->flags & REDIS_PRE_PSYNC))
+        !(server.master->flags & CLIENT_PRE_PSYNC))
         replicationSendAck();
 
     /* If we have attached slaves, PING them from time to time.
@@ -2007,9 +2007,9 @@ void replicationCron(void) {
         while((ln = listNext(&li))) {
             client *slave = ln->value;
 
-            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START ||
-                (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END &&
-                 server.rdb_child_type != REDIS_RDB_CHILD_TYPE_SOCKET))
+            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START ||
+                (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END &&
+                 server.rdb_child_type != RDB_CHILD_TYPE_SOCKET))
             {
                 if (write(slave->fd, "\n", 1) == -1) {
                     /* Don't worry, it's just a ping. */
@@ -2027,11 +2027,11 @@ void replicationCron(void) {
         while((ln = listNext(&li))) {
             client *slave = ln->value;
 
-            if (slave->replstate != REDIS_REPL_ONLINE) continue;
-            if (slave->flags & REDIS_PRE_PSYNC) continue;
+            if (slave->replstate != SLAVE_STATE_ONLINE) continue;
+            if (slave->flags & CLIENT_PRE_PSYNC) continue;
             if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
             {
-                serverLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
+                serverLog(LL_WARNING, "Disconnecting timedout slave: %s",
                     replicationGetSlaveName(slave));
                 freeClient(slave);
             }
@@ -2047,7 +2047,7 @@ void replicationCron(void) {
 
         if (idle > server.repl_backlog_time_limit) {
             freeReplicationBacklog();
-            serverLog(REDIS_NOTICE,
+            serverLog(LL_NOTICE,
                 "Replication backlog freed after %d seconds "
                 "without connected slaves.",
                 (int) server.repl_backlog_time_limit);
@@ -2058,7 +2058,7 @@ void replicationCron(void) {
      * free our Replication Script Cache as there is no need to propagate
      * EVALSHA at all. */
     if (listLength(server.slaves) == 0 &&
-        server.aof_state == REDIS_AOF_OFF &&
+        server.aof_state == AOF_OFF &&
         listLength(server.repl_scriptcache_fifo) != 0)
     {
         replicationScriptCacheFlush();
@@ -2080,7 +2080,7 @@ void replicationCron(void) {
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
             client *slave = ln->value;
-            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+            if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
                 idle = server.unixtime - slave->lastinteraction;
                 if (idle > max_idle) max_idle = idle;
                 slaves_waiting++;
@@ -2099,8 +2099,8 @@ void replicationCron(void) {
                 listRewind(server.slaves,&li);
                 while((ln = listNext(&li))) {
                     client *slave = ln->value;
-                    if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
-                        slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+                    if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START)
+                        slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
                 }
             }
         }