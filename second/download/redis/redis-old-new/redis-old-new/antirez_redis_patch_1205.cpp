@@ -37,13 +37,234 @@
 #include <sys/socket.h>
 #include <sys/stat.h>
 
+void replicationDiscardCachedMaster(void);
+void replicationResurrectCachedMaster(int newfd);
+
 /* ---------------------------------- MASTER -------------------------------- */
 
+void createReplicationBacklog(void) {
+    redisAssert(server.repl_backlog == NULL);
+    server.repl_backlog = zmalloc(server.repl_backlog_size);
+    server.repl_backlog_histlen = 0;
+    server.repl_backlog_idx = 0;
+    /* When a new backlog buffer is created, we increment the replication
+     * offset by one to make sure we'll not be able to PSYNC with any
+     * previous slave. This is needed because we avoid incrementing the
+     * master_repl_offset if no backlog exists nor slaves are attached. */
+    server.master_repl_offset++;
+
+    /* We don't have any data inside our buffer, but virtually the first
+     * byte we have is the next byte that will be generated for the
+     * replication stream. */
+    server.repl_backlog_off = server.master_repl_offset+1;
+}
+
+/* This function is called when the user modifies the replication backlog
+ * size at runtime. It is up to the function to both update the
+ * server.repl_backlog_size and to resize the buffer and setup it so that
+ * it contains the same data as the previous one (possibly less data, but
+ * the most recent bytes, or the same data and more free space in case the
+ * buffer is enlarged). */
+void resizeReplicationBacklog(long long newsize) {
+    if (newsize < REDIS_REPL_BACKLOG_MIN_SIZE)
+        newsize = REDIS_REPL_BACKLOG_MIN_SIZE;
+    if (server.repl_backlog_size == newsize) return;
+
+    server.repl_backlog_size = newsize;
+    if (server.repl_backlog != NULL) {
+        /* What we actually do is to flush the old buffer and realloc a new
+         * empty one. It will refill with new data incrementally.
+         * The reason is that copying a few gigabytes adds latency and even
+         * worse often we need to alloc additional space before freeing the
+         * old buffer. */
+        zfree(server.repl_backlog);
+        server.repl_backlog = zmalloc(server.repl_backlog_size);
+        server.repl_backlog_histlen = 0;
+        server.repl_backlog_idx = 0;
+        /* Next byte we have is... the next since the buffer is emtpy. */
+        server.repl_backlog_off = server.master_repl_offset+1;
+    }
+}
+
+void freeReplicationBacklog(void) {
+    redisAssert(server.repl_backlog != NULL);
+    zfree(server.repl_backlog);
+    server.repl_backlog = NULL;
+}
+
+/* Add data to the replication backlog.
+ * This function also increments the global replication offset stored at
+ * server.master_repl_offset, because there is no case where we want to feed
+ * the backlog without incrementing the buffer. */
+void feedReplicationBacklog(void *ptr, size_t len) {
+    unsigned char *p = ptr;
+
+    server.master_repl_offset += len;
+
+    /* This is a circular buffer, so write as much data we can at every
+     * iteration and rewind the "idx" index if we reach the limit. */
+    while(len) {
+        size_t thislen = server.repl_backlog_size - server.repl_backlog_idx;
+        if (thislen > len) thislen = len;
+        memcpy(server.repl_backlog+server.repl_backlog_idx,p,thislen);
+        server.repl_backlog_idx += thislen;
+        if (server.repl_backlog_idx == server.repl_backlog_size)
+            server.repl_backlog_idx = 0;
+        len -= thislen;
+        p += thislen;
+        server.repl_backlog_histlen += thislen;
+    }
+    if (server.repl_backlog_histlen > server.repl_backlog_size)
+        server.repl_backlog_histlen = server.repl_backlog_size;
+    /* Set the offset of the first byte we have in the backlog. */
+    server.repl_backlog_off = server.master_repl_offset -
+                              server.repl_backlog_histlen + 1;
+}
+
+/* Wrapper for feedReplicationBacklog() that takes Redis string objects
+ * as input. */
+void feedReplicationBacklogWithObject(robj *o) {
+    char llstr[REDIS_LONGSTR_SIZE];
+    void *p;
+    size_t len;
+
+    if (o->encoding == REDIS_ENCODING_INT) {
+        len = ll2string(llstr,sizeof(llstr),(long)o->ptr);
+        p = llstr;
+    } else {
+        len = sdslen(o->ptr);
+        p = o->ptr;
+    }
+    feedReplicationBacklog(p,len);
+}
+
+#define FEEDSLAVE_BUF_SIZE (1024*64)
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int j;
+    int j, i, len;
+    char buf[FEEDSLAVE_BUF_SIZE], *b = buf;
+    char llstr[REDIS_LONGSTR_SIZE];
+    int buf_left = FEEDSLAVE_BUF_SIZE;
+    robj *o;
+
+    /* If there aren't slaves, and there is no backlog buffer to populate,
+     * we can return ASAP. */
+    if (server.repl_backlog == NULL && listLength(slaves) == 0) return;
+
+    /* We can't have slaves attached and no backlog. */
+    redisAssert(!(listLength(slaves) != 0 && server.repl_backlog == NULL));
+
+    /* What we do here is to try to write as much data as possible in a static
+     * buffer "buf" that is used to create an object that is later sent to all
+     * the slaves. This way we do the decoding only one time for most commands
+     * not containing big payloads. */
+
+    /* Create the SELECT command into the static buffer if needed. */
+    if (server.slaveseldb != dictid) {
+        char *selectcmd;
+        size_t sclen;
+
+        if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
+            selectcmd = shared.select[dictid]->ptr;
+            sclen = sdslen(selectcmd);
+            memcpy(b,selectcmd,sclen);
+            b += sclen;
+            buf_left -= sclen;
+        } else {
+            int dictid_len;
+
+            dictid_len = ll2string(llstr,sizeof(llstr),dictid);
+            sclen = snprintf(b,buf_left,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
+                dictid_len, llstr);
+            b += sclen;
+            buf_left -= sclen;
+        }
+    }
+    server.slaveseldb = dictid;
+   
+    /* Add the multi bulk reply size to the static buffer, that is, the number
+     * of arguments of the command to send to every slave. */
+    b[0] = '*';
+    len = ll2string(b+1,REDIS_LONGSTR_SIZE,argc);
+    b += len+1;
+    buf_left -= len;
+    b[0] = '\r';
+    b[1] = '\n';
+    b += 2;
+    buf_left -= 2;
+
+    /* Try to use the static buffer for as much arguments is possible. */
+    for (j = 0; j < argc; j++) {
+        int objlen;
+        char *objptr;
+
+        if (argv[j]->encoding != REDIS_ENCODING_RAW &&
+            argv[j]->encoding != REDIS_ENCODING_INT) {
+            redisPanic("Unexpected encoding");
+        }
+        if (argv[j]->encoding == REDIS_ENCODING_RAW) {
+            objlen = sdslen(argv[j]->ptr);
+            objptr = argv[j]->ptr;
+        } else {
+            objlen = ll2string(llstr,REDIS_LONGSTR_SIZE,(long)argv[j]->ptr);
+            objptr = llstr;
+        }
+        /* We need enough space for bulk reply encoding, newlines, and
+         * the data itself. */
+        if (buf_left < objlen+REDIS_LONGSTR_SIZE+32) break;
+
+        /* Write $...CRLF */
+        b[0] = '$';
+        len = ll2string(b+1,REDIS_LONGSTR_SIZE,objlen);
+        b += len+1;
+        buf_left -= len;
+        b[0] = '\r';
+        b[1] = '\n';
+        b += 2;
+        buf_left -= 2;
+
+        /* And data plus CRLF */
+        memcpy(b,objptr,objlen);
+        b += objlen;
+        buf_left -= objlen;
+        b[0] = '\r';
+        b[1] = '\n';
+        b += 2;
+        buf_left -= 2;
+    }
+
+    /* Create an object with the static buffer content. */
+    redisAssert(buf_left < FEEDSLAVE_BUF_SIZE);
+    o = createStringObject(buf,b-buf);
+
+    /* If we have a backlog, populate it with data and increment
+     * the global replication offset. */
+    if (server.repl_backlog) {
+        feedReplicationBacklogWithObject(o);
+        for (i = j; i < argc; i++) {
+            char aux[REDIS_LONGSTR_SIZE+3];
+            long objlen = stringObjectLen(argv[i]);
+
+            /* We need to feed the buffer with the object as a bulk reply
+             * not just as a plain string, so create the $..CRLF payload len 
+             * ad add the final CRLF */
+            aux[0] = '$';
+            len = ll2string(aux+1,objlen,sizeof(aux)-1);
+            aux[len+1] = '\r';
+            aux[len+2] = '\n';
+            feedReplicationBacklog(aux,len+3);
+            feedReplicationBacklogWithObject(argv[j]);
+            feedReplicationBacklogWithObject(shared.crlf);
+        }
+    }
 
+    /* Write data to slaves. Here we do two things:
+     * 1) We write the "o" object that was created using the accumulated
+     *    static buffer.
+     * 2) We write any additional argument of the command to replicate that
+     *    was not written inside the static buffer for lack of space.
+     */
     listRewind(slaves,&li);
     while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
@@ -54,29 +275,16 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
         /* Feed slaves that are waiting for the initial SYNC (so these commands
          * are queued in the output buffer until the initial SYNC completes),
          * or are already in sync with the master. */
-        if (server.slaveseldb != dictid) {
-            robj *selectcmd;
-
-            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
-                selectcmd = shared.select[dictid];
-                incrRefCount(selectcmd);
-            } else {
-                char dictid_str[64];
-                int dictid_len;
-
-                dictid_len = ll2string(dictid_str,sizeof(dictid_str),dictid);
-                selectcmd = createObject(REDIS_STRING,
-                    sdscatprintf(sdsempty(),
-                        "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
-                        dictid_len, dictid_str));
-            }
-            addReply(slave,selectcmd);
-            decrRefCount(selectcmd);
-        }
-        addReplyMultiBulkLen(slave,argc);
-        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
+
+        /* First, trasmit the object created from the static buffer. */
+        addReply(slave,o);
+
+        /* Finally any additional argument that was not stored inside the
+         * static buffer if any (from j to argc). */
+        for (i = j; i < argc; i++)
+            addReplyBulk(slave,argv[i]);
     }
-    server.slaveseldb = dictid;
+    decrRefCount(o);
 }
 
 void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
@@ -120,6 +328,120 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
     decrRefCount(cmdobj);
 }
 
+/* Feed the slave 'c' with the replication backlog starting from the
+ * specified 'offset' up to the end of the backlog. */
+long long addReplyReplicationBacklog(redisClient *c, long long offset) {
+    long long j, skip, len;
+
+//    printf("SLAVE REQUEST %lld\n", offset);
+
+    if (server.repl_backlog_histlen == 0) {
+//        printf("NO HISTORY\n");
+        return 0;
+    }
+
+//    printf("FIRST BYTE WE HAVE %lld\n", server.repl_backlog_off);
+//    printf("HISTLEN %lld\n", server.repl_backlog_histlen);
+//    printf("IDX %lld\n", server.repl_backlog_idx);
+
+    /* Compute the amount of bytes we need to discard. */
+    skip = offset - server.repl_backlog_off;
+//    printf("SKIP %lld\n", skip);
+
+    /* Point j to the oldest byte, that is actaully our
+     * server.repl_backlog_off byte. */
+    j = (server.repl_backlog_idx +
+        (server.repl_backlog_size-server.repl_backlog_histlen)) %
+        server.repl_backlog_size;
+//    printf("J %lld\n", j);
+
+    /* Discard the amount of data to seek to the specified 'offset'. */
+    j = (j + skip) % server.repl_backlog_size;
+
+    /* Feed slave with data. Since it is a circular buffer we have to
+     * split the reply in two parts if we are cross-boundary. */
+    len = server.repl_backlog_histlen - skip;
+//    printf("LEN %lld\n", len);
+    while(len) {
+        long long thislen =
+            ((server.repl_backlog_size - j) < len) ?
+            (server.repl_backlog_size - j) : len;
+
+//        printf("WRITE %lld\n", thislen);
+        addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
+        len -= thislen;
+        j = 0;
+    }
+    return server.repl_backlog_histlen - skip;
+}
+
+/* This function handles the PSYNC command from the point of view of a
+ * master receiving a request for partial resynchronization.
+ *
+ * On success return REDIS_OK, otherwise REDIS_ERR is returned and we proceed
+ * with the usual full resync. */
+int masterTryPartialResynchronization(redisClient *c) {
+    long long psync_offset, psync_len;
+    char *master_runid = c->argv[1]->ptr;
+
+    /* Is the runid of this master the same advertised by the wannabe slave
+     * via PSYNC? If runid changed this master is a different instance and
+     * there is no way to continue. */
+    if (strcasecmp(master_runid, server.runid)) {
+        /* Run id "?" is used by slaves that want to force a full resync. */
+        if (master_runid[0] != '?') {
+            redisLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
+                "Runid mismatch (Client asked for '%s', I'm '%s')",
+                master_runid, server.runid);
+        } else {
+            redisLog(REDIS_NOTICE,"Full resync requested by slave.");
+        }
+        goto need_full_resync;
+    }
+
+    /* We still have the data our slave is asking for? */
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
+       REDIS_OK) goto need_full_resync;
+    if (!server.repl_backlog ||
+        psync_offset < server.repl_backlog_off ||
+        psync_offset >= (server.repl_backlog_off + server.repl_backlog_size))
+    {
+        redisLog(REDIS_NOTICE,
+            "Unable to partial resync with the slave for lack of backlog (Slave request was: %lld).", psync_offset);
+        goto need_full_resync;
+    }
+
+    /* If we reached this point, we are able to perform a partial resync:
+     * 1) Set client state to make it a slave.
+     * 2) Inform the client we can continue with +CONTINUE
+     * 3) Send the backlog data (from the offset to the end) to the slave. */
+    c->flags |= REDIS_SLAVE;
+    c->replstate = REDIS_REPL_ONLINE;
+    listAddNodeTail(server.slaves,c);
+    addReplySds(c,sdsnew("+CONTINUE\r\n"));
+    psync_len = addReplyReplicationBacklog(c,psync_offset);
+    redisLog(REDIS_NOTICE,
+        "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
+    /* Note that we don't need to set the selected DB at server.slaveseldb
+     * to -1 to force the master to emit SELECT, since the slave already
+     * has this state from the previous connection with the master. */
+
+    return REDIS_OK; /* The caller can return, no full resync needed. */
+
+need_full_resync:
+    /* We need a full resync for some reason... notify the client. */
+    psync_offset = server.master_repl_offset;
+    /* Add 1 to psync_offset if it the replication backlog does not exists
+     * as when it will be created later we'll increment the offset by one. */
+    if (server.repl_backlog == NULL) psync_offset++;
+    addReplySds(c,
+        sdscatprintf(sdsempty(),"+FULLRESYNC %s %lld\r\n",
+        server.runid,
+        psync_offset));
+    return REDIS_ERR;
+}
+
+/* SYNC ad PSYNC command implemenation. */
 void syncCommand(redisClient *c) {
     /* ignore SYNC if already slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
@@ -136,11 +458,24 @@ void syncCommand(redisClient *c) {
      * buffer registering the differences between the BGSAVE and the current
      * dataset, so that we can copy to other slaves if needed. */
     if (listLength(c->reply) != 0) {
-        addReplyError(c,"SYNC is invalid with pending input");
+        addReplyError(c,"SYNC and PSYNC are invalid with pending input");
         return;
     }
 
-    redisLog(REDIS_NOTICE,"Slave ask for synchronization");
+    redisLog(REDIS_NOTICE,"Slave asks for synchronization");
+
+    /* Try a partial resynchronization if this is a PSYNC command.
+     * If it fails, we continue with usual full resynchronization, however
+     * when this happens masterTryPartialResynchronization() already
+     * replied with:
+     *
+     * +FULLRESYNC <runid> <offset>
+     *
+     * So the slave knows the new runid and offset to try a PSYNC later
+     * if the connection with the master is lost. */
+    if (!strcasecmp(c->argv[0]->ptr,"psync") &&
+        masterTryPartialResynchronization(c) == REDIS_OK) return;
+
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
     if (server.rdb_child_pid != -1) {
@@ -185,6 +520,8 @@ void syncCommand(redisClient *c) {
     c->flags |= REDIS_SLAVE;
     server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
     listAddNodeTail(server.slaves,c);
+    if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
+        createReplicationBacklog();
     return;
 }
 
@@ -452,6 +789,9 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.master->flags |= REDIS_MASTER;
         server.master->authenticated = 1;
         server.repl_state = REDIS_REPL_CONNECTED;
+        server.master->reploff = server.repl_master_initial_offset;
+        memcpy(server.master->replrunid, server.repl_master_runid,
+            sizeof(server.repl_master_runid));
         redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
@@ -481,8 +821,8 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 /* Send a synchronous command to the master. Used to send AUTH and
  * REPLCONF commands before starting the replication with SYNC.
  *
- * On success NULL is returned.
- * On error an sds string describing the error is returned.
+ * The command returns an sds string representing the result of the
+ * operation. On error the first byte is a "-".
  */
 char *sendSynchronousCommand(int fd, ...) {
     va_list ap;
@@ -504,30 +844,131 @@ char *sendSynchronousCommand(int fd, ...) {
     /* Transfer command to the server. */
     if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000) == -1) {
         sdsfree(cmd);
-        return sdscatprintf(sdsempty(),"Writing to master: %s",
+        return sdscatprintf(sdsempty(),"-Writing to master: %s",
                 strerror(errno));
     }
     sdsfree(cmd);
 
     /* Read the reply from the server. */
     if (syncReadLine(fd,buf,sizeof(buf),server.repl_syncio_timeout*1000) == -1)
     {
-        return sdscatprintf(sdsempty(),"Reading from master: %s",
+        return sdscatprintf(sdsempty(),"-Reading from master: %s",
                 strerror(errno));
     }
+    return sdsnew(buf);
+}
+
+/* Try a partial resynchronization with the master if we are about to reconnect.
+ * If there is no cached master structure, at least try to issue a
+ * "PSYNC ? -1" command in order to trigger a full resync using the PSYNC
+ * command in order to obtain the master run id and the master replication
+ * global offset.
+ *
+ * This function is designed to be called from syncWithMaster(), so the
+ * following assumptions are made:
+ *
+ * 1) We pass the function an already connected socket "fd".
+ * 2) This function does not close the file descriptor "fd". However in case
+ *    of successful partial resynchronization, the function will reuse
+ *    'fd' as file descriptor of the server.master client structure.
+ *
+ * The function returns:
+ *
+ * PSYNC_CONTINUE: If the PSYNC command succeded and we can continue.
+ * PSYNC_FULLRESYNC: If PSYNC is supported but a full resync is needed.
+ *                   In this case the master run_id and global replication
+ *                   offset is saved.
+ * PSYNC_NOT_SUPPORTED: If the server does not understand PSYNC at all and
+ *                      the caller should fall back to SYNC.
+ */
+
+#define PSYNC_CONTINUE 0
+#define PSYNC_FULLRESYNC 1
+#define PSYNC_NOT_SUPPORTED 2
+int slaveTryPartialResynchronization(int fd) {
+    char *psync_runid;
+    char psync_offset[32];
+    sds reply;
+
+    /* Initially set repl_master_initial_offset to -1 to mark the current
+     * master run_id and offset as not valid. Later if we'll be able to do
+     * a FULL resync using the PSYNC command we'll set the offset at the
+     * right value, so that this information will be propagated to the
+     * client structure representing the master into server.master. */
+    server.repl_master_initial_offset = -1;
+
+    if (server.cached_master) {
+        psync_runid = server.cached_master->replrunid;
+        snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
+        redisLog(REDIS_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+    } else {
+        redisLog(REDIS_NOTICE,"Partial resynchronization not possible (no cached master)");
+        psync_runid = "?";
+        memcpy(psync_offset,"-1",3);
+    }
+
+    /* Issue the PSYNC command */
+    reply = sendSynchronousCommand(fd,"PSYNC",psync_runid,psync_offset,NULL);
+
+    if (!strncmp(reply,"+FULLRESYNC",11)) {
+        char *runid, *offset;
+
+        /* FULL RESYNC, parse the reply in order to extract the run id
+         * and the replication offset. */
+        runid = strchr(reply,' ');
+        if (runid) {
+            runid++;
+            offset = strchr(runid,' ');
+            if (offset) offset++;
+        }
+        if (!runid || !offset || (offset-runid-1) != REDIS_RUN_ID_SIZE) {
+            redisLog(REDIS_WARNING,
+                "Master replied with wrong +FULLRESYNC syntax.");
+        } else {
+            memcpy(server.repl_master_runid, runid, offset-runid-1);
+            server.repl_master_runid[REDIS_RUN_ID_SIZE] = '\0';
+            server.repl_master_initial_offset = strtoll(offset,NULL,10);
+            redisLog(REDIS_NOTICE,"Full resync from master: %s:%lld",
+                server.repl_master_runid,
+                server.repl_master_initial_offset);
+        }
+        /* We are going to full resync, discard the cached master structure. */
+        replicationDiscardCachedMaster();
+        sdsfree(reply);
+        return PSYNC_FULLRESYNC;
+    }
 
-    /* Check for errors from the server. */
-    if (buf[0] != '+') {
-        return sdscatprintf(sdsempty(),"Error from master: %s", buf);
+    if (!strncmp(reply,"+CONTINUE",9)) {
+        /* Partial resync was accepted, set the replication state accordingly */
+        redisLog(REDIS_NOTICE,
+            "Successful partial resynchronization with master.");
+        sdsfree(reply);
+        replicationResurrectCachedMaster(fd);
+        return PSYNC_CONTINUE;
     }
 
-    return NULL; /* No errors. */
+    /* If we reach this point we receied either an error since the master does
+     * not understand PSYNC, or an unexpected reply from the master.
+     * Reply with PSYNC_NOT_SUPPORTED in both cases. */
+
+    if (strncmp(reply,"-ERR",4)) {
+        /* If it's not an error, log the unexpected event. */
+        redisLog(REDIS_WARNING,
+            "Unexpected reply to PSYNC from master: %s", reply);
+    } else {
+        redisLog(REDIS_NOTICE,
+            "Master does not support PSYNC or is in "
+            "error state (reply: %s)", reply);
+    }
+    sdsfree(reply);
+    replicationDiscardCachedMaster();
+    return PSYNC_NOT_SUPPORTED;
 }
 
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     char tmpfile[256], *err;
     int dfd, maxtries = 5;
-    int sockerr = 0;
+    int sockerr = 0, psync_result;
     socklen_t errlen = sizeof(sockerr);
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(privdata);
@@ -600,11 +1041,12 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     /* AUTH with the master if required. */
     if(server.masterauth) {
         err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
-        if (err) {
+        if (err[0] == '-') {
             redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
             sdsfree(err);
             goto error;
         }
+        sdsfree(err);
     }
 
     /* Set the slave port, so that Master's INFO command can list the
@@ -616,17 +1058,33 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         sdsfree(port);
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF listening-port. */
-        if (err) {
-            redisLog(REDIS_NOTICE,"(non critical): Master does not understand REPLCONF listening-port: %s", err);
-            sdsfree(err);
+        if (err[0] == '-') {
+            redisLog(REDIS_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
         }
+        sdsfree(err);
     }
 
-    /* Issue the SYNC command */
-    if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
-        redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
-            strerror(errno));
-        goto error;
+    /* Try a partial resynchonization. If we don't have a cached master
+     * slaveTryPartialResynchronization() will at least try to use PSYNC
+     * to start a full resynchronization so that we get the master run id
+     * and the global offset, to try a partial resync at the next
+     * reconnection attempt. */
+    psync_result = slaveTryPartialResynchronization(fd);
+    if (psync_result == PSYNC_CONTINUE) {
+        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
+        return;
+    }
+
+    /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
+     * and the server.repl_master_runid and repl_master_initial_offset are
+     * already populated. */
+    if (psync_result == PSYNC_NOT_SUPPORTED) {
+        redisLog(REDIS_NOTICE,"Retrying with SYNC...");
+        if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
+            redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
+                strerror(errno));
+            goto error;
+        }
     }
 
     /* Prepare a suitable temp file for bulk transfer */
@@ -733,6 +1191,7 @@ void slaveofCommand(redisClient *c) {
             sdsfree(server.masterhost);
             server.masterhost = NULL;
             if (server.master) freeClient(server.master);
+            replicationDiscardCachedMaster();
             cancelReplicationHandshake();
             server.repl_state = REDIS_REPL_NONE;
             redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
@@ -757,6 +1216,7 @@ void slaveofCommand(redisClient *c) {
         server.masterport = port;
         if (server.master) freeClient(server.master);
         disconnectSlaves(); /* Force our slaves to resync with us as well. */
+        replicationDiscardCachedMaster(); /* Don't try a PSYNC. */
         cancelReplicationHandshake();
         server.repl_state = REDIS_REPL_CONNECT;
         redisLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
@@ -765,6 +1225,92 @@ void slaveofCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
+/* ---------------------- MASTER CACHING FOR PSYNC -------------------------- */
+
+/* In order to implement partial synchronization we need to be able to cache
+ * our master's client structure after a transient disconnection.
+ * It is cached into server.cached_master and flushed away using the following
+ * functions. */
+
+/* This function is called by freeClient() in order to cache the master
+ * client structure instead of destryoing it. freeClient() will return
+ * ASAP after this function returns, so every action needed to avoid problems
+ * with a client that is really "suspended" has to be done by this function.
+ *
+ * The other functions that will deal with the cached master are:
+ *
+ * replicationDiscardCachedMaster() that will make sure to kill the client
+ * as for some reason we don't want to use it in the future.
+ *
+ * replicationResurrectCachedMaster() that is used after a successful PSYNC
+ * handshake in order to reactivate the cached master.
+ */
+void replicationCacheMaster(redisClient *c) {
+    listNode *ln;
+
+    redisAssert(server.master != NULL && server.cached_master == NULL);
+    redisLog(REDIS_NOTICE,"Caching the disconnected master state.");
+
+    /* Remove from the list of clients, we don't want this client to be
+     * listed by CLIENT LIST or processed in any way by batch operations. */
+    ln = listSearchKey(server.clients,c);
+    redisAssert(ln != NULL);
+    listDelNode(server.clients,ln);
+
+    /* Save the master. Server.master will be set to null later by
+     * replicationHandleMasterDisconnection(). */
+    server.cached_master = server.master;
+
+    /* Remove the event handlers and close the socket. We'll later reuse
+     * the socket of the new connection with the master during PSYNC. */
+    aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
+    aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
+    close(c->fd);
+
+    /* Set fd to -1 so that we can safely call freeClient(c) later. */
+    c->fd = -1;
+
+    /* Caching the master happens instead of the actual freeClient() call,
+     * so make sure to adjust the replication state. This function will
+     * also set server.master to NULL. */
+    replicationHandleMasterDisconnection();
+}
+
+/* Free a cached master, called when there are no longer the conditions for
+ * a partial resync on reconnection. */
+void replicationDiscardCachedMaster(void) {
+    if (server.cached_master == NULL) return;
+
+    redisLog(REDIS_NOTICE,"Discarding previously cached master state.");
+    server.cached_master->flags &= ~REDIS_MASTER;
+    freeClient(server.cached_master);
+    server.cached_master = NULL;
+}
+
+/* Turn the cached master into the current master, using the file descriptor
+ * passed as argument as the socket for the new master.
+ *
+ * This funciton is called when successfully setup a partial resynchronization
+ * so the stream of data that we'll receive will start from were this
+ * master left. */
+void replicationResurrectCachedMaster(int newfd) {
+    server.master = server.cached_master;
+    server.cached_master = NULL;
+    server.master->fd = newfd;
+    server.master->flags &= ~(REDIS_CLOSE_AFTER_REPLY|REDIS_CLOSE_ASAP);
+    server.master->authenticated = 1;
+    server.master->lastinteraction = server.unixtime;
+    server.repl_state = REDIS_REPL_CONNECTED;
+
+    /* Re-add to the list of clients. */
+    listAddNodeTail(server.clients,server.master);
+    if (aeCreateFileEvent(server.el, newfd, AE_READABLE,
+                          readQueryFromClient, server.master)) {
+        redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
+        freeClientAsync(server.master); /* Close ASAP. */
+    }
+}
+
 /* --------------------------- REPLICATION CRON  ---------------------------- */
 
 void replicationCron(void) {
@@ -816,8 +1362,8 @@ void replicationCron(void) {
         replicationFeedSlaves(server.slaves, server.slaveseldb, ping_argv, 1);
         decrRefCount(ping_argv[0]);
 
-        /* Second, send a newline to all the slaves in pre-synchronization stage,
-         * that is, slaves waiting for the master to create the RDB file.
+        /* Second, send a newline to all the slaves in pre-synchronization
+         * stage, that is, slaves waiting for the master to create the RDB file.
          * The newline will be ignored by the slave but will refresh the
          * last-io timer preventing a timeout. */
         listRewind(server.slaves,&li);
@@ -832,4 +1378,19 @@ void replicationCron(void) {
             }
         }
     }
+
+    /* If we have no attached slaves and there is a replication backlog
+     * using memory, free it after some (configured) time. */
+    if (listLength(server.slaves) == 0 && server.repl_backlog_time_limit &&
+        server.repl_backlog)
+    {
+        time_t idle = server.unixtime - server.repl_no_slaves_since;
+
+        if (idle > server.repl_backlog_time_limit) {
+            freeReplicationBacklog();
+            redisLog(REDIS_NOTICE,
+                "Replication backlog freed after %d seconds "
+                "without connected slaves.", server.repl_backlog_time_limit);
+        }
+    }
 }