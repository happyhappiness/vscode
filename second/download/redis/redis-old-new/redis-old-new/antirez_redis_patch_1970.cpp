@@ -13,13 +13,9 @@ int listMatchObjects(void *a, void *b) {
 redisClient *createClient(int fd) {
     redisClient *c;
 
-    /* Make sure to allocate a multiple of the page size to prevent wasting
-     * memory. A page size of 4096 is assumed here. We need to compensate
-     * for the zmalloc overhead of sizeof(size_t) bytes. */
-    size_t size = 8192-sizeof(size_t);
-    redisAssert(size > sizeof(redisClient));
-    c = zmalloc(size);
-    c->buflen = size-sizeof(redisClient);
+    /* Allocate more space to hold a static write buffer. */
+    c = zmalloc(sizeof(redisClient)+REDIS_REPLY_CHUNK_BYTES);
+    c->buflen = REDIS_REPLY_CHUNK_BYTES;
     c->bufpos = 0;
 
     anetNonBlock(NULL,fd);
@@ -71,40 +67,95 @@ int _ensureFileEvent(redisClient *c) {
     return REDIS_OK;
 }
 
-void _addReplyObjectToList(redisClient *c, robj *obj) {
-    redisAssert(obj->type == REDIS_STRING &&
-                obj->encoding == REDIS_ENCODING_RAW);
-    listAddNodeTail(c->reply,obj);
+/* Create a duplicate of the last object in the reply list when
+ * it is not exclusively owned by the reply list. */
+robj *dupLastObjectIfNeeded(list *reply) {
+    robj *new, *cur;
+    listNode *ln;
+    redisAssert(listLength(reply) > 0);
+    ln = listLast(reply);
+    cur = listNodeValue(ln);
+    if (cur->refcount > 1) {
+        new = dupStringObject(cur);
+        decrRefCount(cur);
+        listNodeValue(ln) = new;
+    }
+    return listNodeValue(ln);
 }
 
-void _ensureBufferInReplyList(redisClient *c) {
-    sds buffer = sdsnewlen(NULL,REDIS_REPLY_CHUNK_SIZE);
-    sdsupdatelen(buffer); /* sdsnewlen expects non-empty string */
-    listAddNodeTail(c->reply,createObject(REDIS_REPLY_NODE,buffer));
+int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
+    size_t available = c->buflen-c->bufpos;
+
+    /* If there already are entries in the reply list, we cannot
+     * add anything more to the static buffer. */
+    if (listLength(c->reply) > 0) return REDIS_ERR;
+
+    /* Check that the buffer has enough space available for this string. */
+    if (len > available) return REDIS_ERR;
+
+    memcpy(c->buf+c->bufpos,s,len);
+    c->bufpos+=len;
+    return REDIS_OK;
 }
 
-void _addReplyStringToBuffer(redisClient *c, char *s, size_t len) {
-    size_t available = 0;
-    redisAssert(len < REDIS_REPLY_CHUNK_THRESHOLD);
-    if (listLength(c->reply) > 0) {
-        robj *o = listNodeValue(listLast(c->reply));
-
-        /* Make sure to append to a reply node with enough bytes available. */
-        if (o->type == REDIS_REPLY_NODE) available = sdsavail(o->ptr);
-        if (o->type != REDIS_REPLY_NODE || len > available) {
-            _ensureBufferInReplyList(c);
-            _addReplyStringToBuffer(c,s,len);
+void _addReplyObjectToList(redisClient *c, robj *o) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        incrRefCount(o);
+        listAddNodeTail(c->reply,o);
+    } else {
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,o->ptr,sdslen(o->ptr));
         } else {
-            o->ptr = sdscatlen(o->ptr,s,len);
+            incrRefCount(o);
+            listAddNodeTail(c->reply,o);
         }
+    }
+}
+
+/* This method takes responsibility over the sds. When it is no longer
+ * needed it will be free'd, otherwise it ends up in a robj. */
+void _addReplySdsToList(redisClient *c, sds s) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
     } else {
-        available = c->buflen-c->bufpos;
-        if (len > available) {
-            _ensureBufferInReplyList(c);
-            _addReplyStringToBuffer(c,s,len);
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,s,sdslen(s));
+            sdsfree(s);
         } else {
-            memcpy(c->buf+c->bufpos,s,len);
-            c->bufpos += len;
+            listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
+        }
+    }
+}
+
+void _addReplyStringToList(redisClient *c, char *s, size_t len) {
+    robj *tail;
+    if (listLength(c->reply) == 0) {
+        listAddNodeTail(c->reply,createStringObject(s,len));
+    } else {
+        tail = listNodeValue(listLast(c->reply));
+
+        /* Append to this object when possible. */
+        if (tail->ptr != NULL &&
+            sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
+        {
+            tail = dupLastObjectIfNeeded(c->reply);
+            tail->ptr = sdscatlen(tail->ptr,s,len);
+        } else {
+            listAddNodeTail(c->reply,createStringObject(s,len));
         }
     }
 }
@@ -118,13 +169,9 @@ void addReply(redisClient *c, robj *obj) {
         /* This increments the refcount. */
         obj = getDecodedObject(obj);
     }
-
-    if (sdslen(obj->ptr) < REDIS_REPLY_CHUNK_THRESHOLD) {
-        _addReplyStringToBuffer(c,obj->ptr,sdslen(obj->ptr));
-        decrRefCount(obj);
-    } else {
+    if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
         _addReplyObjectToList(c,obj);
-    }
+    decrRefCount(obj);
 }
 
 void addReplySds(redisClient *c, sds s) {
@@ -133,28 +180,25 @@ void addReplySds(redisClient *c, sds s) {
         sdsfree(s);
         return;
     }
-    if (sdslen(s) < REDIS_REPLY_CHUNK_THRESHOLD) {
-        _addReplyStringToBuffer(c,s,sdslen(s));
+    if (_addReplyToBuffer(c,s,sdslen(s)) == REDIS_OK) {
         sdsfree(s);
     } else {
-        _addReplyObjectToList(c,createObject(REDIS_STRING,s));
+        /* This method free's the sds when it is no longer needed. */
+        _addReplySdsToList(c,s);
     }
 }
 
 void addReplyString(redisClient *c, char *s, size_t len) {
     if (_ensureFileEvent(c) != REDIS_OK) return;
-    if (len < REDIS_REPLY_CHUNK_THRESHOLD) {
-        _addReplyStringToBuffer(c,s,len);
-    } else {
-        _addReplyObjectToList(c,createStringObject(s,len));
-    }
+    if (_addReplyToBuffer(c,s,len) != REDIS_OK)
+        _addReplyStringToList(c,s,len);
 }
 
 /* Adds an empty object to the reply list that will contain the multi bulk
  * length, which is not known when this function is called. */
 void *addDeferredMultiBulkLength(redisClient *c) {
     if (_ensureFileEvent(c) != REDIS_OK) return NULL;
-    _addReplyObjectToList(c,createObject(REDIS_STRING,NULL));
+    listAddNodeTail(c->reply,createObject(REDIS_STRING,NULL));
     return listLast(c->reply);
 }
 
@@ -170,9 +214,10 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
-        /* Only glue when the next node is a reply chunk. */
-        if (next->type == REDIS_REPLY_NODE) {
-            len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
+
+        /* Only glue when the next node is an sds */
+        if (next->ptr != NULL) {
+            len->ptr = sdscat(len->ptr,next->ptr);
             listDelNode(c->reply,ln->next);
         }
     }