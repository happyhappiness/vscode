  * length, which is not known when this function is called. */
 void *addDeferredMultiBulkLength(client *c) {
     /* Note that we install the write event here even if the object is not
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
 }
 
 /* Add a double as a bulk reply */
