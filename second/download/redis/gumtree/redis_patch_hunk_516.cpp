         if (s[j] == '\r' || s[j] == '\n') s[j] = ' ';
     }
     addReplyErrorLength(c,s,sdslen(s));
     sdsfree(s);
 }
 
-void addReplyStatusLength(redisClient *c, char *s, size_t len) {
+void addReplyStatusLength(client *c, const char *s, size_t len) {
     addReplyString(c,"+",1);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyStatus(redisClient *c, char *status) {
+void addReplyStatus(client *c, const char *status) {
     addReplyStatusLength(c,status,strlen(status));
 }
 
-void addReplyStatusFormat(redisClient *c, const char *fmt, ...) {
+void addReplyStatusFormat(client *c, const char *fmt, ...) {
     va_list ap;
     va_start(ap,fmt);
     sds s = sdscatvprintf(sdsempty(),fmt,ap);
     va_end(ap);
     addReplyStatusLength(c,s,sdslen(s));
     sdsfree(s);
 }
 
 /* Adds an empty object to the reply list that will contain the multi bulk
  * length, which is not known when this function is called. */
-void *addDeferredMultiBulkLength(redisClient *c) {
+void *addDeferredMultiBulkLength(client *c) {
     /* Note that we install the write event here even if the object is not
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
-    if (prepareClientToWrite(c) != REDIS_OK) return NULL;
-    listAddNodeTail(c->reply,createObject(REDIS_STRING,NULL));
+    if (prepareClientToWrite(c) != C_OK) return NULL;
+    listAddNodeTail(c->reply,createObject(OBJ_STRING,NULL));
     return listLast(c->reply);
 }
 
 /* Populate the length object and try gluing it to the next chunk. */
-void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
+void setDeferredMultiBulkLength(client *c, void *node, long length) {
     listNode *ln = (listNode*)node;
     robj *len, *next;
 
     /* Abort when *node is NULL (see addDeferredMultiBulkLength). */
     if (node == NULL) return;
 
     len = listNodeValue(ln);
     len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
-    len->encoding = REDIS_ENCODING_RAW; /* in case it was an EMBSTR. */
-    c->reply_bytes += zmalloc_size_sds(len->ptr);
+    len->encoding = OBJ_ENCODING_RAW; /* in case it was an EMBSTR. */
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
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
 /* Add a double as a bulk reply */
-void addReplyDouble(redisClient *c, double d) {
+void addReplyDouble(client *c, double d) {
     char dbuf[128], sbuf[128];
     int dlen, slen;
     if (isinf(d)) {
         /* Libc in odd systems (Hi Solaris!) will format infinite in a
          * different way, so better to handle it in an explicit way. */
         addReplyBulkCString(c, d > 0 ? "inf" : "-inf");
