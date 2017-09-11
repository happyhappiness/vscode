@@ -132,14 +132,14 @@ client *createClient(int fd) {
  * to the client. The behavior is the following:
  *
  * If the client should receive new data (normal clients will) the function
- * returns REDIS_OK, and make sure to install the write handler in our event
+ * returns C_OK, and make sure to install the write handler in our event
  * loop so that when the socket is writable new data gets written.
  *
  * If the client should not receive new data, because it is a fake client
  * (used to load AOF in memory), a master or because the setup of the write
- * handler failed, the function returns REDIS_ERR.
+ * handler failed, the function returns C_ERR.
  *
- * The function may return REDIS_OK without actually installing the write
+ * The function may return C_OK without actually installing the write
  * event handler in the following cases:
  *
  * 1) The event handler should already be installed since the output buffer
@@ -148,19 +148,19 @@ client *createClient(int fd) {
  *    writes in the buffer but not actually sending them yet.
  *
  * Typically gets called every time a reply is built, before adding more
- * data to the clients output buffers. If the function returns REDIS_ERR no
+ * data to the clients output buffers. If the function returns C_ERR no
  * data should be appended to the output buffers. */
 int prepareClientToWrite(client *c) {
     /* If it's the Lua client we always return ok without installing any
      * handler since there is no socket at all. */
-    if (c->flags & REDIS_LUA_CLIENT) return REDIS_OK;
+    if (c->flags & REDIS_LUA_CLIENT) return C_OK;
 
     /* Masters don't receive replies, unless REDIS_MASTER_FORCE_REPLY flag
      * is set. */
     if ((c->flags & REDIS_MASTER) &&
-        !(c->flags & REDIS_MASTER_FORCE_REPLY)) return REDIS_ERR;
+        !(c->flags & REDIS_MASTER_FORCE_REPLY)) return C_ERR;
 
-    if (c->fd <= 0) return REDIS_ERR; /* Fake client for AOF loading. */
+    if (c->fd <= 0) return C_ERR; /* Fake client for AOF loading. */
 
     /* Only install the handler if not already installed and, in case of
      * slaves, if the client can actually receive writes. */
@@ -173,12 +173,12 @@ int prepareClientToWrite(client *c) {
                 sendReplyToClient, c) == AE_ERR)
         {
             freeClientAsync(c);
-            return REDIS_ERR;
+            return C_ERR;
         }
     }
 
     /* Authorize the caller to queue in the output buffer of this client. */
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Create a duplicate of the last object in the reply list when
@@ -204,18 +204,18 @@ robj *dupLastObjectIfNeeded(list *reply) {
 int _addReplyToBuffer(client *c, const char *s, size_t len) {
     size_t available = sizeof(c->buf)-c->bufpos;
 
-    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return REDIS_OK;
+    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return C_OK;
 
     /* If there already are entries in the reply list, we cannot
      * add anything more to the static buffer. */
-    if (listLength(c->reply) > 0) return REDIS_ERR;
+    if (listLength(c->reply) > 0) return C_ERR;
 
     /* Check that the buffer has enough space available for this string. */
-    if (len > available) return REDIS_ERR;
+    if (len > available) return C_ERR;
 
     memcpy(c->buf+c->bufpos,s,len);
     c->bufpos+=len;
-    return REDIS_OK;
+    return C_OK;
 }
 
 void _addReplyObjectToList(client *c, robj *o) {
@@ -318,7 +318,7 @@ void _addReplyStringToList(client *c, const char *s, size_t len) {
  * -------------------------------------------------------------------------- */
 
 void addReply(client *c, robj *obj) {
-    if (prepareClientToWrite(c) != REDIS_OK) return;
+    if (prepareClientToWrite(c) != C_OK) return;
 
     /* This is an important place where we can avoid copy-on-write
      * when there is a saving child running, avoiding touching the
@@ -328,7 +328,7 @@ void addReply(client *c, robj *obj) {
      * we'll be able to send the object to the client without
      * messing with its page. */
     if (sdsEncodedObject(obj)) {
-        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != REDIS_OK)
+        if (_addReplyToBuffer(c,obj->ptr,sdslen(obj->ptr)) != C_OK)
             _addReplyObjectToList(c,obj);
     } else if (obj->encoding == OBJ_ENCODING_INT) {
         /* Optimization: if there is room in the static buffer for 32 bytes
@@ -339,13 +339,13 @@ void addReply(client *c, robj *obj) {
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
@@ -354,12 +354,12 @@ void addReply(client *c, robj *obj) {
 }
 
 void addReplySds(client *c, sds s) {
-    if (prepareClientToWrite(c) != REDIS_OK) {
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
@@ -368,8 +368,8 @@ void addReplySds(client *c, sds s) {
 }
 
 void addReplyString(client *c, const char *s, size_t len) {
-    if (prepareClientToWrite(c) != REDIS_OK) return;
-    if (_addReplyToBuffer(c,s,len) != REDIS_OK)
+    if (prepareClientToWrite(c) != C_OK) return;
+    if (_addReplyToBuffer(c,s,len) != C_OK)
         _addReplyStringToList(c,s,len);
 }
 
@@ -424,7 +424,7 @@ void *addDeferredMultiBulkLength(client *c) {
     /* Note that we install the write event here even if the object is not
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
-    if (prepareClientToWrite(c) != REDIS_OK) return NULL;
+    if (prepareClientToWrite(c) != C_OK) return NULL;
     listAddNodeTail(c->reply,createObject(OBJ_STRING,NULL));
     return listLast(c->reply);
 }
@@ -934,7 +934,7 @@ int processInlineBuffer(client *c) {
             addReplyError(c,"Protocol error: too big inline request");
             setProtocolError(c,0);
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Handle the \r\n case. */
@@ -949,7 +949,7 @@ int processInlineBuffer(client *c) {
     if (argv == NULL) {
         addReplyError(c,"Protocol error: unbalanced quotes in request");
         setProtocolError(c,0);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Newline from slaves can be used to refresh the last ACK time.
@@ -977,7 +977,7 @@ int processInlineBuffer(client *c) {
         }
     }
     zfree(argv);
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Helper function. Trims query buffer to make the function that processes
@@ -1009,12 +1009,12 @@ int processMultibulkBuffer(client *c) {
                 addReplyError(c,"Protocol error: too big mbulk count string");
                 setProtocolError(c,0);
             }
-            return REDIS_ERR;
+            return C_ERR;
         }
 
         /* Buffer should also contain \n */
         if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
-            return REDIS_ERR;
+            return C_ERR;
 
         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
@@ -1023,13 +1023,13 @@ int processMultibulkBuffer(client *c) {
         if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
             setProtocolError(c,pos);
-            return REDIS_ERR;
+            return C_ERR;
         }
 
         pos = (newline-c->querybuf)+2;
         if (ll <= 0) {
             sdsrange(c->querybuf,pos,-1);
-            return REDIS_OK;
+            return C_OK;
         }
 
         c->multibulklen = ll;
@@ -1049,7 +1049,7 @@ int processMultibulkBuffer(client *c) {
                     addReplyError(c,
                         "Protocol error: too big bulk count string");
                     setProtocolError(c,0);
-                    return REDIS_ERR;
+                    return C_ERR;
                 }
                 break;
             }
@@ -1063,14 +1063,14 @@ int processMultibulkBuffer(client *c) {
                     "Protocol error: expected '$', got '%c'",
                     c->querybuf[pos]);
                 setProtocolError(c,pos);
-                return REDIS_ERR;
+                return C_ERR;
             }
 
             ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
             if (!ok || ll < 0 || ll > 512*1024*1024) {
                 addReplyError(c,"Protocol error: invalid bulk length");
                 setProtocolError(c,pos);
-                return REDIS_ERR;
+                return C_ERR;
             }
 
             pos += newline-(c->querybuf+pos)+2;
@@ -1125,10 +1125,10 @@ int processMultibulkBuffer(client *c) {
     if (pos) sdsrange(c->querybuf,pos,-1);
 
     /* We're done when c->multibulk == 0 */
-    if (c->multibulklen == 0) return REDIS_OK;
+    if (c->multibulklen == 0) return C_OK;
 
     /* Still not read to process the command */
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 void processInputBuffer(client *c) {
@@ -1156,9 +1156,9 @@ void processInputBuffer(client *c) {
         }
 
         if (c->reqtype == REDIS_REQ_INLINE) {
-            if (processInlineBuffer(c) != REDIS_OK) break;
+            if (processInlineBuffer(c) != C_OK) break;
         } else if (c->reqtype == REDIS_REQ_MULTIBULK) {
-            if (processMultibulkBuffer(c) != REDIS_OK) break;
+            if (processMultibulkBuffer(c) != C_OK) break;
         } else {
             redisPanic("Unknown request type");
         }
@@ -1168,7 +1168,7 @@ void processInputBuffer(client *c) {
             resetClient(c);
         } else {
             /* Only reset the client when the command was executed. */
-            if (processCommand(c) == REDIS_OK)
+            if (processCommand(c) == C_OK)
                 resetClient(c);
         }
     }
@@ -1388,7 +1388,7 @@ void clientCommand(client *c) {
                     long long tmp;
 
                     if (getLongLongFromObjectOrReply(c,c->argv[i+1],&tmp,NULL)
-                        != REDIS_OK) return;
+                        != C_OK) return;
                     id = tmp;
                 } else if (!strcasecmp(c->argv[i]->ptr,"type") && moreargs) {
                     type = getClientTypeByName(c->argv[i+1]->ptr);
@@ -1489,7 +1489,7 @@ void clientCommand(client *c) {
         long long duration;
 
         if (getTimeoutFromObjectOrReply(c,c->argv[2],&duration,UNIT_MILLISECONDS)
-                                        != REDIS_OK) return;
+                                        != C_OK) return;
         pauseClients(duration);
         addReply(c,shared.ok);
     } else {