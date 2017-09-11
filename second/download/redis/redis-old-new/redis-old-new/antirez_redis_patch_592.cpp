@@ -4362,11 +4362,12 @@ void restoreCommand(redisClient *c) {
 
 typedef struct migrateCachedSocket {
     int fd;
+    long last_dbid;
     time_t last_use_time;
 } migrateCachedSocket;
 
-/* Return a TCP socket connected with the target instance, possibly returning
- * a cached one.
+/* Return a migrateCachedSocket containing a TCP socket connected with the
+ * target instance, possibly returning a cached one.
  *
  * This function is responsible of sending errors to the client if a
  * connection can't be established. In this case -1 is returned.
@@ -4376,7 +4377,7 @@ typedef struct migrateCachedSocket {
  * If the caller detects an error while using the socket, migrateCloseSocket()
  * should be called so that the connection will be created from scratch
  * the next time. */
-int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
+migrateCachedSocket* migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
     int fd;
     sds name = sdsempty();
     migrateCachedSocket *cs;
@@ -4389,7 +4390,7 @@ int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
     if (cs) {
         sdsfree(name);
         cs->last_use_time = server.unixtime;
-        return cs->fd;
+        return cs;
     }
 
     /* No cached socket, create one. */
@@ -4409,7 +4410,7 @@ int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
         sdsfree(name);
         addReplyErrorFormat(c,"Can't connect to target node: %s",
             server.neterr);
-        return -1;
+        return NULL;
     }
     anetEnableTcpNoDelay(server.neterr,fd);
 
@@ -4419,15 +4420,16 @@ int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
         addReplySds(c,
             sdsnew("-IOERR error or timeout connecting to the client\r\n"));
         close(fd);
-        return -1;
+        return NULL;
     }
 
     /* Add to the cache and return it to the caller. */
     cs = zmalloc(sizeof(*cs));
     cs->fd = fd;
+    cs->last_dbid = -1;
     cs->last_use_time = server.unixtime;
     dictAdd(server.migrate_cached_sockets,name,cs);
-    return fd;
+    return cs;
 }
 
 /* Free a migrate cached connection. */
@@ -4468,7 +4470,8 @@ void migrateCloseTimedoutSockets(void) {
 
 /* MIGRATE host port key dbid timeout [COPY | REPLACE] */
 void migrateCommand(redisClient *c) {
-    int fd, copy, replace, j;
+    migrateCachedSocket *cs;
+    int copy, replace, j;
     long timeout;
     long dbid;
     long long ttl, expireat;
@@ -4478,6 +4481,7 @@ void migrateCommand(redisClient *c) {
 
 try_again:
     /* Initialization */
+    cs = NULL;
     copy = 0;
     replace = 0;
     ttl = 0;
@@ -4510,14 +4514,17 @@ void migrateCommand(redisClient *c) {
     }
 
     /* Connect */
-    fd = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
-    if (fd == -1) return; /* error sent to the client by migrateGetSocket() */
+    cs = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
+    if (cs == NULL) return; /* error sent to the client by migrateGetSocket() */
 
-    /* Create RESTORE payload and generate the protocol to call the command. */
     rioInitWithBuffer(&cmd,sdsempty());
-    redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
-    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
-    redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,dbid));
+
+    /* Create RESTORE payload and generate the protocol to call the command. */
+    if (cs->last_dbid != dbid) {
+        redisAssertWithInfo(c,NULL,rioWriteBulkCount(&cmd,'*',2));
+        redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"SELECT",6));
+        redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,dbid));
+    }
 
     expireat = getExpire(c->db,c->argv[3]);
     if (expireat != -1) {
@@ -4556,7 +4563,7 @@ void migrateCommand(redisClient *c) {
 
         while ((towrite = sdslen(buf)-pos) > 0) {
             towrite = (towrite > (64*1024) ? (64*1024) : towrite);
-            nwritten = syncWrite(fd,buf+pos,towrite,timeout);
+            nwritten = syncWrite(cs->fd,buf+pos,towrite,timeout);
             if (nwritten != (signed)towrite) goto socket_wr_err;
             pos += nwritten;
         }
@@ -4568,14 +4575,18 @@ void migrateCommand(redisClient *c) {
         char buf2[1024];
 
         /* Read the two replies */
-        if (syncReadLine(fd, buf1, sizeof(buf1), timeout) <= 0)
+        if (cs->last_dbid != dbid && syncReadLine(cs->fd, buf1, sizeof(buf1), timeout) <= 0)
             goto socket_rd_err;
-        if (syncReadLine(fd, buf2, sizeof(buf2), timeout) <= 0)
+        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
             goto socket_rd_err;
-        if (buf1[0] == '-' || buf2[0] == '-') {
+        if ((cs->last_dbid != dbid && buf1[0] == '-') || buf2[0] == '-') {
+            /* If we got an error at all, assume that the last_dbid is no longer valid */
+            cs->last_dbid = -1;
             addReplyErrorFormat(c,"Target instance replied with error: %s",
-                (buf1[0] == '-') ? buf1+1 : buf2+1);
+                (cs->last_dbid != dbid && buf1[0] == '-') ? buf1+1 : buf2+1);
         } else {
+            /* Update the last_dbid in migrateCachedSocket */
+            cs->last_dbid = dbid;
             robj *aux;
 
             if (!copy) {
@@ -4586,10 +4597,12 @@ void migrateCommand(redisClient *c) {
             addReply(c,shared.ok);
             server.dirty++;
 
-            /* Translate MIGRATE as DEL for replication/AOF. */
-            aux = createStringObject("DEL",3);
-            rewriteClientCommandVector(c,2,aux,c->argv[3]);
-            decrRefCount(aux);
+            if (!copy) {
+                /* Translate MIGRATE as DEL for replication/AOF. */
+                aux = createStringObject("DEL",3);
+                rewriteClientCommandVector(c,2,aux,c->argv[3]);
+                decrRefCount(aux);
+            }
         }
     }
 