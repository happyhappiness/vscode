@@ -47,6 +47,7 @@ redisClient *createClient(int fd) {
     c->authenticated = 0;
     c->replstate = REDIS_REPL_NONE;
     c->reply = listCreate();
+    c->reply_bytes = 0;
     listSetFreeMethod(c->reply,decrRefCount);
     listSetDupMethod(c->reply,dupClientReplyValue);
     c->bpop.keys = NULL;
@@ -137,6 +138,7 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
             listAddNodeTail(c->reply,o);
         }
     }
+    c->reply_bytes += sdslen(o->ptr);
 }
 
 /* This method takes responsibility over the sds. When it is no longer
@@ -149,6 +151,7 @@ void _addReplySdsToList(redisClient *c, sds s) {
         return;
     }
 
+    c->reply_bytes += sdslen(s);
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
     } else {
@@ -187,6 +190,7 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
             listAddNodeTail(c->reply,createStringObject(s,len));
         }
     }
+    c->reply_bytes += len;
 }
 
 /* -----------------------------------------------------------------------------
@@ -304,6 +308,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
+    c->reply_bytes += sdslen(len->ptr);
     if (ln->next != NULL) {
         next = listNodeValue(ln->next);
 
@@ -411,6 +416,7 @@ void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
     dst->reply = listDup(src->reply);
     memcpy(dst->buf,src->buf,src->bufpos);
     dst->bufpos = src->bufpos;
+    dst->reply_bytes = src->reply_bytes;
 }
 
 static void acceptCommonHandler(int fd) {
@@ -606,6 +612,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
             if (c->sentlen == objlen) {
                 listDelNode(c->reply,listFirst(c->reply));
                 c->sentlen = 0;
+                c->reply_bytes -= objlen;
             }
         }
         /* Note that we avoid to send more thank REDIS_MAX_WRITE_PER_EVENT
@@ -1008,7 +1015,7 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
     return sdscatprintf(sdsempty(),
-        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu events=%s cmd=%s",
+        "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d qbuf=%lu obl=%lu oll=%lu omem=%lu events=%s cmd=%s",
         ip,port,client->fd,
         (long)(now - client->lastinteraction),
         flags,
@@ -1018,6 +1025,7 @@ sds getClientInfoString(redisClient *client) {
         (unsigned long) sdslen(client->querybuf),
         (unsigned long) client->bufpos,
         (unsigned long) listLength(client->reply),
+        getClientOutputBufferMemoryUsage(client),
         events,
         client->lastcmd ? client->lastcmd->name : "NULL");
 }
@@ -1122,3 +1130,22 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
         redisAssertWithInfo(c,NULL,c->cmd != NULL);
     }
 }
+
+/* This function returns the number of bytes that Redis is virtually
+ * using to store the reply still not read by the client.
+ * It is "virtual" since the reply output list may contain objects that
+ * are shared and are not really using additional memory.
+ *
+ * The function returns the total sum of the length of all the objects
+ * stored in the output list, plus the memory used to allocate every
+ * list node. The static reply buffer is not taken into account since it
+ * is allocated anyway.
+ *
+ * Note: this function is very fast so can be called as many time as
+ * the caller wishes. The main usage of this function currently is
+ * enforcing the client output lenght limits. */
+unsigned long getClientOutputBufferMemoryUsage(redisClient *c) {
+    unsigned long list_item_size = sizeof(listNode);
+
+    return c->reply_bytes + (list_item_size*listLength(c->reply));
+}