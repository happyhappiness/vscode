@@ -22,7 +22,6 @@ int listMatchObjects(void *a, void *b) {
 
 redisClient *createClient(int fd) {
     redisClient *c = zmalloc(sizeof(redisClient));
-    c->bufpos = 0;
 
     /* passing -1 as fd it is possible to create a non connected client.
      * This is useful since all the Redis commands needs to be executed
@@ -42,7 +41,9 @@ redisClient *createClient(int fd) {
 
     selectDb(c,0);
     c->fd = fd;
+    c->bufpos = 0;
     c->querybuf = sdsempty();
+    c->querybuf_peak = 0;
     c->reqtype = 0;
     c->argc = 0;
     c->argv = NULL;
@@ -51,7 +52,7 @@ redisClient *createClient(int fd) {
     c->bulklen = -1;
     c->sentlen = 0;
     c->flags = 0;
-    c->lastinteraction = time(NULL);
+    c->ctime = c->lastinteraction = time(NULL);
     c->authenticated = 0;
     c->replstate = REDIS_REPL_NONE;
     c->reply = listCreate();
@@ -751,34 +752,6 @@ void resetClient(redisClient *c) {
     if (!(c->flags & REDIS_MULTI)) c->flags &= (~REDIS_ASKING);
 }
 
-void closeTimedoutClients(void) {
-    redisClient *c;
-    listNode *ln;
-    time_t now = time(NULL);
-    listIter li;
-
-    listRewind(server.clients,&li);
-    while ((ln = listNext(&li)) != NULL) {
-        c = listNodeValue(ln);
-        if (server.maxidletime &&
-            !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
-            !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
-            !(c->flags & REDIS_BLOCKED) &&  /* no timeout for BLPOP */
-            dictSize(c->pubsub_channels) == 0 && /* no timeout for pubsub */
-            listLength(c->pubsub_patterns) == 0 &&
-            (now - c->lastinteraction > server.maxidletime))
-        {
-            redisLog(REDIS_VERBOSE,"Closing idle client");
-            freeClient(c);
-        } else if (c->flags & REDIS_BLOCKED) {
-            if (c->bpop.timeout != 0 && c->bpop.timeout < now) {
-                addReply(c,shared.nullmultibulk);
-                unblockClientWaitingData(c);
-            }
-        }
-    }
-}
-
 int processInlineBuffer(redisClient *c) {
     char *newline = strstr(c->querybuf,"\r\n");
     int argc, j;
@@ -1026,6 +999,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     qblen = sdslen(c->querybuf);
+    if (c->querybuf_peak < qblen) c->querybuf_peak = qblen;
     c->querybuf = sdsMakeRoomFor(c->querybuf, readlen);
     nread = read(fd, c->querybuf+qblen, readlen);
     if (nread == -1) {
@@ -1087,11 +1061,7 @@ sds getClientInfoString(redisClient *client) {
     time_t now = time(NULL);
     int emask;
 
-    if (anetPeerToString(client->fd,ip,&port) == -1) {
-        ip[0] = '?';
-        ip[1] = '\0';
-        port = 0;
-    }
+    anetPeerToString(client->fd,ip,&port);
     p = flags;
     if (client->flags & REDIS_SLAVE) {
         if (client->flags & REDIS_MONITOR)
@@ -1115,14 +1085,16 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
+        (long)(now - client->ctime),
         (long)(now - client->lastinteraction),
         flags,
         client->db->id,
         (int) dictSize(client->pubsub_channels),
         (int) listLength(client->pubsub_patterns),
         (unsigned long) sdslen(client->querybuf),
+        (unsigned long) sdsavail(client->querybuf),
         (unsigned long) client->bufpos,
         (unsigned long) listLength(client->reply),
         getClientOutputBufferMemoryUsage(client),