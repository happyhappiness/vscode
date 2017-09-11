@@ -33,21 +33,14 @@
 
 static void setProtocolError(redisClient *c, int pos);
 
-/* To evaluate the output buffer size of a client we need to get size of
- * allocated objects, however we can't used zmalloc_size() directly on sds
- * strings because of the trick they use to work (the header is before the
- * returned pointer), so we use this helper function. */
-size_t zmalloc_size_sds(sds s) {
-    return zmalloc_size(s-sizeof(struct sdshdr));
-}
 
 /* Return the amount of memory used by the sds string at object->ptr
  * for a string object. */
 size_t getStringObjectSdsUsedMemory(robj *o) {
     redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
     switch(o->encoding) {
-    case REDIS_ENCODING_RAW: return zmalloc_size_sds(o->ptr);
-    case REDIS_ENCODING_EMBSTR: return sdslen(o->ptr);
+    case REDIS_ENCODING_RAW: return sdsZmallocSize(o->ptr);
+    case REDIS_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
     default: return 0; /* Just integer encoding for now. */
     }
 }
@@ -235,10 +228,10 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
             tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
         {
-            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
+            c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,o->ptr,sdslen(o->ptr));
-            c->reply_bytes += zmalloc_size_sds(tail->ptr);
+            c->reply_bytes += sdsZmallocSize(tail->ptr);
         } else {
             incrRefCount(o);
             listAddNodeTail(c->reply,o);
@@ -260,22 +253,22 @@ void _addReplySdsToList(redisClient *c, sds s) {
 
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
-        c->reply_bytes += zmalloc_size_sds(s);
+        c->reply_bytes += sdsZmallocSize(s);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
         {
-            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
+            c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,sdslen(s));
-            c->reply_bytes += zmalloc_size_sds(tail->ptr);
+            c->reply_bytes += sdsZmallocSize(tail->ptr);
             sdsfree(s);
         } else {
             listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
-            c->reply_bytes += zmalloc_size_sds(s);
+            c->reply_bytes += sdsZmallocSize(s);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -298,10 +291,10 @@ void _addReplyStringToList(redisClient *c, const char *s, size_t len) {
         if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
-            c->reply_bytes -= zmalloc_size_sds(tail->ptr);
+            c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
             tail->ptr = sdscatlen(tail->ptr,s,len);
-            c->reply_bytes += zmalloc_size_sds(tail->ptr);
+            c->reply_bytes += sdsZmallocSize(tail->ptr);
         } else {
             robj *o = createStringObject(s,len);
 
@@ -440,16 +433,16 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
     len->encoding = REDIS_ENCODING_RAW; /* in case it was an EMBSTR. */
-    c->reply_bytes += zmalloc_size_sds(len->ptr);
+    c->reply_bytes += sdsZmallocSize(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
         /* Only glue when the next node is non-NULL (an sds in this case) */
         if (next->ptr != NULL) {
-            c->reply_bytes -= zmalloc_size_sds(len->ptr);
+            c->reply_bytes -= sdsZmallocSize(len->ptr);
             c->reply_bytes -= getStringObjectSdsUsedMemory(next);
             len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
-            c->reply_bytes += zmalloc_size_sds(len->ptr);
+            c->reply_bytes += sdsZmallocSize(len->ptr);
             listDelNode(c->reply,ln->next);
         }
     }