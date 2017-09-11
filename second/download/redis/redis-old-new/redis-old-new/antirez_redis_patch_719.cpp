@@ -41,6 +41,30 @@ void replicationDiscardCachedMaster(void);
 void replicationResurrectCachedMaster(int newfd);
 void replicationSendAck(void);
 
+/* --------------------------- Utility functions ---------------------------- */
+
+/* Return the pointer to a string representing the slave ip:listening_port
+ * pair. Mostly useful for logging, since we want to log a slave using its
+ * IP address and it's listening port which is more clear for the user, for
+ * example: "Closing connection with slave 10.1.2.3:6380". */
+char *replicationGetSlaveName(redisClient *c) {
+    static char buf[REDIS_PEER_ID_LEN];
+    char ip[REDIS_IP_STR_LEN];
+
+    ip[0] = '\0';
+    buf[0] = '\0';
+    if (anetPeerToString(c->fd,ip,sizeof(ip),NULL) != -1) {
+        if (c->slave_listening_port)
+            snprintf(buf,sizeof(buf),"%s:%d",ip,c->slave_listening_port);
+        else
+            snprintf(buf,sizeof(buf),"%s:<unknown-slave-port>",ip);
+    } else {
+        snprintf(buf,sizeof(buf),"client id #%llu",
+            (unsigned long long) c->id);
+    }
+    return buf;
+}
+
 /* ---------------------------------- MASTER -------------------------------- */
 
 void createReplicationBacklog(void) {
@@ -212,7 +236,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     }
 
     /* Write the command to every slave. */
-    listRewind(slaves,&li);
+    listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
 
@@ -345,7 +369,8 @@ int masterTryPartialResynchronization(redisClient *c) {
                 "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
                 master_runid, server.runid);
         } else {
-            redisLog(REDIS_NOTICE,"Full resync requested by slave.");
+            redisLog(REDIS_NOTICE,"Full resync requested by slave %s",
+                replicationGetSlaveName(c));
         }
         goto need_full_resync;
     }
@@ -358,10 +383,10 @@ int masterTryPartialResynchronization(redisClient *c) {
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
     {
         redisLog(REDIS_NOTICE,
-            "Unable to partial resync with the slave for lack of backlog (Slave request was: %lld).", psync_offset);
+            "Unable to partial resync with slave %s for lack of backlog (Slave request was: %lld).", replicationGetSlaveName(c), psync_offset);
         if (psync_offset > server.master_repl_offset) {
             redisLog(REDIS_WARNING,
-                "Warning: slave tried to PSYNC with an offset that is greater than the master replication offset.");
+                "Warning: slave %s tried to PSYNC with an offset that is greater than the master replication offset.", replicationGetSlaveName(c));
         }
         goto need_full_resync;
     }
@@ -384,7 +409,9 @@ int masterTryPartialResynchronization(redisClient *c) {
     }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
     redisLog(REDIS_NOTICE,
-        "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
+        "Partial resynchronization request from %s accepted. Sending %lld bytes of backlog starting from offset %lld.",
+            replicationGetSlaveName(c),
+            psync_len, psync_offset);
     /* Note that we don't need to set the selected DB at server.slaveseldb
      * to -1 to force the master to emit SELECT, since the slave already
      * has this state from the previous connection with the master. */
@@ -408,6 +435,28 @@ int masterTryPartialResynchronization(redisClient *c) {
     return REDIS_ERR;
 }
 
+/* Start a BGSAVE for replication goals, which is, selecting the disk or
+ * socket target depending on the configuration, and making sure that
+ * the script cache is flushed before to start.
+ *
+ * Returns REDIS_OK on success or REDIS_ERR otherwise. */
+int startBgsaveForReplication(void) {
+    int retval;
+
+    redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
+        server.repl_diskless_sync ? "slaves sockets" : "disk");
+
+    if (server.repl_diskless_sync)
+        retval = rdbSaveToSlavesSockets();
+    else
+        retval = rdbSaveBackground(server.rdb_filename);
+
+    /* Flush the script cache, since we need that slave differences are
+     * accumulated without requiring slaves to match our cached scripts. */
+    if (retval == REDIS_OK) replicationScriptCacheFlush();
+    return retval;
+}
+
 /* SYNC and PSYNC command implemenation. */
 void syncCommand(redisClient *c) {
     /* ignore SYNC if already slave or in monitor mode */
@@ -429,7 +478,8 @@ void syncCommand(redisClient *c) {
         return;
     }
 
-    redisLog(REDIS_NOTICE,"Slave asks for synchronization");
+    redisLog(REDIS_NOTICE,"Slave %s asks for synchronization",
+        replicationGetSlaveName(c));
 
     /* Try a partial resynchronization if this is a PSYNC command.
      * If it fails, we continue with usual full resynchronization, however
@@ -465,10 +515,12 @@ void syncCommand(redisClient *c) {
 
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
-    if (server.rdb_child_pid != -1) {
+    if (server.rdb_child_pid != -1 &&
+        server.rdb_child_type == REDIS_RDB_CHILD_TYPE_DISK)
+    {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
-         * registering differences since the server forked to save */
+         * registering differences since the server forked to save. */
         redisClient *slave;
         listNode *ln;
         listIter li;
@@ -486,21 +538,35 @@ void syncCommand(redisClient *c) {
             redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
-             * register differences */
+             * register differences. */
             c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
+    } else if (server.rdb_child_pid != -1 &&
+               server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
+    {
+        /* There is an RDB child process but it is writing directly to
+         * children sockets. We need to wait for the next BGSAVE
+         * in order to synchronize. */
+        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+        redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
     } else {
-        /* Ok we don't have a BGSAVE in progress, let's start one */
-        redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
-        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
-            redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
-            addReplyError(c,"Unable to perform background save");
-            return;
+        if (server.repl_diskless_sync) {
+            /* Diskless replication RDB child is created inside
+             * replicationCron() since we want to delay its start a
+             * few seconds to wait for more slaves to arrive. */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+            if (server.repl_diskless_sync_delay)
+                redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
+        } else {
+            /* Ok we don't have a BGSAVE in progress, let's start one. */
+            if (startBgsaveForReplication() != REDIS_OK) {
+                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                addReplyError(c,"Unable to perform background save");
+                return;
+            }
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         }
-        c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-        /* Flush the script cache for the new slave. */
-        replicationScriptCacheFlush();
     }
 
     if (server.repl_disable_tcp_nodelay)
@@ -573,6 +639,29 @@ void replconfCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
+/* This function puts a slave in the online state, and should be called just
+ * after a slave received the RDB file for the initial synchronization, and
+ * we are finally ready to send the incremental stream of commands.
+ *
+ * It does a few things:
+ *
+ * 1) Put the slave in ONLINE state.
+ * 2) Make sure the writable event is re-installed, since calling the SYNC
+ *    command disables it, so that we can accumulate output buffer without
+ *    sending it to the slave.
+ * 3) Update the count of good slaves. */
+void putSlaveOnline(redisClient *slave) {
+    slave->replstate = REDIS_REPL_ONLINE;
+    slave->repl_ack_time = server.unixtime;
+    if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
+        sendReplyToClient, slave) == AE_ERR) {
+        redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
+        freeClient(slave);
+        return;
+    }
+    refreshGoodSlavesCount();
+}
+
 void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *slave = privdata;
     REDIS_NOTUSED(el);
@@ -623,26 +712,26 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
         close(slave->repldbfd);
         slave->repldbfd = -1;
         aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
-        slave->replstate = REDIS_REPL_ONLINE;
-        slave->repl_ack_time = server.unixtime;
-        if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
-            sendReplyToClient, slave) == AE_ERR) {
-            redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
-            freeClient(slave);
-            return;
-        }
-        refreshGoodSlavesCount();
-        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
+        putSlaveOnline(slave);
+        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded (disk)");
     }
 }
 
-/* This function is called at the end of every background saving.
- * The argument bgsaveerr is REDIS_OK if the background saving succeeded
- * otherwise REDIS_ERR is passed to the function.
+/* This function is called at the end of every background saving,
+ * or when the replication RDB transfer strategy is modified from
+ * disk to socket or the other way around.
  *
  * The goal of this function is to handle slaves waiting for a successful
- * background saving in order to perform non-blocking synchronization. */
-void updateSlavesWaitingBgsave(int bgsaveerr) {
+ * background saving in order to perform non-blocking synchronization, and
+ * to schedule a new BGSAVE if there are slaves that attached while a
+ * BGSAVE was in progress, but it was not a good one for replication (no
+ * other slave was accumulating differences).
+ *
+ * The argument bgsaveerr is REDIS_OK if the background saving succeeded
+ * otherwise REDIS_ERR is passed to the function.
+ * The 'type' argument is the type of the child that terminated
+ * (if it had a disk or socket target). */
+void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     listNode *ln;
     int startbgsave = 0;
     listIter li;
@@ -657,37 +746,44 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
         } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
-            if (bgsaveerr != REDIS_OK) {
-                freeClient(slave);
-                redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
-                continue;
-            }
-            if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
-                redis_fstat(slave->repldbfd,&buf) == -1) {
-                freeClient(slave);
-                redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
-                continue;
-            }
-            slave->repldboff = 0;
-            slave->repldbsize = buf.st_size;
-            slave->replstate = REDIS_REPL_SEND_BULK;
-            slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
-                (unsigned long long) slave->repldbsize);
-
-            aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
-            if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
-                freeClient(slave);
-                continue;
+            /* If this was an RDB on disk save, we have to prepare to send
+             * the RDB from disk to the slave socket. Otherwise if this was
+             * already an RDB -> Slaves socket transfer, used in the case of
+             * diskless replication, our work is trivial, we can just put
+             * the slave online. */
+            if (type == REDIS_RDB_CHILD_TYPE_SOCKET) {
+                putSlaveOnline(slave);
+                redisLog(REDIS_NOTICE,
+                    "Synchronization with slave %s succeeded (socket)",
+                        replicationGetSlaveName(slave));
+            } else {
+                if (bgsaveerr != REDIS_OK) {
+                    freeClient(slave);
+                    redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                    continue;
+                }
+                if ((slave->repldbfd = open(server.rdb_filename,O_RDONLY)) == -1 ||
+                    redis_fstat(slave->repldbfd,&buf) == -1) {
+                    freeClient(slave);
+                    redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                    continue;
+                }
+                slave->repldboff = 0;
+                slave->repldbsize = buf.st_size;
+                slave->replstate = REDIS_REPL_SEND_BULK;
+                slave->replpreamble = sdscatprintf(sdsempty(),"$%lld\r\n",
+                    (unsigned long long) slave->repldbsize);
+
+                aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
+                if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave) == AE_ERR) {
+                    freeClient(slave);
+                    continue;
+                }
             }
         }
     }
     if (startbgsave) {
-        /* Since we are starting a new background save for one or more slaves,
-         * we flush the Replication Script Cache to use EVAL to propagate every
-         * new EVALSHA for the first time, since all the new slaves don't know
-         * about previous scripts. */
-        replicationScriptCacheFlush();
-        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
+        if (startBgsaveForReplication() != REDIS_OK) {
             listIter li;
 
             listRewind(server.slaves,&li);
@@ -751,6 +847,12 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(privdata);
     REDIS_NOTUSED(mask);
 
+    /* Static vars used to hold the EOF mark, and the last bytes received
+     * form the server: when they match, we reached the end of the transfer. */
+    static char eofmark[REDIS_RUN_ID_SIZE];
+    static char lastbytes[REDIS_RUN_ID_SIZE];
+    static int usemark = 0;
+
     /* If repl_transfer_size == -1 we still have to read the bulk length
      * from the master reply. */
     if (server.repl_transfer_size == -1) {
@@ -776,30 +878,85 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$' (we received '%s'), are you sure the host and port are right?", buf);
             goto error;
         }
-        server.repl_transfer_size = strtol(buf+1,NULL,10);
-        redisLog(REDIS_NOTICE,
-            "MASTER <-> SLAVE sync: receiving %lld bytes from master",
-            (long long) server.repl_transfer_size);
+
+        /* There are two possible forms for the bulk payload. One is the
+         * usual $<count> bulk format. The other is used for diskless transfers
+         * when the master does not know beforehand the size of the file to
+         * transfer. In the latter case, the following format is used:
+         *
+         * $EOF:<40 bytes delimiter>
+         *
+         * At the end of the file the announced delimiter is transmitted. The
+         * delimiter is long and random enough that the probability of a
+         * collision with the actual file content can be ignored. */
+        if (strncmp(buf+1,"EOF:",4) == 0 && strlen(buf+5) >= REDIS_RUN_ID_SIZE) {
+            usemark = 1;
+            memcpy(eofmark,buf+5,REDIS_RUN_ID_SIZE);
+            memset(lastbytes,0,REDIS_RUN_ID_SIZE);
+            /* Set any repl_transfer_size to avoid entering this code path
+             * at the next call. */
+            server.repl_transfer_size = 0;
+            redisLog(REDIS_NOTICE,
+                "MASTER <-> SLAVE sync: receiving streamed RDB from master");
+        } else {
+            usemark = 0;
+            server.repl_transfer_size = strtol(buf+1,NULL,10);
+            redisLog(REDIS_NOTICE,
+                "MASTER <-> SLAVE sync: receiving %lld bytes from master",
+                (long long) server.repl_transfer_size);
+        }
         return;
     }
 
     /* Read bulk data */
-    left = server.repl_transfer_size - server.repl_transfer_read;
-    readlen = (left < (signed)sizeof(buf)) ? left : (signed)sizeof(buf);
+    if (usemark) {
+        readlen = sizeof(buf);
+    } else {
+        left = server.repl_transfer_size - server.repl_transfer_read;
+        readlen = (left < (signed)sizeof(buf)) ? left : (signed)sizeof(buf);
+    }
+
     nread = read(fd,buf,readlen);
     if (nread <= 0) {
         redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
             (nread == -1) ? strerror(errno) : "connection lost");
         replicationAbortSyncTransfer();
         return;
     }
+
+    /* When a mark is used, we want to detect EOF asap in order to avoid
+     * writing the EOF mark into the file... */
+    int eof_reached = 0;
+
+    if (usemark) {
+        /* Update the last bytes array, and check if it matches our delimiter. */
+        if (nread >= REDIS_RUN_ID_SIZE) {
+            memcpy(lastbytes,buf+nread-REDIS_RUN_ID_SIZE,REDIS_RUN_ID_SIZE);
+        } else {
+            int rem = REDIS_RUN_ID_SIZE-nread;
+            memmove(lastbytes,lastbytes+nread,rem);
+            memcpy(lastbytes+rem,buf,nread);
+        }
+        if (memcmp(lastbytes,eofmark,REDIS_RUN_ID_SIZE) == 0) eof_reached = 1;
+    }
+
     server.repl_transfer_lastio = server.unixtime;
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
         redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
         goto error;
     }
     server.repl_transfer_read += nread;
 
+    /* Delete the last 40 bytes from the file if we reached EOF. */
+    if (usemark && eof_reached) {
+        if (ftruncate(server.repl_transfer_fd,
+            server.repl_transfer_read - REDIS_RUN_ID_SIZE) == -1)
+        {
+            redisLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
+            goto error;
+        }
+    }
+
     /* Sync data on disk from time to time, otherwise at the end of the transfer
      * we may suffer a big delay as the memory buffers are copied into the
      * actual disk. */
@@ -814,7 +971,12 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     /* Check if the transfer is now complete */
-    if (server.repl_transfer_read == server.repl_transfer_size) {
+    if (!usemark) {
+        if (server.repl_transfer_read == server.repl_transfer_size)
+            eof_reached = 1;
+    }
+
+    if (eof_reached) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             replicationAbortSyncTransfer();
@@ -1817,7 +1979,9 @@ void replicationCron(void) {
             redisClient *slave = ln->value;
 
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START ||
-                slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+                (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END &&
+                 server.rdb_child_type != REDIS_RDB_CHILD_TYPE_SOCKET))
+            {
                 if (write(slave->fd, "\n", 1) == -1) {
                     /* Don't worry, it's just a ping. */
                 }
@@ -1838,15 +2002,8 @@ void replicationCron(void) {
             if (slave->flags & REDIS_PRE_PSYNC) continue;
             if ((server.unixtime - slave->repl_ack_time) > server.repl_timeout)
             {
-                char ip[REDIS_IP_STR_LEN];
-                int port;
-
-                if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) != -1) {
-                    redisLog(REDIS_WARNING,
-                        "Disconnecting timedout slave: %s:%d",
-                        ip, slave->slave_listening_port);
-                }
-                freeClient(slave);
+                    redisLog(REDIS_WARNING, "Disconnecting timedout slave: %s",
+                        replicationGetSlaveName(slave));
             }
         }
     }
@@ -1877,6 +2034,48 @@ void replicationCron(void) {
         replicationScriptCacheFlush();
     }
 
+    /* If we are using diskless replication and there are slaves waiting
+     * in WAIT_BGSAVE_START state, check if enough seconds elapsed and
+     * start a BGSAVE.
+     *
+     * This code is also useful to trigger a BGSAVE if the diskless
+     * replication was turned off with CONFIG SET, while there were already
+     * slaves in WAIT_BGSAVE_START state. */
+    if (server.rdb_child_pid == -1 && server.aof_child_pid == -1) {
+        time_t idle, max_idle = 0;
+        int slaves_waiting = 0;
+        listNode *ln;
+        listIter li;
+
+        listRewind(server.slaves,&li);
+        while((ln = listNext(&li))) {
+            redisClient *slave = ln->value;
+            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+                idle = server.unixtime - slave->lastinteraction;
+                if (idle > max_idle) max_idle = idle;
+                slaves_waiting++;
+            }
+        }
+
+        if (slaves_waiting && max_idle > server.repl_diskless_sync_delay) {
+            /* Start a BGSAVE. Usually with socket target, or with disk target
+             * if there was a recent socket -> disk config change. */
+            if (startBgsaveForReplication() == REDIS_OK) {
+                /* It started! We need to change the state of slaves
+                 * from WAIT_BGSAVE_START to WAIT_BGSAVE_END in case
+                 * the current target is disk. Otherwise it was already done
+                 * by rdbSaveToSlavesSockets() which is called by
+                 * startBgsaveForReplication(). */
+                listRewind(server.slaves,&li);
+                while((ln = listNext(&li))) {
+                    redisClient *slave = ln->value;
+                    if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
+                        slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+                }
+            }
+        }
+    }
+
     /* Refresh the number of slaves with lag <= min-slaves-max-lag. */
     refreshGoodSlavesCount();
 }