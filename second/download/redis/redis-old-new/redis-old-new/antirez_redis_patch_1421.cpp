@@ -3,6 +3,14 @@
 
 static void setProtocolError(redisClient *c, int pos);
 
+/* To evaluate the output buffer size of a client we need to get size of
+ * allocated objects, however we can't used zmalloc_size() directly on sds
+ * strings because of the trick they use to work (the header is before the
+ * returned pointer), so we use this helper function. */
+size_t zmalloc_size_sds(sds s) {
+    return zmalloc_size(s-sizeof(struct sdshdr));
+}
+
 void *dupClientReplyValue(void *o) {
     incrRefCount((robj*)o);
     return o;
@@ -137,21 +145,24 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
     if (listLength(c->reply) == 0) {
         incrRefCount(o);
         listAddNodeTail(c->reply,o);
+        c->reply_bytes += zmalloc_size_sds(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
         {
+            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,o->ptr,sdslen(o->ptr));
+            c->reply_bytes += zmalloc_size_sds(tail->ptr);
         } else {
             incrRefCount(o);
             listAddNodeTail(c->reply,o);
+            c->reply_bytes += zmalloc_size_sds(o->ptr);
         }
     }
-    c->reply_bytes += sdslen(o->ptr);
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
@@ -165,21 +176,24 @@ void _addReplySdsToList(redisClient *c, sds s) {
         return;
     }
 
-    c->reply_bytes += sdslen(s);
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+        c->reply_bytes += zmalloc_size_sds(s);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
         {
+            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,sdslen(s));
+            c->reply_bytes += zmalloc_size_sds(tail->ptr);
             sdsfree(s);
         } else {
             listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+            c->reply_bytes += zmalloc_size_sds(s);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -191,21 +205,28 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
-        listAddNodeTail(c->reply,createStringObject(s,len));
+        robj *o = createStringObject(s,len);
+
+        listAddNodeTail(c->reply,o);
+        c->reply_bytes += zmalloc_size_sds(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
+            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,len);
+            c->reply_bytes += zmalloc_size_sds(tail->ptr);
         } else {
-            listAddNodeTail(c->reply,createStringObject(s,len));
+            robj *o = createStringObject(s,len);
+
+            listAddNodeTail(c->reply,o);
+            c->reply_bytes += zmalloc_size_sds(o->ptr);
         }
     }
-    c->reply_bytes += len;
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
@@ -336,7 +357,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    c->reply_bytes += sdslen(len->ptr);
+    c->reply_bytes += zmalloc_size_sds(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
@@ -363,6 +384,18 @@ void addReplyDouble(redisClient *c, double d) {
 void addReplyLongLongWithPrefix(redisClient *c, long long ll, char prefix) {
     char buf[128];
     int len;
+
+    /* Things like $3\r\n or *2\r\n are emitted very often by the protocol
+     * so we have a few shared objects to use if the integer is small
+     * like it is most of the times. */
+    if (prefix == '*' && ll < REDIS_SHARED_BULKHDR_LEN) {
+        addReply(c,shared.mbulkhdr[ll]);
+        return;
+    } else if (prefix == '$' && ll < REDIS_SHARED_BULKHDR_LEN) {
+        addReply(c,shared.bulkhdr[ll]);
+        return;
+    }
+
     buf[0] = prefix;
     len = ll2string(buf+1,sizeof(buf)-1,ll);
     buf[len+1] = '\r';
@@ -626,6 +659,7 @@ void freeClientsInAsyncFreeQueue(void) {
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *c = privdata;
     int nwritten = 0, totwritten = 0, objlen;
+    size_t objmem;
     robj *o;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
@@ -651,6 +685,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         } else {
             o = listNodeValue(listFirst(c->reply));
             objlen = sdslen(o->ptr);
+            objmem = zmalloc_size_sds(o->ptr);
 
             if (objlen == 0) {
                 listDelNode(c->reply,listFirst(c->reply));
@@ -671,15 +706,20 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
             if (c->sentlen == objlen) {
                 listDelNode(c->reply,listFirst(c->reply));
                 c->sentlen = 0;
-                c->reply_bytes -= objlen;
+                c->reply_bytes -= objmem;
             }
         }
-        /* Note that we avoid to send more thank REDIS_MAX_WRITE_PER_EVENT
+        /* Note that we avoid to send more than REDIS_MAX_WRITE_PER_EVENT
          * bytes, in a single threaded server it's a good idea to serve
          * other clients as well, even if a very large request comes from
          * super fast link that is always able to accept data (in real world
-         * scenario think about 'KEYS *' against the loopback interfae) */
-        if (totwritten > REDIS_MAX_WRITE_PER_EVENT) break;
+         * scenario think about 'KEYS *' against the loopback interface).
+         *
+         * However if we are over the maxmemory limit we ignore that and
+         * just deliver as much data as it is possible to deliver. */
+        if (totwritten > REDIS_MAX_WRITE_PER_EVENT &&
+            (server.maxmemory == 0 ||
+             zmalloc_used_memory() < server.maxmemory)) break;
     }
     if (nwritten == -1) {
         if (errno == EAGAIN) {
@@ -1205,7 +1245,7 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
  * the caller wishes. The main usage of this function currently is
  * enforcing the client output length limits. */
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c) {
-    unsigned long list_item_size = sizeof(listNode);
+    unsigned long list_item_size = sizeof(listNode)+sizeof(robj);
 
     return c->reply_bytes + (list_item_size*listLength(c->reply));
 }
@@ -1298,3 +1338,24 @@ void asyncCloseClientOnOutputBufferLimitReached(redisClient *c) {
         sdsfree(client);
     }
 }
+
+/* Helper function used by freeMemoryIfNeeded() in order to flush slaves
+ * output buffers without returning control to the event loop. */
+void flushSlavesOutputBuffers(void) {
+    listIter li;
+    listNode *ln;
+
+    listRewind(server.slaves,&li);
+    while((ln = listNext(&li))) {
+        redisClient *slave = listNodeValue(ln);
+        int events;
+
+        events = aeGetFileEvents(server.el,slave->fd);
+        if (events & AE_WRITABLE &&
+            slave->replstate == REDIS_REPL_ONLINE &&
+            listLength(slave->reply))
+        {
+            sendReplyToClient(server.el,slave->fd,slave,0);
+        }
+    }
+}