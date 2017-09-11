@@ -302,46 +302,46 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
 long long addReplyReplicationBacklog(redisClient *c, long long offset) {
     long long j, skip, len;
 
-    redisLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
+    serverLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
 
     if (server.repl_backlog_histlen == 0) {
-        redisLog(REDIS_DEBUG, "[PSYNC] Backlog history len is zero");
+        serverLog(REDIS_DEBUG, "[PSYNC] Backlog history len is zero");
         return 0;
     }
 
-    redisLog(REDIS_DEBUG, "[PSYNC] Backlog size: %lld",
+    serverLog(REDIS_DEBUG, "[PSYNC] Backlog size: %lld",
              server.repl_backlog_size);
-    redisLog(REDIS_DEBUG, "[PSYNC] First byte: %lld",
+    serverLog(REDIS_DEBUG, "[PSYNC] First byte: %lld",
              server.repl_backlog_off);
-    redisLog(REDIS_DEBUG, "[PSYNC] History len: %lld",
+    serverLog(REDIS_DEBUG, "[PSYNC] History len: %lld",
              server.repl_backlog_histlen);
-    redisLog(REDIS_DEBUG, "[PSYNC] Current index: %lld",
+    serverLog(REDIS_DEBUG, "[PSYNC] Current index: %lld",
              server.repl_backlog_idx);
 
     /* Compute the amount of bytes we need to discard. */
     skip = offset - server.repl_backlog_off;
-    redisLog(REDIS_DEBUG, "[PSYNC] Skipping: %lld", skip);
+    serverLog(REDIS_DEBUG, "[PSYNC] Skipping: %lld", skip);
 
     /* Point j to the oldest byte, that is actaully our
      * server.repl_backlog_off byte. */
     j = (server.repl_backlog_idx +
         (server.repl_backlog_size-server.repl_backlog_histlen)) %
         server.repl_backlog_size;
-    redisLog(REDIS_DEBUG, "[PSYNC] Index of first byte: %lld", j);
+    serverLog(REDIS_DEBUG, "[PSYNC] Index of first byte: %lld", j);
 
     /* Discard the amount of data to seek to the specified 'offset'. */
     j = (j + skip) % server.repl_backlog_size;
 
     /* Feed slave with data. Since it is a circular buffer we have to
      * split the reply in two parts if we are cross-boundary. */
     len = server.repl_backlog_histlen - skip;
-    redisLog(REDIS_DEBUG, "[PSYNC] Reply total length: %lld", len);
+    serverLog(REDIS_DEBUG, "[PSYNC] Reply total length: %lld", len);
     while(len) {
         long long thislen =
             ((server.repl_backlog_size - j) < len) ?
             (server.repl_backlog_size - j) : len;
 
-        redisLog(REDIS_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
+        serverLog(REDIS_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
         addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
         len -= thislen;
         j = 0;
@@ -366,11 +366,11 @@ int masterTryPartialResynchronization(redisClient *c) {
     if (strcasecmp(master_runid, server.runid)) {
         /* Run id "?" is used by slaves that want to force a full resync. */
         if (master_runid[0] != '?') {
-            redisLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
+            serverLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
                 "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
                 master_runid, server.runid);
         } else {
-            redisLog(REDIS_NOTICE,"Full resync requested by slave %s",
+            serverLog(REDIS_NOTICE,"Full resync requested by slave %s",
                 replicationGetSlaveName(c));
         }
         goto need_full_resync;
@@ -383,10 +383,10 @@ int masterTryPartialResynchronization(redisClient *c) {
         psync_offset < server.repl_backlog_off ||
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
     {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Unable to partial resync with slave %s for lack of backlog (Slave request was: %lld).", replicationGetSlaveName(c), psync_offset);
         if (psync_offset > server.master_repl_offset) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Warning: slave %s tried to PSYNC with an offset that is greater than the master replication offset.", replicationGetSlaveName(c));
         }
         goto need_full_resync;
@@ -410,7 +410,7 @@ int masterTryPartialResynchronization(redisClient *c) {
         return REDIS_OK;
     }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
-    redisLog(REDIS_NOTICE,
+    serverLog(REDIS_NOTICE,
         "Partial resynchronization request from %s accepted. Sending %lld bytes of backlog starting from offset %lld.",
             replicationGetSlaveName(c),
             psync_len, psync_offset);
@@ -445,7 +445,7 @@ int masterTryPartialResynchronization(redisClient *c) {
 int startBgsaveForReplication(void) {
     int retval;
 
-    redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
+    serverLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
         server.repl_diskless_sync ? "slaves sockets" : "disk");
 
     if (server.repl_diskless_sync)
@@ -480,7 +480,7 @@ void syncCommand(redisClient *c) {
         return;
     }
 
-    redisLog(REDIS_NOTICE,"Slave %s asks for synchronization",
+    serverLog(REDIS_NOTICE,"Slave %s asks for synchronization",
         replicationGetSlaveName(c));
 
     /* Try a partial resynchronization if this is a PSYNC command.
@@ -537,12 +537,12 @@ void syncCommand(redisClient *c) {
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
             c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-            redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
+            serverLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
              * register differences. */
             c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
-            redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
+            serverLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
     } else if (server.rdb_child_pid != -1 &&
                server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
@@ -551,19 +551,19 @@ void syncCommand(redisClient *c) {
          * children sockets. We need to wait for the next BGSAVE
          * in order to synchronize. */
         c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
-        redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
+        serverLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
     } else {
         if (server.repl_diskless_sync) {
             /* Diskless replication RDB child is created inside
              * replicationCron() since we want to delay its start a
              * few seconds to wait for more slaves to arrive. */
             c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             if (server.repl_diskless_sync_delay)
-                redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
+                serverLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
             /* Ok we don't have a BGSAVE in progress, let's start one. */
             if (startBgsaveForReplication() != REDIS_OK) {
-                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                serverLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");
                 return;
             }
@@ -664,12 +664,12 @@ void putSlaveOnline(redisClient *slave) {
     slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
     if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
         sendReplyToClient, slave) == AE_ERR) {
-        redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
         freeClient(slave);
         return;
     }
     refreshGoodSlavesCount();
-    redisLog(REDIS_NOTICE,"Synchronization with slave %s succeeded",
+    serverLog(REDIS_NOTICE,"Synchronization with slave %s succeeded",
         replicationGetSlaveName(slave));
 }
 
@@ -686,7 +686,7 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (slave->replpreamble) {
         nwritten = write(fd,slave->replpreamble,sdslen(slave->replpreamble));
         if (nwritten == -1) {
-            redisLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
+            serverLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
                 strerror(errno));
             freeClient(slave);
             return;
@@ -706,14 +706,14 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
     buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
     if (buflen <= 0) {
-        redisLog(REDIS_WARNING,"Read error sending DB to slave: %s",
+        serverLog(REDIS_WARNING,"Read error sending DB to slave: %s",
             (buflen == 0) ? "premature EOF" : strerror(errno));
         freeClient(slave);
         return;
     }
     if ((nwritten = write(fd,buf,buflen)) == -1) {
         if (errno != EAGAIN) {
-            redisLog(REDIS_WARNING,"Write error sending DB to slave: %s",
+            serverLog(REDIS_WARNING,"Write error sending DB to slave: %s",
                 strerror(errno));
             freeClient(slave);
         }
@@ -764,7 +764,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
              * diskless replication, our work is trivial, we can just put
              * the slave online. */
             if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
-                redisLog(REDIS_NOTICE,
+                serverLog(REDIS_NOTICE,
                     "Streamed RDB transfer with slave %s succeeded (socket). Waiting for REPLCONF ACK from slave to enable streaming",
                         replicationGetSlaveName(slave));
                 /* Note: we wait for a REPLCONF ACK message from slave in
@@ -778,13 +778,13 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             } else {
                 if (bgsaveerr != REDIS_OK) {
                     freeClient(slave);
-                    redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                    serverLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
                     continue;
                 }
                 if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
                     redis_fstat(slave->repldbfd,&buf) == -1) {
                     freeClient(slave);
-                    redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                    serverLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                     continue;
                 }
                 slave->repldboff = 0;
@@ -806,7 +806,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             listIter li;
 
             listRewind(server.slaves,&li);
-            redisLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
+            serverLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
             while((ln = listNext(&li))) {
                 redisClient *slave = ln->value;
 
@@ -893,14 +893,14 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
      * from the master reply. */
     if (server.repl_transfer_size == -1) {
         if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
                 strerror(errno));
             goto error;
         }
 
         if (buf[0] == '-') {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "MASTER aborted replication with an error: %s",
                 buf+1);
             goto error;
@@ -911,7 +911,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             server.repl_transfer_lastio = server.unixtime;
             return;
         } else if (buf[0] != '$') {
-            redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$' (we received '%s'), are you sure the host and port are right?", buf);
+            serverLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$' (we received '%s'), are you sure the host and port are right?", buf);
             goto error;
         }
 
@@ -932,12 +932,12 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             /* Set any repl_transfer_size to avoid entering this code path
              * at the next call. */
             server.repl_transfer_size = 0;
-            redisLog(REDIS_NOTICE,
+            serverLog(REDIS_NOTICE,
                 "MASTER <-> SLAVE sync: receiving streamed RDB from master");
         } else {
             usemark = 0;
             server.repl_transfer_size = strtol(buf+1,NULL,10);
-            redisLog(REDIS_NOTICE,
+            serverLog(REDIS_NOTICE,
                 "MASTER <-> SLAVE sync: receiving %lld bytes from master",
                 (long long) server.repl_transfer_size);
         }
@@ -954,7 +954,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     nread = read(fd,buf,readlen);
     if (nread <= 0) {
-        redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
+        serverLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
             (nread == -1) ? strerror(errno) : "connection lost");
         replicationAbortSyncTransfer();
         return;
@@ -979,7 +979,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     server.repl_transfer_lastio = server.unixtime;
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
-        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
         goto error;
     }
     server.repl_transfer_read += nread;
@@ -989,7 +989,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (ftruncate(server.repl_transfer_fd,
             server.repl_transfer_read - REDIS_RUN_ID_SIZE) == -1)
         {
-            redisLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
+            serverLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
             goto error;
         }
     }
@@ -1015,29 +1015,29 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (eof_reached) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
-            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
+            serverLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             replicationAbortSyncTransfer();
             return;
         }
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
+        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
         signalFlushedDb(-1);
         emptyDb(replicationEmptyDbCallback);
         /* Before loading the DB into memory we need to delete the readable
          * handler, otherwise it will get called recursively since
          * rdbLoad() will call the event loop to process events from time to
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
+        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
         if (rdbLoad(server.rdb_filename) != REDIS_OK) {
-            redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
+            serverLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             replicationAbortSyncTransfer();
             return;
         }
         /* Final setup of the connected slave <- master link */
         zfree(server.repl_transfer_tmpfile);
         close(server.repl_transfer_fd);
         replicationCreateMasterClient(server.repl_transfer_s);
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
+        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
@@ -1046,11 +1046,11 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
             stopAppendOnly();
             while (retry-- && startAppendOnly() == REDIS_ERR) {
-                redisLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
+                serverLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                 sleep(1);
             }
             if (!retry) {
-                redisLog(REDIS_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
+                serverLog(REDIS_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                 exit(1);
             }
         }
@@ -1145,9 +1145,9 @@ int slaveTryPartialResynchronization(int fd) {
     if (server.cached_master) {
         psync_runid = server.cached_master->replrunid;
         snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
-        redisLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+        serverLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
     } else {
-        redisLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
+        serverLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
         psync_runid = "?";
         memcpy(psync_offset,"-1",3);
     }
@@ -1167,7 +1167,7 @@ int slaveTryPartialResynchronization(int fd) {
             if (offset) offset++;
         }
         if (!runid || !offset || (offset-runid-1) != REDIS_RUN_ID_SIZE) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Master replied with wrong +FULLRESYNC syntax.");
             /* This is an unexpected condition, actually the +FULLRESYNC
              * reply means that the master supports PSYNC, but the reply
@@ -1178,7 +1178,7 @@ int slaveTryPartialResynchronization(int fd) {
             memcpy(server.repl_master_runid, runid, offset-runid-1);
             server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
             server.repl_master_initial_offset = strtoll(offset,NULL,10);
-            redisLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
+            serverLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
                 server.repl_master_runid,
                 server.repl_master_initial_offset);
         }
@@ -1190,7 +1190,7 @@ int slaveTryPartialResynchronization(int fd) {
 
     if (!strncmp(reply,"+CONTINUE",9)) {
         /* Partial resync was accepted, set the replication state accordingly */
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Successful partial resynchronization with master.");
         sdsfree(reply);
         replicationResurrectCachedMaster(fd);
@@ -1203,10 +1203,10 @@ int slaveTryPartialResynchronization(int fd) {
 
     if (strncmp(reply,"-ERR",4)) {
         /* If it's not an error, log the unexpected event. */
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Unexpected reply to PSYNC from master: %s", reply);
     } else {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Master does not support PSYNC or is in "
             "error state (reply: %s)", reply);
     }
@@ -1236,7 +1236,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         sockerr = errno;
     if (sockerr) {
         aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
-        redisLog(REDIS_WARNING,"Error condition on socket for SYNC: %s",
+        serverLog(REDIS_WARNING,"Error condition on socket for SYNC: %s",
             strerror(sockerr));
         goto error;
     }
@@ -1246,7 +1246,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
      * replication process where we have long timeouts in the order of
      * seconds (in the meantime the slave would block). */
     if (server.repl_state == REDIS_REPL_CONNECTING) {
-        redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
+        serverLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
         /* Delete the writable event so that the readable event remains
          * registered and we can wait for the PONG reply. */
         aeDeleteFileEvent(server.el,fd,AE_WRITABLE);
@@ -1270,7 +1270,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (syncReadLine(fd,buf,sizeof(buf),
             server.repl_syncio_timeout*1000) == -1)
         {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "I/O error reading PING reply from master: %s",
                 strerror(errno));
             goto error;
@@ -1285,10 +1285,10 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
             strncmp(buf,"-NOAUTH",7) != 0 &&
             strncmp(buf,"-ERR operation not permitted",28) != 0)
         {
-            redisLog(REDIS_WARNING,"Error reply to PING from master: '%s'",buf);
+            serverLog(REDIS_WARNING,"Error reply to PING from master: '%s'",buf);
             goto error;
         } else {
-            redisLog(REDIS_NOTICE,
+            serverLog(REDIS_NOTICE,
                 "Master replied to PING, replication can continue...");
         }
     }
@@ -1297,7 +1297,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     if(server.masterauth) {
         err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
         if (err[0] == '-') {
-            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
+            serverLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
             sdsfree(err);
             goto error;
         }
@@ -1314,7 +1314,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF listening-port. */
         if (err[0] == '-') {
-            redisLog(REDIS_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
+            serverLog(REDIS_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
         }
         sdsfree(err);
     }
@@ -1326,17 +1326,17 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
      * reconnection attempt. */
     psync_result = slaveTryPartialResynchronization(fd);
     if (psync_result == PSYNC_CONTINUE) {
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
+        serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
         return;
     }
 
     /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
      * and the server.repl_master_runid and repl_master_initial_offset are
      * already populated. */
     if (psync_result == PSYNC_NOT_SUPPORTED) {
-        redisLog(REDIS_NOTICE,"Retrying with SYNC...");
+        serverLog(REDIS_NOTICE,"Retrying with SYNC...");
         if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
-            redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
+            serverLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
                 strerror(errno));
             goto error;
         }
@@ -1351,15 +1351,15 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         sleep(1);
     }
     if (dfd == -1) {
-        redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
+        serverLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
         goto error;
     }
 
     /* Setup the non blocking download of the bulk file. */
     if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
             == AE_ERR)
     {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Can't create readable event for SYNC: %s (fd=%d)",
             strerror(errno),fd);
         goto error;
@@ -1387,7 +1387,7 @@ int connectWithMaster(void) {
     fd = anetTcpNonBlockBestEffortBindConnect(NULL,
         server.masterhost,server.masterport,REDIS_BIND_ADDR);
     if (fd == -1) {
-        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
+        serverLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
             strerror(errno));
         return REDIS_ERR;
     }
@@ -1396,7 +1396,7 @@ int connectWithMaster(void) {
             AE_ERR)
     {
         close(fd);
-        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
+        serverLog(REDIS_WARNING,"Can't create readable event for SYNC");
         return REDIS_ERR;
     }
 
@@ -1491,7 +1491,7 @@ void slaveofCommand(redisClient *c) {
         !strcasecmp(c->argv[2]->ptr,"one")) {
         if (server.masterhost) {
             replicationUnsetMaster();
-            redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
+            serverLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
         }
     } else {
         long port;
@@ -1502,14 +1502,14 @@ void slaveofCommand(redisClient *c) {
         /* Check if we are already attached to the specified slave */
         if (server.masterhost && !strcasecmp(server.masterhost,c->argv[1]->ptr)
             && server.masterport == port) {
-            redisLog(REDIS_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
+            serverLog(REDIS_NOTICE,"SLAVE OF would result into synchronization with the master we are already connected with. No operation performed.");
             addReplySds(c,sdsnew("+OK Already connected to specified master\r\n"));
             return;
         }
         /* There was no previous master or the user specified a different one,
          * we can continue. */
         replicationSetMaster(c->argv[1]->ptr, port);
-        redisLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
+        serverLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
             server.masterhost, server.masterport);
     }
     addReply(c,shared.ok);
@@ -1604,7 +1604,7 @@ void replicationCacheMaster(redisClient *c) {
     listNode *ln;
 
     redisAssert(server.master != NULL && server.cached_master == NULL);
-    redisLog(REDIS_NOTICE,"Caching the disconnected master state.");
+    serverLog(REDIS_NOTICE,"Caching the disconnected master state.");
 
     /* Remove from the list of clients, we don't want this client to be
      * listed by CLIENT LIST or processed in any way by batch operations. */
@@ -1642,7 +1642,7 @@ void replicationCacheMaster(redisClient *c) {
 void replicationDiscardCachedMaster(void) {
     if (server.cached_master == NULL) return;
 
-    redisLog(REDIS_NOTICE,"Discarding previously cached master state.");
+    serverLog(REDIS_NOTICE,"Discarding previously cached master state.");
     server.cached_master->flags &= ~REDIS_MASTER;
     freeClient(server.cached_master);
     server.cached_master = NULL;
@@ -1667,7 +1667,7 @@ void replicationResurrectCachedMaster(int newfd) {
     listAddNodeTail(server.clients,server.master);
     if (aeCreateFileEvent(server.el, newfd, AE_READABLE,
                           readQueryFromClient, server.master)) {
-        redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
         freeClientAsync(server.master); /* Close ASAP. */
     }
 
@@ -1676,7 +1676,7 @@ void replicationResurrectCachedMaster(int newfd) {
     if (server.master->bufpos || listLength(server.master->reply)) {
         if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
                           sendReplyToClient, server.master)) {
-            redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
+            serverLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
             freeClientAsync(server.master); /* Close ASAP. */
         }
     }
@@ -1949,32 +1949,32 @@ void replicationCron(void) {
          server.repl_state == REDIS_REPL_RECEIVE_PONG) &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
+        serverLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
         undoConnectWithMaster();
     }
 
     /* Bulk transfer I/O timeout? */
     if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
+        serverLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
         replicationAbortSyncTransfer();
     }
 
     /* Timed out master when we are an already connected slave? */
     if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTED &&
         (time(NULL)-server.master->lastinteraction) > server.repl_timeout)
     {
-        redisLog(REDIS_WARNING,"MASTER timeout: no data nor PING received...");
+        serverLog(REDIS_WARNING,"MASTER timeout: no data nor PING received...");
         freeClient(server.master);
     }
 
     /* Check if we should connect to a MASTER */
     if (server.repl_state == REDIS_REPL_CONNECT) {
-        redisLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
+        serverLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
             server.masterhost, server.masterport);
         if (connectWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
+            serverLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
         }
     }
 
@@ -2031,7 +2031,7 @@ void replicationCron(void) {
             if (slave->flags & REDIS_PRE_PSYNC) continue;
             if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
             {
-                redisLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
+                serverLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
                     replicationGetSlaveName(slave));
                 freeClient(slave);
             }
@@ -2047,7 +2047,7 @@ void replicationCron(void) {
 
         if (idle > server.repl_backlog_time_limit) {
             freeReplicationBacklog();
-            redisLog(REDIS_NOTICE,
+            serverLog(REDIS_NOTICE,
                 "Replication backlog freed after %d seconds "
                 "without connected slaves.",
                 (int) server.repl_backlog_time_limit);