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
-    c->reply_bytes += zmalloc_size(o->ptr);
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
@@ -165,21 +176,24 @@ void _addReplySdsToList(redisClient *c, sds s) {
         return;
     }
 
-    c->reply_bytes += zmalloc_size(s);
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
@@ -194,23 +208,23 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
         robj *o = createStringObject(s,len);
 
         listAddNodeTail(c->reply,o);
-        c->reply_bytes += zmalloc_size(o->ptr);
+        c->reply_bytes += zmalloc_size_sds(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
-            c->reply_bytes -= zmalloc_size(tail->ptr);
+            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,len);
-            c->reply_bytes += zmalloc_size(tail->ptr);
+            c->reply_bytes += zmalloc_size_sds(tail->ptr);
         } else {
             robj *o = createStringObject(s,len);
 
             listAddNodeTail(c->reply,o);
-            c->reply_bytes += zmalloc_size(o->ptr);
+            c->reply_bytes += zmalloc_size_sds(o->ptr);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -343,7 +357,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    c->reply_bytes += zmalloc_size(len->ptr);
+    c->reply_bytes += zmalloc_size_sds(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
@@ -671,7 +685,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         } else {
             o = listNodeValue(listFirst(c->reply));
             objlen = sdslen(o->ptr);
-            objmem = zmalloc_size(o->ptr);
+            objmem = zmalloc_size_sds(o->ptr);
 
             if (objlen == 0) {
                 listDelNode(c->reply,listFirst(c->reply));