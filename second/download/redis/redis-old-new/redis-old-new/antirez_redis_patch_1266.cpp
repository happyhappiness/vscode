@@ -486,7 +486,7 @@ void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
     dst->reply_bytes = src->reply_bytes;
 }
 
-static void acceptCommonHandler(int fd) {
+static void acceptCommonHandler(int fd, int flags) {
     redisClient *c;
     if ((c = createClient(fd)) == NULL) {
         redisLog(REDIS_WARNING,"Error allocating resoures for the client");
@@ -509,6 +509,7 @@ static void acceptCommonHandler(int fd) {
         return;
     }
     server.stat_numconnections++;
+    c->flags |= flags;
 }
 
 void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -524,7 +525,7 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     redisLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
-    acceptCommonHandler(cfd);
+    acceptCommonHandler(cfd,0);
 }
 
 void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -539,7 +540,7 @@ void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     redisLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
-    acceptCommonHandler(cfd);
+    acceptCommonHandler(cfd,REDIS_UNIX_SOCKET);
 }
 
 
@@ -1062,10 +1063,11 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
 /* Turn a Redis client into an sds string representing its state. */
 sds getClientInfoString(redisClient *client) {
     char ip[32], flags[16], events[3], *p;
-    int port;
+    int port = 0; /* initialized to zero for the unix socket case. */
     int emask;
 
-    anetPeerToString(client->fd,ip,&port);
+    if (!(client->flags & REDIS_UNIX_SOCKET))
+        anetPeerToString(client->fd,ip,&port);
     p = flags;
     if (client->flags & REDIS_SLAVE) {
         if (client->flags & REDIS_MONITOR)
@@ -1080,6 +1082,7 @@ sds getClientInfoString(redisClient *client) {
     if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
     if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
     if (client->flags & REDIS_CLOSE_ASAP) *p++ = 'A';
+    if (client->flags & REDIS_UNIX_SOCKET) *p++ = 'U';
     if (p == flags) *p++ = 'N';
     *p++ = '\0';
 
@@ -1090,7 +1093,8 @@ sds getClientInfoString(redisClient *client) {
     *p = '\0';
     return sdscatprintf(sdsempty(),
         "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d multi=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
-        ip,port,client->fd,
+        (client->flags & REDIS_UNIX_SOCKET) ? server.unixsocket : ip,
+        port,client->fd,
         (long)(server.unixtime - client->ctime),
         (long)(server.unixtime - client->lastinteraction),
         flags,