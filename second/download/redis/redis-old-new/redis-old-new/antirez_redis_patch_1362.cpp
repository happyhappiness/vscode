@@ -52,7 +52,7 @@ redisClient *createClient(int fd) {
     c->bulklen = -1;
     c->sentlen = 0;
     c->flags = 0;
-    c->ctime = c->lastinteraction = time(NULL);
+    c->ctime = c->lastinteraction = server.unixtime;
     c->authenticated = 0;
     c->replstate = REDIS_REPL_NONE;
     c->reply = listCreate();
@@ -604,7 +604,7 @@ void freeClient(redisClient *c) {
     if (c->flags & REDIS_MASTER) {
         server.master = NULL;
         server.repl_state = REDIS_REPL_CONNECT;
-        server.repl_down_since = time(NULL);
+        server.repl_down_since = server.unixtime;
         /* Since we lost the connection with the master, we should also
          * close the connection with all our slaves if we have any, so
          * when we'll resync with the master the other slaves will sync again
@@ -732,7 +732,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
             return;
         }
     }
-    if (totwritten > 0) c->lastinteraction = time(NULL);
+    if (totwritten > 0) c->lastinteraction = server.unixtime;
     if (c->bufpos == 0 && listLength(c->reply) == 0) {
         c->sentlen = 0;
         aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
@@ -1017,7 +1017,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
     if (nread) {
         sdsIncrLen(c->querybuf,nread);
-        c->lastinteraction = time(NULL);
+        c->lastinteraction = server.unixtime;
     } else {
         server.current_client = NULL;
         return;
@@ -1058,7 +1058,6 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
 sds getClientInfoString(redisClient *client) {
     char ip[32], flags[16], events[3], *p;
     int port;
-    time_t now = time(NULL);
     int emask;
 
     anetPeerToString(client->fd,ip,&port);
@@ -1087,8 +1086,8 @@ sds getClientInfoString(redisClient *client) {
     return sdscatprintf(sdsempty(),
         "addr=%s:%d fd=%d age=%ld idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu qbuf-free=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
-        (long)(now - client->ctime),
-        (long)(now - client->lastinteraction),
+        (long)(server.unixtime - client->ctime),
+        (long)(server.unixtime - client->lastinteraction),
         flags,
         client->db->id,
         (int) dictSize(client->pubsub_channels),