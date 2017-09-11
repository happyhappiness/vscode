@@ -52,9 +52,13 @@ size_t getStringObjectSdsUsedMemory(robj *o) {
     }
 }
 
+/* Client.reply list dup and free methods. */
 void *dupClientReplyValue(void *o) {
-    incrRefCount((robj*)o);
-    return o;
+    return sdsdup(o);
+}
+
+void freeClientReplyValue(void *o) {
+    sdsfree(o);
 }
 
 int listMatchObjects(void *a, void *b) {
@@ -109,7 +113,7 @@ client *createClient(int fd) {
     c->reply = listCreate();
     c->reply_bytes = 0;
     c->obuf_soft_limit_reached_time = 0;
-    listSetFreeMethod(c->reply,decrRefCountVoid);
+    listSetFreeMethod(c->reply,freeClientReplyValue);
     listSetDupMethod(c->reply,dupClientReplyValue);
     c->btype = BLOCKED_NONE;
     c->bpop.timeout = 0;
@@ -144,7 +148,7 @@ client *createClient(int fd) {
  * event handler in the following cases:
  *
  * 1) The event handler should already be installed since the output buffer
- *    already contained something.
+ *    already contains something.
  * 2) The client is a slave but not yet online, so we want to just accumulate
  *    writes in the buffer but not actually sending them yet.
  *
@@ -186,22 +190,6 @@ int prepareClientToWrite(client *c) {
     return C_OK;
 }
 
-/* Create a duplicate of the last object in the reply list when
- * it is not exclusively owned by the reply list. */
-robj *dupLastObjectIfNeeded(list *reply) {
-    robj *new, *cur;
-    listNode *ln;
-    serverAssert(listLength(reply) > 0);
-    ln = listLast(reply);
-    cur = listNodeValue(ln);
-    if (cur->refcount > 1) {
-        new = dupStringObject(cur);
-        decrRefCount(cur);
-        listNodeValue(ln) = new;
-    }
-    return listNodeValue(ln);
-}
-
 /* -----------------------------------------------------------------------------
  * Low level functions to add more data to output buffers.
  * -------------------------------------------------------------------------- */
@@ -224,30 +212,26 @@ int _addReplyToBuffer(client *c, const char *s, size_t len) {
 }
 
 void _addReplyObjectToList(client *c, robj *o) {
-    robj *tail;
-
     if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
-        incrRefCount(o);
-        listAddNodeTail(c->reply,o);
-        c->reply_bytes += getStringObjectSdsUsedMemory(o);
+        sds s = sdsdup(o->ptr);
+        listAddNodeTail(c->reply,s);
+        c->reply_bytes += sdslen(s);
     } else {
-        tail = listNodeValue(listLast(c->reply));
-
-        /* Append to this object when possible. */
-        if (tail->ptr != NULL &&
-            tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+sdslen(o->ptr) <= PROTO_REPLY_CHUNK_BYTES)
-        {
-            c->reply_bytes -= sdsZmallocSize(tail->ptr);
-            tail = dupLastObjectIfNeeded(c->reply);
-            tail->ptr = sdscatlen(tail->ptr,o->ptr,sdslen(o->ptr));
-            c->reply_bytes += sdsZmallocSize(tail->ptr);
+        listNode *ln = listLast(c->reply);
+        sds tail = listNodeValue(ln);
+
+        /* Append to this object when possible. If tail == NULL it was
+         * set via addDeferredMultiBulkLength(). */
+        if (tail && sdslen(tail)+sdslen(o->ptr) <= PROTO_REPLY_CHUNK_BYTES) {
+            tail = sdscatsds(tail,o->ptr);
+            listNodeValue(ln) = tail;
+            c->reply_bytes += sdslen(o->ptr);
         } else {
-            incrRefCount(o);
-            listAddNodeTail(c->reply,o);
-            c->reply_bytes += getStringObjectSdsUsedMemory(o);
+            sds s = sdsdup(o->ptr);
+            listAddNodeTail(c->reply,s);
+            c->reply_bytes += sdslen(s);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -256,62 +240,54 @@ void _addReplyObjectToList(client *c, robj *o) {
 /* This method takes responsibility over the sds. When it is no longer
  * needed it will be free'd, otherwise it ends up in a robj. */
 void _addReplySdsToList(client *c, sds s) {
-    robj *tail;
-
     if (c->flags & CLIENT_CLOSE_AFTER_REPLY) {
         sdsfree(s);
         return;
     }
 
     if (listLength(c->reply) == 0) {
-        listAddNodeTail(c->reply,createObject(OBJ_STRING,s));
-        c->reply_bytes += sdsZmallocSize(s);
+        listAddNodeTail(c->reply,s);
+        c->reply_bytes += sdslen(s);
     } else {
-        tail = listNodeValue(listLast(c->reply));
-
-        /* Append to this object when possible. */
-        if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+sdslen(s) <= PROTO_REPLY_CHUNK_BYTES)
-        {
-            c->reply_bytes -= sdsZmallocSize(tail->ptr);
-            tail = dupLastObjectIfNeeded(c->reply);
-            tail->ptr = sdscatlen(tail->ptr,s,sdslen(s));
-            c->reply_bytes += sdsZmallocSize(tail->ptr);
+        listNode *ln = listLast(c->reply);
+        sds tail = listNodeValue(ln);
+
+        /* Append to this object when possible. If tail == NULL it was
+         * set via addDeferredMultiBulkLength(). */
+        if (tail && sdslen(tail)+sdslen(s) <= PROTO_REPLY_CHUNK_BYTES) {
+            tail = sdscatsds(tail,s);
+            listNodeValue(ln) = tail;
+            c->reply_bytes += sdslen(s);
             sdsfree(s);
         } else {
-            listAddNodeTail(c->reply,createObject(OBJ_STRING,s));
-            c->reply_bytes += sdsZmallocSize(s);
+            listAddNodeTail(c->reply,s);
+            c->reply_bytes += sdslen(s);
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
 void _addReplyStringToList(client *c, const char *s, size_t len) {
-    robj *tail;
-
     if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
-        robj *o = createStringObject(s,len);
-
-        listAddNodeTail(c->reply,o);
-        c->reply_bytes += getStringObjectSdsUsedMemory(o);
+        sds node = sdsnewlen(s,len);
+        listAddNodeTail(c->reply,node);
+        c->reply_bytes += len;
     } else {
-        tail = listNodeValue(listLast(c->reply));
-
-        /* Append to this object when possible. */
-        if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+len <= PROTO_REPLY_CHUNK_BYTES)
-        {
-            c->reply_bytes -= sdsZmallocSize(tail->ptr);
-            tail = dupLastObjectIfNeeded(c->reply);
-            tail->ptr = sdscatlen(tail->ptr,s,len);
-            c->reply_bytes += sdsZmallocSize(tail->ptr);
+        listNode *ln = listLast(c->reply);
+        sds tail = listNodeValue(ln);
+
+        /* Append to this object when possible. If tail == NULL it was
+         * set via addDeferredMultiBulkLength(). */
+        if (tail && sdslen(tail)+len <= PROTO_REPLY_CHUNK_BYTES) {
+            tail = sdscatlen(tail,s,len);
+            listNodeValue(ln) = tail;
+            c->reply_bytes += len;
         } else {
-            robj *o = createStringObject(s,len);
-
-            listAddNodeTail(c->reply,o);
-            c->reply_bytes += getStringObjectSdsUsedMemory(o);
+            sds node = sdsnewlen(s,len);
+            listAddNodeTail(c->reply,node);
+            c->reply_bytes += len;
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -430,32 +406,32 @@ void *addDeferredMultiBulkLength(client *c) {
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
     if (prepareClientToWrite(c) != C_OK) return NULL;
-    listAddNodeTail(c->reply,createObject(OBJ_STRING,NULL));
+    listAddNodeTail(c->reply,NULL); /* NULL is our placeholder. */
     return listLast(c->reply);
 }
 
 /* Populate the length object and try gluing it to the next chunk. */
 void setDeferredMultiBulkLength(client *c, void *node, long length) {
     listNode *ln = (listNode*)node;
-    robj *len, *next;
+    sds len, next;
 
-    /* Abort when *node is NULL (see addDeferredMultiBulkLength). */
+    /* Abort when *node is NULL: when the client should not accept writes
+     * we return NULL in addDeferredMultiBulkLength() */
     if (node == NULL) return;
 
-    len = listNodeValue(ln);
-    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    len->encoding = OBJ_ENCODING_RAW; /* in case it was an EMBSTR. */
-    c->reply_bytes += sdsZmallocSize(len->ptr);
+    len = sdscatprintf(sdsnewlen("*",1),"%ld\r\n",length);
+    listNodeValue(ln) = len;
+    c->reply_bytes += sdslen(len);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
         /* Only glue when the next node is non-NULL (an sds in this case) */
-        if (next->ptr != NULL) {
-            c->reply_bytes -= sdsZmallocSize(len->ptr);
-            c->reply_bytes -= getStringObjectSdsUsedMemory(next);
-            len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
-            c->reply_bytes += sdsZmallocSize(len->ptr);
+        if (next != NULL) {
+            len = sdscatsds(len,next);
             listDelNode(c->reply,ln->next);
+            listNodeValue(ln) = len;
+            /* No need to update c->reply_bytes: we are just moving the same
+             * amount of bytes from one node to another. */
         }
     }
     asyncCloseClientOnOutputBufferLimitReached(c);
@@ -845,8 +821,7 @@ void freeClientsInAsyncFreeQueue(void) {
 int writeToClient(int fd, client *c, int handler_installed) {
     ssize_t nwritten = 0, totwritten = 0;
     size_t objlen;
-    size_t objmem;
-    robj *o;
+    sds o;
 
     while(clientHasPendingReplies(c)) {
         if (c->bufpos > 0) {
@@ -863,16 +838,14 @@ int writeToClient(int fd, client *c, int handler_installed) {
             }
         } else {
             o = listNodeValue(listFirst(c->reply));
-            objlen = sdslen(o->ptr);
-            objmem = getStringObjectSdsUsedMemory(o);
+            objlen = sdslen(o);
 
             if (objlen == 0) {
                 listDelNode(c->reply,listFirst(c->reply));
-                c->reply_bytes -= objmem;
                 continue;
             }
 
-            nwritten = write(fd, ((char*)o->ptr)+c->sentlen,objlen-c->sentlen);
+            nwritten = write(fd, o + c->sentlen, objlen - c->sentlen);
             if (nwritten <= 0) break;
             c->sentlen += nwritten;
             totwritten += nwritten;
@@ -881,7 +854,7 @@ int writeToClient(int fd, client *c, int handler_installed) {
             if (c->sentlen == objlen) {
                 listDelNode(c->reply,listFirst(c->reply));
                 c->sentlen = 0;
-                c->reply_bytes -= objmem;
+                c->reply_bytes -= objlen;
             }
         }
         /* Note that we avoid to send more than NET_MAX_WRITES_PER_EVENT
@@ -1626,7 +1599,9 @@ void rewriteClientCommandArgument(client *c, int i, robj *newval) {
  * the caller wishes. The main usage of this function currently is
  * enforcing the client output length limits. */
 unsigned long getClientOutputBufferMemoryUsage(client *c) {
-    unsigned long list_item_size = sizeof(listNode)+sizeof(robj);
+    unsigned long list_item_size = sizeof(listNode)+5;
+    /* The +5 above means we assume an sds16 hdr, may not be true
+     * but is not going to be a problem. */
 
     return c->reply_bytes + (list_item_size*listLength(c->reply));
 }