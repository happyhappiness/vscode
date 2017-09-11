@@ -1132,38 +1132,53 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
  * The command returns an sds string representing the result of the
  * operation. On error the first byte is a "-".
  */
-char *sendSynchronousCommand(int fd, ...) {
-    va_list ap;
-    sds cmd = sdsempty();
-    char *arg, buf[256];
+#define SYNC_CMD_READ (1<<0)
+#define SYNC_CMD_WRITE (1<<1)
+#define SYNC_CMD_FULL (SYNC_CMD_READ|SYNC_CMD_WRITE)
+char *sendSynchronousCommand(int flags, int fd, ...) {
 
     /* Create the command to send to the master, we use simple inline
      * protocol for simplicity as currently we only send simple strings. */
-    va_start(ap,fd);
-    while(1) {
-        arg = va_arg(ap, char*);
-        if (arg == NULL) break;
-
-        if (sdslen(cmd) != 0) cmd = sdscatlen(cmd," ",1);
-        cmd = sdscat(cmd,arg);
-    }
-    cmd = sdscatlen(cmd,"\r\n",2);
+    if (flags & SYNC_CMD_WRITE) {
+        char *arg;
+        va_list ap;
+        sds cmd = sdsempty();
+        va_start(ap,fd);
+
+        while(1) {
+            arg = va_arg(ap, char*);
+            if (arg == NULL) break;
+
+            if (sdslen(cmd) != 0) cmd = sdscatlen(cmd," ",1);
+            cmd = sdscat(cmd,arg);
+        }
+        cmd = sdscatlen(cmd,"\r\n",2);
 
-    /* Transfer command to the server. */
-    if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000) == -1) {
+        /* Transfer command to the server. */
+        if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000)
+            == -1)
+        {
+            sdsfree(cmd);
+            return sdscatprintf(sdsempty(),"-Writing to master: %s",
+                    strerror(errno));
+        }
         sdsfree(cmd);
-        return sdscatprintf(sdsempty(),"-Writing to master: %s",
-                strerror(errno));
+        va_end(ap);
     }
-    sdsfree(cmd);
 
     /* Read the reply from the server. */
-    if (syncReadLine(fd,buf,sizeof(buf),server.repl_syncio_timeout*1000) == -1)
-    {
-        return sdscatprintf(sdsempty(),"-Reading from master: %s",
-                strerror(errno));
+    if (flags & SYNC_CMD_READ) {
+        char buf[256];
+
+        if (syncReadLine(fd,buf,sizeof(buf),server.repl_syncio_timeout*1000)
+            == -1)
+        {
+            return sdscatprintf(sdsempty(),"-Reading from master: %s",
+                    strerror(errno));
+        }
+        return sdsnew(buf);
     }
-    return sdsnew(buf);
+    return NULL;
 }
 
 /* Try a partial resynchronization with the master if we are about to reconnect.
@@ -1180,6 +1195,19 @@ char *sendSynchronousCommand(int fd, ...) {
  *    of successful partial resynchronization, the function will reuse
  *    'fd' as file descriptor of the server.master client structure.
  *
+ * The function is split in two halves: if read_reply is 0, the function
+ * writes the PSYNC command on the socket, and a new function call is
+ * needed, with read_reply set to 1, in order to read the reply of the
+ * command. This is useful in order to support non blocking operations, so
+ * that we write, return into the event loop, and read when there are data.
+ *
+ * When read_reply is 0 the function returns PSYNC_WRITE_ERR if there
+ * was a write error, or PSYNC_WAIT_REPLY to signal we need another call
+ * with read_reply set to 1. However even when read_reply is set to 1
+ * the function may return PSYNC_WAIT_REPLY again to signal there were
+ * insufficient data to read to complete its work. We should re-enter
+ * into the event loop and wait in such a case.
+ *
  * The function returns:
  *
  * PSYNC_CONTINUE: If the PSYNC command succeded and we can continue.
@@ -1188,35 +1216,57 @@ char *sendSynchronousCommand(int fd, ...) {
  *                   offset is saved.
  * PSYNC_NOT_SUPPORTED: If the server does not understand PSYNC at all and
  *                      the caller should fall back to SYNC.
+ * PSYNC_WRITE_ERR: There was an error writing the command to the socket.
+ * PSYNC_WAIT_REPLY: Call again the function with read_reply set to 1.
  */
 
-#define PSYNC_CONTINUE 0
-#define PSYNC_FULLRESYNC 1
-#define PSYNC_NOT_SUPPORTED 2
-int slaveTryPartialResynchronization(int fd) {
+#define PSYNC_WRITE_ERROR 0
+#define PSYNC_WAIT_REPLY 1
+#define PSYNC_CONTINUE 2
+#define PSYNC_FULLRESYNC 3
+#define PSYNC_NOT_SUPPORTED 4
+int slaveTryPartialResynchronization(int fd, int read_reply) {
     char *psync_runid;
     char psync_offset[32];
     sds reply;
 
-    /* Initially set repl_master_initial_offset to -1 to mark the current
-     * master run_id and offset as not valid. Later if we'll be able to do
-     * a FULL resync using the PSYNC command we'll set the offset at the
-     * right value, so that this information will be propagated to the
-     * client structure representing the master into server.master. */
-    server.repl_master_initial_offset = -1;
-
-    if (server.cached_master) {
-        psync_runid = server.cached_master->replrunid;
-        snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
-        serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
-    } else {
-        serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
-        psync_runid = "?";
-        memcpy(psync_offset,"-1",3);
+    /* Writing half */
+    if (!read_reply) {
+        /* Initially set repl_master_initial_offset to -1 to mark the current
+         * master run_id and offset as not valid. Later if we'll be able to do
+         * a FULL resync using the PSYNC command we'll set the offset at the
+         * right value, so that this information will be propagated to the
+         * client structure representing the master into server.master. */
+        server.repl_master_initial_offset = -1;
+
+        if (server.cached_master) {
+            psync_runid = server.cached_master->replrunid;
+            snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
+            serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
+        } else {
+            serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
+            psync_runid = "?";
+            memcpy(psync_offset,"-1",3);
+        }
+
+        /* Issue the PSYNC command */
+        reply = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PSYNC",psync_runid,psync_offset,NULL);
+        if (reply != NULL) {
+            serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
+            sdsfree(reply);
+            return PSYNC_WRITE_ERROR;
+        }
+        return PSYNC_WAIT_REPLY;
     }
 
-    /* Issue the PSYNC command */
-    reply = sendSynchronousCommand(fd,"PSYNC",psync_runid,psync_offset,NULL);
+    /* Reading half */
+    reply = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
+    if (sdslen(reply) == 0) {
+        /* The master may send empty newlines after it receives PSYNC
+         * and before to reply, just to keep the connection alive. */
+        sdsfree(reply);
+        return PSYNC_WAIT_REPLY;
+    }
 
     if (!strncmp(reply,"+FULLRESYNC",11)) {
         char *runid = NULL, *offset = NULL;
@@ -1260,7 +1310,7 @@ int slaveTryPartialResynchronization(int fd) {
         return PSYNC_CONTINUE;
     }
 
-    /* If we reach this point we receied either an error since the master does
+    /* If we reach this point we received either an error since the master does
      * not understand PSYNC, or an unexpected reply from the master.
      * Return PSYNC_NOT_SUPPORTED to the caller in both cases. */
 
@@ -1279,7 +1329,7 @@ int slaveTryPartialResynchronization(int fd) {
 }
 
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
-    char tmpfile[256], *err;
+    char tmpfile[256], *err = NULL;
     int dfd, maxtries = 5;
     int sockerr = 0, psync_result;
     socklen_t errlen = sizeof(sockerr);
@@ -1304,10 +1354,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         goto error;
     }
 
-    /* If we were connecting, it's time to send a non blocking PING, we want to
-     * make sure the master is able to reply before going into the actual
-     * replication process where we have long timeouts in the order of
-     * seconds (in the meantime the slave would block). */
+    /* Send a PING to check the master is able to reply without errors. */
     if (server.repl_state == REPL_STATE_CONNECTING) {
         serverLog(LL_NOTICE,"Non blocking connect for SYNC fired the event.");
         /* Delete the writable event so that the readable event remains
@@ -1316,95 +1363,148 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.repl_state = REPL_STATE_RECEIVE_PONG;
         /* Send the PING, don't check for errors at all, we have the timeout
          * that will take care about this. */
-        syncWrite(fd,"PING\r\n",6,100);
+        err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"PING",NULL);
+        if (err) goto write_error;
         return;
     }
 
     /* Receive the PONG command. */
     if (server.repl_state == REPL_STATE_RECEIVE_PONG) {
-        char buf[1024];
-
-        /* Delete the readable event, we no longer need it now that there is
-         * the PING reply to read. */
-        aeDeleteFileEvent(server.el,fd,AE_READABLE);
-
-        /* Read the reply with explicit timeout. */
-        buf[0] = '\0';
-        if (syncReadLine(fd,buf,sizeof(buf),
-            server.repl_syncio_timeout*1000) == -1)
-        {
-            serverLog(LL_WARNING,
-                "I/O error reading PING reply from master: %s",
-                strerror(errno));
-            goto error;
-        }
+        err = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
 
         /* We accept only two replies as valid, a positive +PONG reply
          * (we just check for "+") or an authentication error.
          * Note that older versions of Redis replied with "operation not
          * permitted" instead of using a proper error code, so we test
          * both. */
-        if (buf[0] != '+' &&
-            strncmp(buf,"-NOAUTH",7) != 0 &&
-            strncmp(buf,"-ERR operation not permitted",28) != 0)
+        if (err[0] != '+' &&
+            strncmp(err,"-NOAUTH",7) != 0 &&
+            strncmp(err,"-ERR operation not permitted",28) != 0)
         {
-            serverLog(LL_WARNING,"Error reply to PING from master: '%s'",buf);
+            serverLog(LL_WARNING,"Error reply to PING from master: '%s'",err);
+            sdsfree(err);
             goto error;
         } else {
             serverLog(LL_NOTICE,
                 "Master replied to PING, replication can continue...");
         }
+        sdsfree(err);
+        server.repl_state = REPL_STATE_SEND_AUTH;
     }
 
     /* AUTH with the master if required. */
-    if(server.masterauth) {
-        err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
+    if (server.repl_state == REPL_STATE_SEND_AUTH) {
+        if (server.masterauth) {
+            err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"AUTH",server.masterauth,NULL);
+            if (err) goto write_error;
+            server.repl_state = REPL_STATE_RECEIVE_AUTH;
+            return;
+        } else {
+            server.repl_state = REPL_STATE_SEND_PORT;
+        }
+    }
+
+    /* Receive AUTH reply. */
+    if (server.repl_state == REPL_STATE_RECEIVE_AUTH) {
+        err = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
         if (err[0] == '-') {
             serverLog(LL_WARNING,"Unable to AUTH to MASTER: %s",err);
             sdsfree(err);
             goto error;
         }
         sdsfree(err);
+        server.repl_state = REPL_STATE_SEND_PORT;
     }
 
     /* Set the slave port, so that Master's INFO command can list the
      * slave listening port correctly. */
-    {
+    if (server.repl_state == REPL_STATE_SEND_PORT) {
         sds port = sdsfromlonglong(server.port);
-        err = sendSynchronousCommand(fd,"REPLCONF","listening-port",port,
-                                         NULL);
+        err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"REPLCONF",
+                "listening-port",port, NULL);
         sdsfree(port);
+        if (err) goto write_error;
+        sdsfree(err);
+        server.repl_state = REPL_STATE_RECEIVE_PORT;
+        return;
+    }
+
+    /* Receive REPLCONF listening-port reply. */
+    if (server.repl_state == REPL_STATE_RECEIVE_PORT) {
+        err = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF listening-port. */
         if (err[0] == '-') {
             serverLog(LL_NOTICE,"(Non critical) Master does not understand "
                                 "REPLCONF listening-port: %s", err);
         }
         sdsfree(err);
+        server.repl_state = REPL_STATE_SEND_CAPA;
     }
 
     /* Inform the master of our capabilities. While we currently send
      * just one capability, it is possible to chain new capabilities here
      * in the form of REPLCONF capa X capa Y capa Z ...
      * The master will ignore capabilities it does not understand. */
-    {
-        err = sendSynchronousCommand(fd,"REPLCONF","capa","eof",NULL);
+    if (server.repl_state == REPL_STATE_SEND_CAPA) {
+        err = sendSynchronousCommand(SYNC_CMD_WRITE,fd,"REPLCONF",
+                "capa","eof",NULL);
+        if (err) goto write_error;
+        sdsfree(err);
+        server.repl_state = REPL_STATE_RECEIVE_CAPA;
+        return;
+    }
 
+    /* Receive CAPA reply. */
+    if (server.repl_state == REPL_STATE_RECEIVE_CAPA) {
+        err = sendSynchronousCommand(SYNC_CMD_READ,fd,NULL);
         /* Ignore the error if any, not all the Redis versions support
          * REPLCONF capa. */
         if (err[0] == '-') {
             serverLog(LL_NOTICE,"(Non critical) Master does not understand "
                                   "REPLCONF capa: %s", err);
         }
         sdsfree(err);
+        server.repl_state = REPL_STATE_SEND_PSYNC;
     }
 
     /* Try a partial resynchonization. If we don't have a cached master
      * slaveTryPartialResynchronization() will at least try to use PSYNC
      * to start a full resynchronization so that we get the master run id
      * and the global offset, to try a partial resync at the next
      * reconnection attempt. */
-    psync_result = slaveTryPartialResynchronization(fd);
+    if (server.repl_state == REPL_STATE_SEND_PSYNC) {
+        if (slaveTryPartialResynchronization(fd,0) == PSYNC_WRITE_ERROR) {
+            err = sdsnew("Write error sending the PSYNC command.");
+            goto write_error;
+        }
+        server.repl_state = REPL_STATE_RECEIVE_PSYNC;
+        return;
+    }
+
+    /* If reached this point, we should be in REPL_STATE_RECEIVE_PSYNC. */
+    if (server.repl_state != REPL_STATE_RECEIVE_PSYNC) {
+        serverLog(LL_WARNING,"syncWithMaster(): state machine error, "
+                             "state should be RECEIVE_PSYNC but is %d",
+                             server.repl_state);
+        goto error;
+    }
+
+    /* Delete the readable event, we no longer need it now that there is
+     * the last reply to read. */
+    aeDeleteFileEvent(server.el,fd,AE_READABLE);
+    psync_result = slaveTryPartialResynchronization(fd,1);
+    if (psync_result == PSYNC_WAIT_REPLY) {
+        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
+            syncWithMaster,NULL) == AE_ERR)
+        {
+            serverLog(LL_WARNING,"Failed to reinstall the read event in "
+                                 "PSYNC_WAIT_REPLY state.");
+            goto error;
+        }
+        return; /* Try again later... */
+    }
+
     if (psync_result == PSYNC_CONTINUE) {
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
         return;
@@ -1466,6 +1566,11 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     server.repl_transfer_s = -1;
     server.repl_state = REPL_STATE_CONNECT;
     return;
+
+write_error: /* Handle sendSynchronousCommand(SYNC_CMD_WRITE) errors. */
+    serverLog(LL_WARNING,"Sending command to master in replication handshake: %s", err);
+    sdsfree(err);
+    goto error;
 }
 
 int connectWithMaster(void) {
@@ -1652,7 +1757,15 @@ void roleCommand(client *c) {
         case REPL_STATE_NONE: slavestate = "none"; break;
         case REPL_STATE_CONNECT: slavestate = "connect"; break;
         case REPL_STATE_CONNECTING: slavestate = "connecting"; break;
-        case REPL_STATE_RECEIVE_PONG: /* see next */
+        case REPL_STATE_RECEIVE_PONG:
+        case REPL_STATE_SEND_AUTH:
+        case REPL_STATE_RECEIVE_AUTH:
+        case REPL_STATE_SEND_PORT:
+        case REPL_STATE_RECEIVE_PORT:
+        case REPL_STATE_SEND_CAPA:
+        case REPL_STATE_RECEIVE_CAPA:
+        case REPL_STATE_SEND_PSYNC:
+        case REPL_STATE_RECEIVE_PSYNC: slavestate = "handshake"; break;
         case REPL_STATE_TRANSFER: slavestate = "sync"; break;
         case REPL_STATE_CONNECTED: slavestate = "connected"; break;
         default: slavestate = "unknown"; break;