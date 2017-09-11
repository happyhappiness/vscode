@@ -592,7 +592,7 @@ void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
 static void acceptCommonHandler(int fd, int flags) {
     redisClient *c;
     if ((c = createClient(fd)) == NULL) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Error registering fd event for the new client: %s (fd=%d)",
             strerror(errno),fd);
         close(fd); /* May be already closed, just ignore errors */
@@ -628,11 +628,11 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
         if (cfd == ANET_ERR) {
             if (errno != EWOULDBLOCK)
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "Accepting client connection: %s", server.neterr);
             return;
         }
-        redisLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
+        serverLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
         acceptCommonHandler(cfd,0);
     }
 }
@@ -647,11 +647,11 @@ void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         cfd = anetUnixAccept(server.neterr, fd);
         if (cfd == ANET_ERR) {
             if (errno != EWOULDBLOCK)
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "Accepting client connection: %s", server.neterr);
             return;
         }
-        redisLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
+        serverLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
         acceptCommonHandler(cfd,REDIS_UNIX_SOCKET);
     }
 }
@@ -700,7 +700,7 @@ void freeClient(redisClient *c) {
      * Note that before doing this we make sure that the client is not in
      * some unexpected state, by checking its flags. */
     if (server.master && c->flags & REDIS_MASTER) {
-        redisLog(REDIS_WARNING,"Connection with master lost.");
+        serverLog(REDIS_WARNING,"Connection with master lost.");
         if (!(c->flags & (REDIS_CLOSE_AFTER_REPLY|
                           REDIS_CLOSE_ASAP|
                           REDIS_BLOCKED|
@@ -713,7 +713,7 @@ void freeClient(redisClient *c) {
 
     /* Log link disconnection with slave */
     if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR)) {
-        redisLog(REDIS_WARNING,"Connection with slave %s lost.",
+        serverLog(REDIS_WARNING,"Connection with slave %s lost.",
             replicationGetSlaveName(c));
     }
 
@@ -883,7 +883,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (errno == EAGAIN) {
             nwritten = 0;
         } else {
-            redisLog(REDIS_VERBOSE,
+            serverLog(REDIS_VERBOSE,
                 "Error writing to client: %s", strerror(errno));
             freeClient(c);
             return;
@@ -985,7 +985,7 @@ int processInlineBuffer(redisClient *c) {
 static void setProtocolError(redisClient *c, int pos) {
     if (server.verbosity <= REDIS_VERBOSE) {
         sds client = catClientInfoString(sdsempty(),c);
-        redisLog(REDIS_VERBOSE,
+        serverLog(REDIS_VERBOSE,
             "Protocol error from client: %s", client);
         sdsfree(client);
     }
@@ -1205,12 +1205,12 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (errno == EAGAIN) {
             return;
         } else {
-            redisLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
+            serverLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
             freeClient(c);
             return;
         }
     } else if (nread == 0) {
-        redisLog(REDIS_VERBOSE, "Client closed connection");
+        serverLog(REDIS_VERBOSE, "Client closed connection");
         freeClient(c);
         return;
     }
@@ -1223,7 +1223,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
 
         bytes = sdscatrepr(bytes,c->querybuf,64);
-        redisLog(REDIS_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
+        serverLog(REDIS_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
         sdsfree(ci);
         sdsfree(bytes);
         freeClient(c);
@@ -1660,7 +1660,7 @@ void asyncCloseClientOnOutputBufferLimitReached(redisClient *c) {
         sds client = catClientInfoString(sdsempty(),c);
 
         freeClientAsync(c);
-        redisLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
+        serverLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
         sdsfree(client);
     }
 }