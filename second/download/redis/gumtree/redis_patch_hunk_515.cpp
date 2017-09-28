 
 /* -----------------------------------------------------------------------------
  * Higher level functions to queue data on the client output buffer.
  * The following functions are the ones that commands implementations will call.
  * -------------------------------------------------------------------------- */
 
-void addReply(redisClient *c, robj *obj) {
-    if (prepareClientToWrite(c) != REDIS_OK) return;
+void addReply(client *c, robj *obj) {
+    if (prepareClientToWrite(c) != C_OK) return;
 
     /* This is an important place where we can avoid copy-on-write
      * when there is a saving child running, avoiding touching the
      * refcount field of the object if it's not needed.
      *
      * If the encoding is RAW and there is room in the static buffer
      * we'll be able to send the object to the client without
      * messing with its page. */
     if (sdsEncodedObject(obj)) {
-        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != C_OK)
             _addReplyObjectToList(c,obj);
-    } else if (obj->encoding == REDIS_ENCODING_INT) {
+    } else if (obj->encoding == OBJ_ENCODING_INT) {
         /* Optimization: if there is room in the static buffer for 32 bytes
          * (more than the max chars a 64 bit integer can take as string) we
          * avoid decoding the object and go for the lower level approach. */
         if (listLength(c->reply) == 0 && (sizeof(c->buf) - c->bufpos) >= 32) {
             char buf[32];
             int len;
 
             len = ll2string(buf,sizeof(buf),(long)obj->ptr);
-            if (_addReplyToBuffer(c,buf,len) == REDIS_OK)
+            if (_addReplyToBuffer(c,buf,len) == C_OK)
                 return;
             /* else... continue with the normal code path, but should never
              * happen actually since we verified there is room. */
         }
         obj = getDecodedObject(obj);
-        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != C_OK)
             _addReplyObjectToList(c,obj);
         decrRefCount(obj);
     } else {
-        redisPanic("Wrong obj->encoding in addReply()");
+        serverPanic("Wrong obj->encoding in addReply()");
     }
 }
 
-void addReplySds(redisClient *c, sds s) {
-    if (prepareClientToWrite(c) != REDIS_OK) {
+void addReplySds(client *c, sds s) {
+    if (prepareClientToWrite(c) != C_OK) {
         /* The caller expects the sds to be free'd. */
         sdsfree(s);
         return;
     }
-    if (_addReplyToBuffer(c,s,sdslen(s)) == REDIS_OK) {
+    if (_addReplyToBuffer(c,s,sdslen(s)) == C_OK) {
         sdsfree(s);
     } else {
         /* This method free's the sds when it is no longer needed. */
         _addReplySdsToList(c,s);
     }
 }
 
-void addReplyString(redisClient *c, char *s, size_t len) {
-    if (prepareClientToWrite(c) != REDIS_OK) return;
-    if (_addReplyToBuffer(c,s,len) != REDIS_OK)
+void addReplyString(client *c, const char *s, size_t len) {
+    if (prepareClientToWrite(c) != C_OK) return;
+    if (_addReplyToBuffer(c,s,len) != C_OK)
         _addReplyStringToList(c,s,len);
 }
 
-void addReplyErrorLength(redisClient *c, char *s, size_t len) {
+void addReplyErrorLength(client *c, const char *s, size_t len) {
     addReplyString(c,"-ERR ",5);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyError(redisClient *c, char *err) {
+void addReplyError(client *c, const char *err) {
     addReplyErrorLength(c,err,strlen(err));
 }
 
-void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
+void addReplyErrorFormat(client *c, const char *fmt, ...) {
     size_t l, j;
     va_list ap;
     va_start(ap,fmt);
     sds s = sdscatvprintf(sdsempty(),fmt,ap);
     va_end(ap);
     /* Make sure there are no newlines in the string, otherwise invalid protocol
