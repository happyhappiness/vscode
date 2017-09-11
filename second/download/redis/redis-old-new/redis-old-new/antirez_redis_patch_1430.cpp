@@ -151,7 +151,7 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
             listAddNodeTail(c->reply,o);
         }
     }
-    c->reply_bytes += sdslen(o->ptr);
+    c->reply_bytes += zmalloc_size(o->ptr);
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
@@ -165,7 +165,7 @@ void _addReplySdsToList(redisClient *c, sds s) {
         return;
     }
 
-    c->reply_bytes += sdslen(s);
+    c->reply_bytes += zmalloc_size(s);
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
     } else {
@@ -191,21 +191,28 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
-        listAddNodeTail(c->reply,createStringObject(s,len));
+        robj *o = createStringObject(s,len);
+
+        listAddNodeTail(c->reply,o);
+        c->reply_bytes += zmalloc_size(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
+            c->reply_bytes -= zmalloc_size(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,len);
+            c->reply_bytes += zmalloc_size(tail->ptr);
         } else {
-            listAddNodeTail(c->reply,createStringObject(s,len));
+            robj *o = createStringObject(s,len);
+
+            listAddNodeTail(c->reply,o);
+            c->reply_bytes += zmalloc_size(o->ptr);
         }
     }
-    c->reply_bytes += len;
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
@@ -336,7 +343,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    c->reply_bytes += sdslen(len->ptr);
+    c->reply_bytes += zmalloc_size(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
@@ -638,6 +645,7 @@ void freeClientsInAsyncFreeQueue(void) {
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *c = privdata;
     int nwritten = 0, totwritten = 0, objlen;
+    size_t objmem;
     robj *o;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
@@ -663,6 +671,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         } else {
             o = listNodeValue(listFirst(c->reply));
             objlen = sdslen(o->ptr);
+            objmem = zmalloc_size(o->ptr);
 
             if (objlen == 0) {
                 listDelNode(c->reply,listFirst(c->reply));
@@ -683,7 +692,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
             if (c->sentlen == objlen) {
                 listDelNode(c->reply,listFirst(c->reply));
                 c->sentlen = 0;
-                c->reply_bytes -= objlen;
+                c->reply_bytes -= objmem;
             }
         }
         /* Note that we avoid to send more than REDIS_MAX_WRITE_PER_EVENT
@@ -1222,7 +1231,7 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
  * the caller wishes. The main usage of this function currently is
  * enforcing the client output length limits. */
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c) {
-    unsigned long list_item_size = sizeof(listNode);
+    unsigned long list_item_size = sizeof(listNode)+sizeof(robj);
 
     return c->reply_bytes + (list_item_size*listLength(c->reply));
 }