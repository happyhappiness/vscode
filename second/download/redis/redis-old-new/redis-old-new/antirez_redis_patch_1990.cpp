@@ -145,6 +145,34 @@ void addReplyString(redisClient *c, char *s, size_t len) {
     }
 }
 
+/* Adds an empty object to the reply list that will contain the multi bulk
+ * length, which is not known when this function is called. */
+void *addDeferredMultiBulkLength(redisClient *c) {
+    if (_ensureFileEvent(c) != REDIS_OK) return NULL;
+    _addReplyObjectToList(c,createObject(REDIS_STRING,NULL));
+    return listLast(c->reply);
+}
+
+/* Populate the length object and try glueing it to the next chunk. */
+void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
+    listNode *ln = (listNode*)node;
+    robj *len, *next;
+
+    /* Abort when *node is NULL (see addDeferredMultiBulkLength). */
+    if (node == NULL) return;
+
+    len = listNodeValue(ln);
+    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
+    if (ln->next != NULL) {
+        next = listNodeValue(ln->next);
+        /* Only glue when the next node is a reply chunk. */
+        if (next->type == REDIS_REPLY_NODE) {
+            len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
+            listDelNode(c->reply,ln->next);
+        }
+    }
+}
+
 void addReplyDouble(redisClient *c, double d) {
     char dbuf[128], sbuf[128];
     int dlen, slen;