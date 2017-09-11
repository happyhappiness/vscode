@@ -1106,18 +1106,19 @@ int processMultibulkBuffer(redisClient *c) {
 }
 
 void processInputBuffer(redisClient *c) {
+    server.current_client = c;
     /* Keep processing while there is something in the input buffer */
     while(sdslen(c->querybuf)) {
         /* Return if clients are paused. */
-        if (!(c->flags & REDIS_SLAVE) && clientsArePaused()) return;
+        if (!(c->flags & REDIS_SLAVE) && clientsArePaused()) break;
 
         /* Immediately abort if the client is in the middle of something. */
-        if (c->flags & REDIS_BLOCKED) return;
+        if (c->flags & REDIS_BLOCKED) break;
 
         /* REDIS_CLOSE_AFTER_REPLY closes the connection once the reply is
          * written to the client. Make sure to not let the reply grow after
          * this flag has been set (i.e. don't process more commands). */
-        if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+        if (c->flags & REDIS_CLOSE_AFTER_REPLY) break;
 
         /* Determine request type when unknown. */
         if (!c->reqtype) {
@@ -1145,6 +1146,7 @@ void processInputBuffer(redisClient *c) {
                 resetClient(c);
         }
     }
+    server.current_client = NULL;
 }
 
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -1154,7 +1156,6 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
-    server.current_client = c;
     readlen = REDIS_IOBUF_LEN;
     /* If this is a multi bulk request, and we are processing a bulk reply
      * that is large enough, try to maximize the probability that the query
@@ -1176,7 +1177,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     nread = read(fd, c->querybuf+qblen, readlen);
     if (nread == -1) {
         if (errno == EAGAIN) {
-            nread = 0;
+            return;
         } else {
             redisLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
             freeClient(c);
@@ -1187,15 +1188,11 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         freeClient(c);
         return;
     }
-    if (nread) {
-        sdsIncrLen(c->querybuf,nread);
-        c->lastinteraction = server.unixtime;
-        if (c->flags & REDIS_MASTER) c->reploff += nread;
-        server.stat_net_input_bytes += nread;
-    } else {
-        server.current_client = NULL;
-        return;
-    }
+
+    sdsIncrLen(c->querybuf,nread);
+    c->lastinteraction = server.unixtime;
+    if (c->flags & REDIS_MASTER) c->reploff += nread;
+    server.stat_net_input_bytes += nread;
     if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
         sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
 
@@ -1207,7 +1204,6 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     processInputBuffer(c);
-    server.current_client = NULL;
 }
 
 void getClientsMaxBuffers(unsigned long *longest_output_list,