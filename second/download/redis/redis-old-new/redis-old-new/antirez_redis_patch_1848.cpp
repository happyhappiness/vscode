@@ -5,6 +5,8 @@
 #include <fcntl.h>
 #include <sys/stat.h>
 
+/* ---------------------------------- MASTER -------------------------------- */
+
 void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
@@ -288,9 +290,101 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
     }
 }
 
+/* ----------------------------------- SLAVE -------------------------------- */
+
+/* Abort the async download of the bulk dataset while SYNC-ing with master */
+void replicationAbortSyncTransfer(void) {
+    redisAssert(server.replstate == REDIS_REPL_TRANSFER);
+
+    aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
+    close(server.repl_transfer_s);
+    close(server.repl_transfer_fd);
+    unlink(server.repl_transfer_tmpfile);
+    zfree(server.repl_transfer_tmpfile);
+    server.replstate = REDIS_REPL_CONNECT;
+}
+
+/* Asynchronously read the SYNC payload we receive from a master */
+void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
+    char buf[4096];
+    ssize_t nread, readlen;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(privdata);
+    REDIS_NOTUSED(mask);
+
+    /* If repl_transfer_left == -1 we still have to read the bulk length
+     * from the master reply. */
+    if (server.repl_transfer_left == -1) {
+        if (syncReadLine(fd,buf,1024,3600) == -1) {
+            redisLog(REDIS_WARNING,
+                "I/O error reading bulk count from MASTER: %s",
+                strerror(errno));
+            replicationAbortSyncTransfer();
+            return;
+        }
+        if (buf[0] == '-') {
+            redisLog(REDIS_WARNING,
+                "MASTER aborted replication with an error: %s",
+                buf+1);
+            replicationAbortSyncTransfer();
+            return;
+        } else if (buf[0] != '$') {
+            redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
+            replicationAbortSyncTransfer();
+            return;
+        }
+        server.repl_transfer_left = strtol(buf+1,NULL,10);
+        redisLog(REDIS_NOTICE,
+            "MASTER <-> SLAVE sync: receiving %ld bytes from master",
+            server.repl_transfer_left);
+        return;
+    }
+
+    /* Read bulk data */
+    readlen = (server.repl_transfer_left < (signed)sizeof(buf)) ?
+        server.repl_transfer_left : (signed)sizeof(buf);
+    nread = read(fd,buf,readlen);
+    if (nread <= 0) {
+        redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
+            (nread == -1) ? strerror(errno) : "connection lost");
+        replicationAbortSyncTransfer();
+        return;
+    }
+    server.repl_transfer_lastio = time(NULL);
+    if (write(server.repl_transfer_fd,buf,nread) != nread) {
+        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
+        replicationAbortSyncTransfer();
+        return;
+    }
+    server.repl_transfer_left -= nread;
+    /* Check if the transfer is now complete */
+    if (server.repl_transfer_left == 0) {
+        if (rename(server.repl_transfer_tmpfile,server.dbfilename) == -1) {
+            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
+            replicationAbortSyncTransfer();
+            return;
+        }
+        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
+        emptyDb();
+        if (rdbLoad(server.dbfilename) != REDIS_OK) {
+            redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
+            replicationAbortSyncTransfer();
+            return;
+        }
+        /* Final setup of the connected slave <- master link */
+        aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
+        zfree(server.repl_transfer_tmpfile);
+        close(server.repl_transfer_fd);
+        server.master = createClient(server.repl_transfer_s);
+        server.master->flags |= REDIS_MASTER;
+        server.master->authenticated = 1;
+        server.replstate = REDIS_REPL_CONNECTED;
+        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
+    }
+}
+
 int syncWithMaster(void) {
     char buf[1024], tmpfile[256], authcmd[1024];
-    long dumpsize;
     int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
     int dfd, maxtries = 5;
 
@@ -330,26 +424,8 @@ int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
-    /* Read the bulk write count */
-    if (syncReadLine(fd,buf,1024,3600) == -1) {
-        close(fd);
-        redisLog(REDIS_WARNING,"I/O error reading bulk count from MASTER: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-    if (buf[0] == '-') {
-        close(fd);
-        redisLog(REDIS_WARNING,"MASTER aborted replication with an error: %s",
-            buf+1);
-        return REDIS_ERR;
-    } else if (buf[0] != '$') {
-        close(fd);
-        redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
-        return REDIS_ERR;
-    }
-    dumpsize = strtol(buf+1,NULL,10);
-    redisLog(REDIS_NOTICE,"Receiving %ld bytes data dump from MASTER",dumpsize);
-    /* Read the bulk write data on a temp file */
+
+    /* Prepare a suitable temp file for bulk transfer */
     while(maxtries--) {
         snprintf(tmpfile,256,
             "temp-%d.%ld.rdb",(int)time(NULL),(long int)getpid());
@@ -362,43 +438,21 @@ int syncWithMaster(void) {
         redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
         return REDIS_ERR;
     }
-    while(dumpsize) {
-        int nread, nwritten;
 
-        nread = read(fd,buf,(dumpsize < 1024)?dumpsize:1024);
-        if (nread <= 0) {
-            redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
-                (nread == -1) ? strerror(errno) : "connection lost");
-            close(fd);
-            close(dfd);
-            return REDIS_ERR;
-        }
-        nwritten = write(dfd,buf,nread);
-        if (nwritten == -1) {
-            redisLog(REDIS_WARNING,"Write error writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
-            close(fd);
-            close(dfd);
-            return REDIS_ERR;
-        }
-        dumpsize -= nread;
-    }
-    close(dfd);
-    if (rename(tmpfile,server.dbfilename) == -1) {
-        redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
-        unlink(tmpfile);
+    /* Setup the non blocking download of the bulk file. */
+    if (aeCreateFileEvent(server.el, fd, AE_READABLE, readSyncBulkPayload, NULL)
+            == AE_ERR)
+    {
         close(fd);
+        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
         return REDIS_ERR;
     }
-    emptyDb();
-    if (rdbLoad(server.dbfilename) != REDIS_OK) {
-        redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
-        close(fd);
-        return REDIS_ERR;
-    }
-    server.master = createClient(fd);
-    server.master->flags |= REDIS_MASTER;
-    server.master->authenticated = 1;
-    server.replstate = REDIS_REPL_CONNECTED;
+    server.replstate = REDIS_REPL_TRANSFER;
+    server.repl_transfer_left = -1;
+    server.repl_transfer_s = fd;
+    server.repl_transfer_fd = dfd;
+    server.repl_transfer_lastio = time(NULL);
+    server.repl_transfer_tmpfile = zstrdup(tmpfile);
     return REDIS_OK;
 }
 
@@ -409,6 +463,8 @@ void slaveofCommand(redisClient *c) {
             sdsfree(server.masterhost);
             server.masterhost = NULL;
             if (server.master) freeClient(server.master);
+            if (server.replstate == REDIS_REPL_TRANSFER)
+                replicationAbortSyncTransfer();
             server.replstate = REDIS_REPL_NONE;
             redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
         }
@@ -417,9 +473,34 @@ void slaveofCommand(redisClient *c) {
         server.masterhost = sdsdup(c->argv[1]->ptr);
         server.masterport = atoi(c->argv[2]->ptr);
         if (server.master) freeClient(server.master);
+        if (server.replstate == REDIS_REPL_TRANSFER)
+            replicationAbortSyncTransfer();
         server.replstate = REDIS_REPL_CONNECT;
         redisLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
             server.masterhost, server.masterport);
     }
     addReply(c,shared.ok);
 }
+
+/* --------------------------- REPLICATION CRON  ---------------------------- */
+
+#define REDIS_REPL_TRANSFER_TIMEOUT 60
+
+void replicationCron(void) {
+    /* Bulk transfer I/O timeout? */
+    if (server.masterhost && server.replstate == REDIS_REPL_TRANSFER &&
+        (time(NULL)-server.repl_transfer_lastio) > REDIS_REPL_TRANSFER_TIMEOUT)
+    {
+        redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER...");
+        replicationAbortSyncTransfer();
+    }
+
+    /* Check if we should connect to a MASTER */
+    if (server.replstate == REDIS_REPL_CONNECT) {
+        redisLog(REDIS_NOTICE,"Connecting to MASTER...");
+        if (syncWithMaster() == REDIS_OK) {
+            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started: SYNC sent");
+            if (server.appendonly) rewriteAppendOnlyFileBackground();
+        }
+    }
+}