@@ -10,46 +10,18 @@
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
-    int outc = 0, j;
-    robj **outv;
-    /* We need 1+(ARGS*3) objects since commands are using the new protocol
-     * and we one 1 object for the first "*<count>\r\n" multibulk count, then
-     * for every additional object we have "$<count>\r\n" + object + "\r\n". */
-    robj *static_outv[REDIS_STATIC_ARGS*3+1];
-    robj *lenobj;
-
-    if (argc <= REDIS_STATIC_ARGS) {
-        outv = static_outv;
-    } else {
-        outv = zmalloc(sizeof(robj*)*(argc*3+1));
-    }
-
-    lenobj = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(), "*%d\r\n", argc));
-    lenobj->refcount = 0;
-    outv[outc++] = lenobj;
-    for (j = 0; j < argc; j++) {
-        lenobj = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(),"$%lu\r\n",
-                (unsigned long) stringObjectLen(argv[j])));
-        lenobj->refcount = 0;
-        outv[outc++] = lenobj;
-        outv[outc++] = argv[j];
-        outv[outc++] = shared.crlf;
-    }
+    int j;
 
-    /* Increment all the refcounts at start and decrement at end in order to
-     * be sure to free objects if there is no slave in a replication state
-     * able to be feed with commands */
-    for (j = 0; j < outc; j++) incrRefCount(outv[j]);
     listRewind(slaves,&li);
     while((ln = listNext(&li))) {
         redisClient *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;
 
-        /* Feed all the other slaves, MONITORs and so on */
+        /* Feed slaves that are waiting for the initial SYNC (so these commands
+         * are queued in the output buffer until the intial SYNC completes),
+         * or are already in sync with the master. */
         if (slave->slaveseldb != dictid) {
             robj *selectcmd;
 
@@ -73,10 +45,9 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
             addReply(slave,selectcmd);
             slave->slaveseldb = dictid;
         }
-        for (j = 0; j < outc; j++) addReply(slave,outv[j]);
+        addReplyMultiBulkLen(slave,argc);
+        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
     }
-    for (j = 0; j < outc; j++) decrRefCount(outv[j]);
-    if (outv != static_outv) zfree(outv);
 }
 
 void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc) {
@@ -315,19 +286,18 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     /* If repl_transfer_left == -1 we still have to read the bulk length
      * from the master reply. */
     if (server.repl_transfer_left == -1) {
-        if (syncReadLine(fd,buf,1024,3600) == -1) {
+        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
                 strerror(errno));
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         }
+
         if (buf[0] == '-') {
             redisLog(REDIS_WARNING,
                 "MASTER aborted replication with an error: %s",
                 buf+1);
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         } else if (buf[0] == '\0') {
             /* At this stage just a newline works as a PING in order to take
              * the connection live. So we refresh our last interaction
@@ -336,8 +306,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             return;
         } else if (buf[0] != '$') {
             redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         }
         server.repl_transfer_left = strtol(buf+1,NULL,10);
         redisLog(REDIS_NOTICE,
@@ -359,8 +328,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     server.repl_transfer_lastio = time(NULL);
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
         redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
-        replicationAbortSyncTransfer();
-        return;
+        goto error;
     }
     server.repl_transfer_left -= nread;
     /* Check if the transfer is now complete */
@@ -390,49 +358,58 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.master->authenticated = 1;
         server.replstate = REDIS_REPL_CONNECTED;
         redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
+        /* Rewrite the AOF file now that the dataset changed. */
+        if (server.appendonly) rewriteAppendOnlyFileBackground();
     }
+
+    return;
+
+error:
+    replicationAbortSyncTransfer();
+    return;
 }
 
-int syncWithMaster(void) {
-    char buf[1024], tmpfile[256], authcmd[1024];
-    int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
+void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
+    char buf[1024], tmpfile[256];
     int dfd, maxtries = 5;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(privdata);
+    REDIS_NOTUSED(mask);
 
-    if (fd == -1) {
-        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
+    redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
+    /* This event should only be triggered once since it is used to have a
+     * non-blocking connect(2) to the master. It has been triggered when this
+     * function is called, so we can delete it. */
+    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
 
     /* AUTH with the master if required. */
     if(server.masterauth) {
-    	snprintf(authcmd, 1024, "AUTH %s\r\n", server.masterauth);
-    	if (syncWrite(fd, authcmd, strlen(server.masterauth)+7, 5) == -1) {
-            close(fd);
+        char authcmd[1024];
+        size_t authlen;
+
+        authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
+        if (syncWrite(fd,authcmd,authlen,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                 strerror(errno));
-            return REDIS_ERR;
-    	}
+            goto error;
+        }
         /* Read the AUTH result.  */
-        if (syncReadLine(fd,buf,1024,3600) == -1) {
-            close(fd);
+        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout) == -1) {
             redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
                 strerror(errno));
-            return REDIS_ERR;
+            goto error;
         }
         if (buf[0] != '+') {
-            close(fd);
             redisLog(REDIS_WARNING,"Cannot AUTH to MASTER, is the masterauth password correct?");
-            return REDIS_ERR;
+            goto error;
         }
     }
 
     /* Issue the SYNC command */
-    if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
-        close(fd);
+    if (syncWrite(fd,"SYNC \r\n",7,server.repl_syncio_timeout) == -1) {
         redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
             strerror(errno));
-        return REDIS_ERR;
+        goto error;
     }
 
     /* Prepare a suitable temp file for bulk transfer */
@@ -444,25 +421,51 @@ int syncWithMaster(void) {
         sleep(1);
     }
     if (dfd == -1) {
-        close(fd);
         redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
-        return REDIS_ERR;
+        goto error;
     }
 
     /* Setup the non blocking download of the bulk file. */
-    if (aeCreateFileEvent(server.el, fd, AE_READABLE, readSyncBulkPayload, NULL)
+    if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
             == AE_ERR)
     {
-        close(fd);
         redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
-        return REDIS_ERR;
+        goto error;
     }
+
     server.replstate = REDIS_REPL_TRANSFER;
     server.repl_transfer_left = -1;
-    server.repl_transfer_s = fd;
     server.repl_transfer_fd = dfd;
     server.repl_transfer_lastio = time(NULL);
     server.repl_transfer_tmpfile = zstrdup(tmpfile);
+    return;
+
+error:
+    server.replstate = REDIS_REPL_CONNECT;
+    close(fd);
+    return;
+}
+
+int connectWithMaster(void) {
+    int fd;
+
+    fd = anetTcpNonBlockConnect(NULL,server.masterhost,server.masterport);
+    if (fd == -1) {
+        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    }
+
+    if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,syncWithMaster,NULL) ==
+            AE_ERR)
+    {
+        close(fd);
+        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
+        return REDIS_ERR;
+    }
+
+    server.repl_transfer_s = fd;
+    server.replstate = REDIS_REPL_CONNECTING;
     return REDIS_OK;
 }
 
@@ -517,9 +520,8 @@ void replicationCron(void) {
     /* Check if we should connect to a MASTER */
     if (server.replstate == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
-        if (syncWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started: SYNC sent");
-            if (server.appendonly) rewriteAppendOnlyFileBackground();
+        if (connectWithMaster() == REDIS_OK) {
+            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
         }
     }
     