@@ -145,6 +145,46 @@ void syncCommand(redisClient *c) {
     return;
 }
 
+/* REPLCONF <option> <value> <option> <value> ...
+ * This command is used by a slave in order to configure the replication
+ * process before starting it with the SYNC command.
+ *
+ * Currently the only use of this command is to communicate to the master
+ * what is the listening port of the Slave redis instance, so that the
+ * master can accurately list slaves and their listening ports in
+ * the INFO output.
+ *
+ * In the future the same command can be used in order to configure
+ * the replication to initiate an incremental replication instead of a
+ * full resync. */
+void replconfCommand(redisClient *c) {
+    int j;
+
+    if ((c->argc % 2) == 0) {
+        /* Number of arguments must be odd to make sure that every
+         * option has a corresponding value. */
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+
+    /* Process every option-value pair. */
+    for (j = 1; j < c->argc; j+=2) {
+        if (!strcasecmp(c->argv[j]->ptr,"listening-port")) {
+            long port;
+
+            if ((getLongFromObjectOrReply(c,c->argv[j+1],
+                    &port,NULL) != REDIS_OK))
+                return;
+            c->slave_listening_port = port;
+        } else {
+            addReplyErrorFormat(c,"Unrecognized REPLCONF option: %s",
+                (char*)c->argv[j]->ptr);
+            return;
+        }
+    }
+    addReply(c,shared.ok);
+}
+
 void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *slave = privdata;
     REDIS_NOTUSED(el);
@@ -378,8 +418,54 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     return;
 }
 
+/* Send a synchronous command to the master. Used to send AUTH and
+ * REPLCONF commadns before starting the replication with SYNC.
+ *
+ * On success NULL is returned.
+ * On error an sds string describing the error is returned.
+ */
+char *sendSynchronousCommand(int fd, ...) {
+    va_list ap;
+    sds cmd = sdsempty();
+    char *arg, buf[256];
+
+    /* Create the command to send to the master, we use simple inline
+     * protocol for simplicity as currently we only send simple strings. */
+    va_start(ap,fd);
+    while(1) {
+        arg = va_arg(ap, char*);
+        if (arg == NULL) break;
+
+        if (sdslen(cmd) != 0) cmd = sdscatlen(cmd," ",1);
+        cmd = sdscat(cmd,arg);
+    }
+    cmd = sdscatlen(cmd,"\r\n",2);
+
+    /* Transfer command to the server. */
+    if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000) == -1) {
+        sdsfree(cmd);
+        return sdscatprintf(sdsempty(),"Writing to master: %s",
+                strerror(errno));
+    }
+    sdsfree(cmd);
+
+    /* Read the reply from the server. */
+    if (syncReadLine(fd,buf,sizeof(buf),server.repl_syncio_timeout*1000) == -1)
+    {
+        return sdscatprintf(sdsempty(),"Reading from master: %s",
+                strerror(errno));
+    }
+
+    /* Check for errors from the server. */
+    if (buf[0] != '+') {
+        return sdscatprintf(sdsempty(),"Error from master: %s", buf);
+    }
+
+    return NULL; /* No errors. */
+}
+
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
-    char buf[1024], tmpfile[256];
+    char tmpfile[256], *err;
     int dfd, maxtries = 5;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(privdata);
@@ -400,24 +486,26 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     /* AUTH with the master if required. */
     if(server.masterauth) {
-        char authcmd[1024];
-        size_t authlen;
-
-        authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
-        if (syncWrite(fd,authcmd,authlen,server.repl_syncio_timeout*1000) == -1) {
-            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
-                strerror(errno));
-            goto error;
-        }
-        /* Read the AUTH result.  */
-        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
-            redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
-                strerror(errno));
+        err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
+        if (err) {
+            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
+            sdsfree(err);
             goto error;
         }
-        if (buf[0] != '+') {
-            redisLog(REDIS_WARNING,"Cannot AUTH to MASTER, is the masterauth password correct?");
-            goto error;
+    }
+
+    /* Set the slave port, so that Master's INFO command can list the
+     * slave listening port correctly. */
+    {
+        sds port = sdsfromlonglong(server.port);
+        err = sendSynchronousCommand(fd,"REPLCONF","listening-port",port,
+                                         NULL);
+        sdsfree(port);
+        /* Ignore the error if any, not all the Redis versions support
+         * REPLCONF listening-port. */
+        if (err) {
+            redisLog(REDIS_NOTICE,"(non critical): Master does not understand REPLCONF listening-port: %s", err);
+            sdsfree(err);
         }
     }
 