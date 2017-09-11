@@ -1625,14 +1625,135 @@ void restoreCommand(redisClient *c) {
     server.dirty++;
 }
 
+/* MIGRATE socket cache implementation.
+ *
+ * We take a map between host:ip and a TCP socket that we used to connect
+ * to this instance in recent time.
+ * This sockets are closed when the max number we cache is reached, and also
+ * in serverCron() when they are around for more than a few seconds. */
+#define MIGRATE_SOCKET_CACHE_ITEMS 64 /* max num of items in the cache. */
+#define MIGRATE_SOCKET_CACHE_TTL 10 /* close cached socekts after 10 sec. */
+
+typedef struct migrateCachedSocket {
+    int fd;
+    time_t last_use_time;
+} migrateCachedSocket;
+
+/* Return a TCP scoket connected with the target instance, possibly returning
+ * a cached one.
+ *
+ * This function is responsible of sending errors to the client if a
+ * connection can't be established. In this case -1 is returned.
+ * Otherwise on success the socket is returned, and the caller should not
+ * attempt to free it after usage.
+ *
+ * If the caller detects an error while using the socket, migrateCloseSocket()
+ * should be called so that the connection will be craeted from scratch
+ * the next time. */
+int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
+    int fd;
+    sds name = sdsempty();
+    migrateCachedSocket *cs;
+
+    /* Check if we have an already cached socket for this ip:port pair. */
+    name = sdscatlen(name,host->ptr,sdslen(host->ptr));
+    name = sdscatlen(name,":",1);
+    name = sdscatlen(name,port->ptr,sdslen(port->ptr));
+    cs = dictFetchValue(server.migrate_cached_sockets,name);
+    if (cs) {
+        sdsfree(name);
+        cs->last_use_time = server.unixtime;
+        return cs->fd;
+    }
+
+    /* No cached socket, create one. */
+    if (dictSize(server.migrate_cached_sockets) == MIGRATE_SOCKET_CACHE_ITEMS) {
+        /* Too many items, drop one at random. */
+        dictEntry *de = dictGetRandomKey(server.migrate_cached_sockets);
+        cs = dictGetVal(de);
+        close(cs->fd);
+        zfree(cs);
+        dictDelete(server.migrate_cached_sockets,dictGetKey(de));
+    }
+
+    /* Create the socket */
+    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
+                atoi(c->argv[2]->ptr));
+    if (fd == -1) {
+        sdsfree(name);
+        addReplyErrorFormat(c,"Can't connect to target node: %s",
+            server.neterr);
+        return -1;
+    }
+    anetTcpNoDelay(server.neterr,fd);
+
+    /* Check if it connects within the specified timeout. */
+    if ((aeWait(fd,AE_WRITABLE,timeout) & AE_WRITABLE) == 0) {
+        sdsfree(name);
+        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
+        close(fd);
+        return -1;
+    }
+
+    /* Add to the cache and return it to the caller. */
+    cs = zmalloc(sizeof(*cs));
+    cs->fd = fd;
+    cs->last_use_time = server.unixtime;
+    dictAdd(server.migrate_cached_sockets,name,cs);
+    return fd;
+}
+
+/* Free a migrate cached connection. */
+void migrateCloseSocket(robj *host, robj *port) {
+    sds name = sdsempty();
+    migrateCachedSocket *cs;
+
+    name = sdscatlen(name,host->ptr,sdslen(host->ptr));
+    name = sdscatlen(name,":",1);
+    name = sdscatlen(name,port->ptr,sdslen(port->ptr));
+    cs = dictFetchValue(server.migrate_cached_sockets,name);
+    if (!cs) {
+        sdsfree(name);
+        return;
+    }
+
+    close(cs->fd);
+    zfree(cs);
+    dictDelete(server.migrate_cached_sockets,name);
+    sdsfree(name);
+}
+
+void migrateCloseTimedoutSockets(void) {
+    dictIterator *di = dictGetSafeIterator(server.migrate_cached_sockets);
+    dictEntry *de;
+
+    while((de = dictNext(di)) != NULL) {
+        migrateCachedSocket *cs = dictGetVal(de);
+
+        if ((server.unixtime - cs->last_use_time) > MIGRATE_SOCKET_CACHE_TTL) {
+            close(cs->fd);
+            zfree(cs);
+            dictDelete(server.migrate_cached_sockets,dictGetKey(de));
+        }
+    }
+    dictReleaseIterator(di);
+}
+
 /* MIGRATE host port key dbid timeout [COPY | REPLACE] */
 void migrateCommand(redisClient *c) {
-    int fd, copy = 0, replace = 0, j;
+    int fd, copy, replace, j;
     long timeout;
     long dbid;
-    long long ttl = 0, expireat;
+    long long ttl, expireat;
     robj *o;
     rio cmd, payload;
+    int retry_num = 0;
+
+try_again:
+    /* Initialization */
+    copy = 0;
+    replace = 0;
+    ttl = 0;
 
     /* Parse additional options */
     for (j = 6; j < c->argc; j++) {
@@ -1651,7 +1772,7 @@ void migrateCommand(redisClient *c) {
         return;
     if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != REDIS_OK)
         return;
-    if (timeout <= 0) timeout = 1;
+    if (timeout <= 0) timeout = 1000;
 
     /* Check if the key is here. If not we reply with success as there is
      * nothing to migrate (for instance the key expired in the meantime), but
@@ -1662,17 +1783,8 @@ void migrateCommand(redisClient *c) {
     }
     
     /* Connect */
-    fd = anetTcpNonBlockConnect(server.neterr,c->argv[1]->ptr,
-                atoi(c->argv[2]->ptr));
-    if (fd == -1) {
-        addReplyErrorFormat(c,"Can't connect to target node: %s",
-            server.neterr);
-        return;
-    }
-    if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
-        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
-        return;
-    }
+    fd = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
+    if (fd == -1) return; /* error sent to the client by migrateGetSocket() */
 
     /* Create RESTORE payload and generate the protocol to call the command. */
     rioInitWithBuffer(&cmd,sdsempty());
@@ -1704,6 +1816,7 @@ void migrateCommand(redisClient *c) {
         redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"REPLACE",7));
 
     /* Tranfer the query to the other node in 64K chunks. */
+    errno = 0;
     {
         sds buf = cmd.io.buffer.ptr;
         size_t pos = 0, towrite;
@@ -1749,19 +1862,22 @@ void migrateCommand(redisClient *c) {
     }
 
     sdsfree(cmd.io.buffer.ptr);
-    close(fd);
     return;
 
 socket_wr_err:
-    addReplySds(c,sdsnew("-IOERR error or timeout writing to target instance\r\n"));
     sdsfree(cmd.io.buffer.ptr);
-    close(fd);
+    migrateCloseSocket(c->argv[1],c->argv[2]);
+    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
+    addReplySds(c,
+        sdsnew("-IOERR error or timeout writing to target instance\r\n"));
     return;
 
 socket_rd_err:
-    addReplySds(c,sdsnew("-IOERR error or timeout reading from target node\r\n"));
     sdsfree(cmd.io.buffer.ptr);
-    close(fd);
+    migrateCloseSocket(c->argv[1],c->argv[2]);
+    if (errno != ETIMEDOUT && retry_num++ == 0) goto try_again;
+    addReplySds(c,
+        sdsnew("-IOERR error or timeout reading from target node\r\n"));
     return;
 }
 