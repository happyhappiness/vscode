@@ -67,11 +67,23 @@ redisClient *createClient(int fd) {
     return c;
 }
 
-/* Set the event loop to listen for write events on the client's socket.
- * Typically gets called every time a reply is built. */
-int _installWriteEvent(redisClient *c) {
+/* This function is called every time we are going to transmit new data
+ * to the client. The behavior is the following:
+ *
+ * If the client should receive new data (normal clients will) the function
+ * returns REDIS_OK, and make sure to install the write handler in our event
+ * loop so that when the socket is writable new data gets written.
+ *
+ * If the client should not receive new data, because it is a fake client
+ * or a slave, or because the setup of the write handler failed, the function
+ * returns REDIS_ERR.
+ *
+ * Typically gets called every time a reply is built, before adding more
+ * data to the clients output buffers. If the function returns REDIS_ERR no
+ * data should be appended to the output buffers. */
+int prepareClientToWrite(redisClient *c) {
     if (c->flags & REDIS_LUA_CLIENT) return REDIS_OK;
-    if (c->fd <= 0) return REDIS_ERR;
+    if (c->fd <= 0) return REDIS_ERR; /* Fake client */
     if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
          c->replstate == REDIS_REPL_ONLINE) &&
@@ -203,7 +215,7 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
  * -------------------------------------------------------------------------- */
 
 void addReply(redisClient *c, robj *obj) {
-    if (_installWriteEvent(c) != REDIS_OK) return;
+    if (prepareClientToWrite(c) != REDIS_OK) return;
 
     /* This is an important place where we can avoid copy-on-write
      * when there is a saving child running, avoiding touching the
@@ -215,19 +227,31 @@ void addReply(redisClient *c, robj *obj) {
     if (obj->encoding == REDIS_ENCODING_RAW) {
         if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
             _addReplyObjectToList(c,obj);
-    } else {
-        /* FIXME: convert the long into string and use _addReplyToBuffer()
-         * instead of calling getDecodedObject. As this place in the
-         * code is too performance critical. */
+    } else if (obj->encoding == REDIS_ENCODING_INT) {
+        /* Optimization: if there is room in the static buffer for 32 bytes
+         * (more than the max chars a 64 bit integer can take as string) we
+         * avoid decoding the object and go for the lower level approach. */
+        if (listLength(c->reply) == 0 && (sizeof(c->buf) - c->bufpos) >= 32) {
+            char buf[32];
+            int len;
+
+            len = ll2string(buf,sizeof(buf),(long)obj->ptr);
+            if (_addReplyToBuffer(c,buf,len) == REDIS_OK)
+                return;
+            /* else... continue with the normal code path, but should never
+             * happen actually since we verified there is room. */
+        }
         obj = getDecodedObject(obj);
         if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
             _addReplyObjectToList(c,obj);
         decrRefCount(obj);
+    } else {
+        redisPanic("Wrong obj->encoding in addReply()");
     }
 }
 
 void addReplySds(redisClient *c, sds s) {
-    if (_installWriteEvent(c) != REDIS_OK) {
+    if (prepareClientToWrite(c) != REDIS_OK) {
         /* The caller expects the sds to be free'd. */
         sdsfree(s);
         return;
@@ -241,19 +265,19 @@ void addReplySds(redisClient *c, sds s) {
 }
 
 void addReplyString(redisClient *c, char *s, size_t len) {
-    if (_installWriteEvent(c) != REDIS_OK) return;
+    if (prepareClientToWrite(c) != REDIS_OK) return;
     if (_addReplyToBuffer(c,s,len) != REDIS_OK)
         _addReplyStringToList(c,s,len);
 }
 
-void _addReplyError(redisClient *c, char *s, size_t len) {
+void addReplyErrorLength(redisClient *c, char *s, size_t len) {
     addReplyString(c,"-ERR ",5);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
 void addReplyError(redisClient *c, char *err) {
-    _addReplyError(c,err,strlen(err));
+    addReplyErrorLength(c,err,strlen(err));
 }
 
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
@@ -268,26 +292,26 @@ void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
     for (j = 0; j < l; j++) {
         if (s[j] == '\r' || s[j] == '\n') s[j] = ' ';
     }
-    _addReplyError(c,s,sdslen(s));
+    addReplyErrorLength(c,s,sdslen(s));
     sdsfree(s);
 }
 
-void _addReplyStatus(redisClient *c, char *s, size_t len) {
+void addReplyStatusLength(redisClient *c, char *s, size_t len) {
     addReplyString(c,"+",1);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
 void addReplyStatus(redisClient *c, char *status) {
-    _addReplyStatus(c,status,strlen(status));
+    addReplyStatusLength(c,status,strlen(status));
 }
 
 void addReplyStatusFormat(redisClient *c, const char *fmt, ...) {
     va_list ap;
     va_start(ap,fmt);
     sds s = sdscatvprintf(sdsempty(),fmt,ap);
     va_end(ap);
-    _addReplyStatus(c,s,sdslen(s));
+    addReplyStatusLength(c,s,sdslen(s));
     sdsfree(s);
 }
 
@@ -297,7 +321,7 @@ void *addDeferredMultiBulkLength(redisClient *c) {
     /* Note that we install the write event here even if the object is not
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
-    if (_installWriteEvent(c) != REDIS_OK) return NULL;
+    if (prepareClientToWrite(c) != REDIS_OK) return NULL;
     listAddNodeTail(c->reply,createObject(REDIS_STRING,NULL));
     return listLast(c->reply);
 }
@@ -336,7 +360,7 @@ void addReplyDouble(redisClient *c, double d) {
 
 /* Add a long long as integer reply or bulk len / multi bulk count.
  * Basically this is used to output <prefix><long long><crlf>. */
-void _addReplyLongLong(redisClient *c, long long ll, char prefix) {
+void addReplyLongLongWithPrefix(redisClient *c, long long ll, char prefix) {
     char buf[128];
     int len;
     buf[0] = prefix;
@@ -352,11 +376,11 @@ void addReplyLongLong(redisClient *c, long long ll) {
     else if (ll == 1)
         addReply(c,shared.cone);
     else
-        _addReplyLongLong(c,ll,':');
+        addReplyLongLongWithPrefix(c,ll,':');
 }
 
 void addReplyMultiBulkLen(redisClient *c, long length) {
-    _addReplyLongLong(c,length,'*');
+    addReplyLongLongWithPrefix(c,length,'*');
 }
 
 /* Create the length prefix of a bulk reply, example: $2234 */
@@ -378,7 +402,7 @@ void addReplyBulkLen(redisClient *c, robj *obj) {
             len++;
         }
     }
-    _addReplyLongLong(c,len,'$');
+    addReplyLongLongWithPrefix(c,len,'$');
 }
 
 /* Add a Redis Object as a bulk reply */
@@ -390,7 +414,7 @@ void addReplyBulk(redisClient *c, robj *obj) {
 
 /* Add a C buffer as bulk reply */
 void addReplyBulkCBuffer(redisClient *c, void *p, size_t len) {
-    _addReplyLongLong(c,len,'$');
+    addReplyLongLongWithPrefix(c,len,'$');
     addReplyString(c,p,len);
     addReply(c,shared.crlf);
 }