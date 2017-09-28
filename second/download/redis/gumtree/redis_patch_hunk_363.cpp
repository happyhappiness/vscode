 /* Send a synchronous command to the master. Used to send AUTH and
  * REPLCONF commands before starting the replication with SYNC.
  *
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
-
-    /* Transfer command to the server. */
-    if (syncWrite(fd,cmd,sdslen(cmd),server.repl_syncio_timeout*1000) == -1) {
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
+
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
  * If there is no cached master structure, at least try to issue a
  * "PSYNC ? -1" command in order to trigger a full resync using the PSYNC
  * command in order to obtain the master run id and the master replication
