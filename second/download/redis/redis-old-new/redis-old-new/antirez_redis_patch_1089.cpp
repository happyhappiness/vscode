@@ -184,12 +184,15 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
     if (listLength(c->reply) == 0) {
         incrRefCount(o);
         listAddNodeTail(c->reply,o);
-        c->reply_bytes += zmalloc_size_sds(o->ptr);
+        c->reply_bytes += (o->encoding == REDIS_ENCODING_RAW) ?
+                          zmalloc_size_sds(o->ptr) :
+                          sdslen(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
+            tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= zmalloc_size_sds(tail->ptr);
@@ -199,7 +202,9 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
         } else {
             incrRefCount(o);
             listAddNodeTail(c->reply,o);
-            c->reply_bytes += zmalloc_size_sds(o->ptr);
+            c->reply_bytes += (o->encoding == REDIS_ENCODING_RAW) ?
+                              zmalloc_size_sds(o->ptr) :
+                              sdslen(o->ptr);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -222,7 +227,7 @@ void _addReplySdsToList(redisClient *c, sds s) {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
-        if (tail->ptr != NULL &&
+        if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= zmalloc_size_sds(tail->ptr);
@@ -247,12 +252,14 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
         robj *o = createStringObject(s,len);
 
         listAddNodeTail(c->reply,o);
-        c->reply_bytes += zmalloc_size_sds(o->ptr);
+        c->reply_bytes += (o->encoding == REDIS_ENCODING_RAW) ?
+                          zmalloc_size_sds(o->ptr) :
+                          sdslen(o->ptr);
     } else {
         tail = listNodeValue(listLast(c->reply));
 
         /* Append to this object when possible. */
-        if (tail->ptr != NULL &&
+        if (tail->ptr != NULL && tail->encoding == REDIS_ENCODING_RAW &&
             sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= zmalloc_size_sds(tail->ptr);
@@ -263,7 +270,9 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
             robj *o = createStringObject(s,len);
 
             listAddNodeTail(c->reply,o);
-            c->reply_bytes += zmalloc_size_sds(o->ptr);
+            c->reply_bytes += (o->encoding == REDIS_ENCODING_RAW) ?
+                              zmalloc_size_sds(o->ptr) :
+                              sdslen(o->ptr);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -284,7 +293,7 @@ void addReply(redisClient *c, robj *obj) {
      * If the encoding is RAW and there is room in the static buffer
      * we'll be able to send the object to the client without
      * messing with its page. */
-    if (obj->encoding == REDIS_ENCODING_RAW) {
+    if (sdsEncodedObject(obj)) {
         if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
             _addReplyObjectToList(c,obj);
     } else if (obj->encoding == REDIS_ENCODING_INT) {
@@ -396,6 +405,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
+    len->encoding = REDIS_ENCODING_RAW; /* in case it was an EMBSTR. */
     c->reply_bytes += zmalloc_size_sds(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
@@ -468,7 +478,7 @@ void addReplyMultiBulkLen(redisClient *c, long length) {
 void addReplyBulkLen(redisClient *c, robj *obj) {
     size_t len;
 
-    if (obj->encoding == REDIS_ENCODING_RAW) {
+    if (sdsEncodedObject(obj)) {
         len = sdslen(obj->ptr);
     } else {
         long n = (long)obj->ptr;
@@ -765,7 +775,9 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         } else {
             o = listNodeValue(listFirst(c->reply));
             objlen = sdslen(o->ptr);
-            objmem = zmalloc_size_sds(o->ptr);
+            objmem = (o->encoding == REDIS_ENCODING_RAW) ?
+                        zmalloc_size_sds(o->ptr) :
+                        sdslen(o->ptr);
 
             if (objlen == 0) {
                 listDelNode(c->reply,listFirst(c->reply));