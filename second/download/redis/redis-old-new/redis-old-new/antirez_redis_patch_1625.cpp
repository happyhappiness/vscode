@@ -393,46 +393,44 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
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
+    /* Remove this event before anything else. */
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
+        if (syncWrite(fd,authcmd,authlen,5) == -1) {
             redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                 strerror(errno));
-            return REDIS_ERR;
-    	}
+            goto error;
+        }
         /* Read the AUTH result.  */
         if (syncReadLine(fd,buf,1024,3600) == -1) {
-            close(fd);
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
     if (syncWrite(fd,"SYNC \r\n",7,5) == -1) {
-        close(fd);
         redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
             strerror(errno));
-        return REDIS_ERR;
+        goto error;
     }
 
     /* Prepare a suitable temp file for bulk transfer */
@@ -444,25 +442,51 @@ int syncWithMaster(void) {
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
+    if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,
+            syncWithMaster,NULL) == AE_ERR)
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
 
@@ -517,8 +541,8 @@ void replicationCron(void) {
     /* Check if we should connect to a MASTER */
     if (server.replstate == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
-        if (syncWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started: SYNC sent");
+        if (connectWithMaster() == REDIS_OK) {
+            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
             if (server.appendonly) rewriteAppendOnlyFileBackground();
         }
     }