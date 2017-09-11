@@ -58,11 +58,12 @@
     } while(0);
 
 /* Forward declaration of function in hiredis.c */
-void __redisAppendCommand(redisContext *c, char *cmd, size_t len);
+int __redisAppendCommand(redisContext *c, const char *cmd, size_t len);
 
 /* Functions managing dictionary of callbacks for pub/sub. */
 static unsigned int callbackHash(const void *key) {
-    return dictGenHashFunction((unsigned char*)key,sdslen((char*)key));
+    return dictGenHashFunction((const unsigned char *)key,
+                               sdslen((const sds)key));
 }
 
 static void *callbackValDup(void *privdata, const void *src) {
@@ -76,8 +77,8 @@ static int callbackKeyCompare(void *privdata, const void *key1, const void *key2
     int l1, l2;
     ((void) privdata);
 
-    l1 = sdslen((sds)key1);
-    l2 = sdslen((sds)key2);
+    l1 = sdslen((const sds)key1);
+    l2 = sdslen((const sds)key2);
     if (l1 != l2) return 0;
     return memcmp(key1,key2,l1) == 0;
 }
@@ -102,7 +103,12 @@ static dictType callbackDict = {
 };
 
 static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
-    redisAsyncContext *ac = realloc(c,sizeof(redisAsyncContext));
+    redisAsyncContext *ac;
+
+    ac = realloc(c,sizeof(redisAsyncContext));
+    if (ac == NULL)
+        return NULL;
+
     c = &(ac->c);
 
     /* The regular connect functions will always set the flag REDIS_CONNECTED.
@@ -136,25 +142,66 @@ static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
 /* We want the error field to be accessible directly instead of requiring
  * an indirection to the redisContext struct. */
 static void __redisAsyncCopyError(redisAsyncContext *ac) {
+    if (!ac)
+        return;
+
     redisContext *c = &(ac->c);
     ac->err = c->err;
     ac->errstr = c->errstr;
 }
 
 redisAsyncContext *redisAsyncConnect(const char *ip, int port) {
-    redisContext *c = redisConnectNonBlock(ip,port);
+    redisContext *c;
+    redisAsyncContext *ac;
+
+    c = redisConnectNonBlock(ip,port);
+    if (c == NULL)
+        return NULL;
+
+    ac = redisAsyncInitialize(c);
+    if (ac == NULL) {
+        redisFree(c);
+        return NULL;
+    }
+
+    __redisAsyncCopyError(ac);
+    return ac;
+}
+
+redisAsyncContext *redisAsyncConnectBind(const char *ip, int port,
+                                         const char *source_addr) {
+    redisContext *c = redisConnectBindNonBlock(ip,port,source_addr);
     redisAsyncContext *ac = redisAsyncInitialize(c);
     __redisAsyncCopyError(ac);
     return ac;
 }
 
-redisAsyncContext *redisAsyncConnectUnix(const char *path) {
-    redisContext *c = redisConnectUnixNonBlock(path);
+redisAsyncContext *redisAsyncConnectBindWithReuse(const char *ip, int port,
+                                                  const char *source_addr) {
+    redisContext *c = redisConnectBindNonBlockWithReuse(ip,port,source_addr);
     redisAsyncContext *ac = redisAsyncInitialize(c);
     __redisAsyncCopyError(ac);
     return ac;
 }
 
+redisAsyncContext *redisAsyncConnectUnix(const char *path) {
+    redisContext *c;
+    redisAsyncContext *ac;
+
+    c = redisConnectUnixNonBlock(path);
+    if (c == NULL)
+        return NULL;
+
+    ac = redisAsyncInitialize(c);
+    if (ac == NULL) {
+        redisFree(c);
+        return NULL;
+    }
+
+    __redisAsyncCopyError(ac);
+    return ac;
+}
+
 int redisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn) {
     if (ac->onConnect == NULL) {
         ac->onConnect = fn;
@@ -182,6 +229,9 @@ static int __redisPushCallback(redisCallbackList *list, redisCallback *source) {
 
     /* Copy callback from stack to heap */
     cb = malloc(sizeof(*cb));
+    if (cb == NULL)
+        return REDIS_ERR_OOM;
+
     if (source != NULL) {
         memcpy(cb,source,sizeof(*cb));
         cb->next = NULL;
@@ -360,19 +410,20 @@ static int __redisGetSubscribeCallback(redisAsyncContext *ac, redisReply *reply,
 
 void redisProcessCallbacks(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
-    redisCallback cb;
+    redisCallback cb = {NULL, NULL, NULL};
     void *reply = NULL;
     int status;
 
     while((status = redisGetReply(c,&reply)) == REDIS_OK) {
         if (reply == NULL) {
             /* When the connection is being disconnected and there are
              * no more replies, this is the cue to really disconnect. */
-            if (c->flags & REDIS_DISCONNECTING && sdslen(c->obuf) == 0) {
+            if (c->flags & REDIS_DISCONNECTING && sdslen(c->obuf) == 0
+                && ac->replies.head == NULL) {
                 __redisAsyncDisconnect(ac);
                 return;
             }
-            
+
             /* If monitor mode, repush callback */
             if(c->flags & REDIS_MONITORING) {
                 __redisPushCallback(&ac->replies,&cb);
@@ -404,6 +455,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
             if (((redisReply*)reply)->type == REDIS_REPLY_ERROR) {
                 c->err = REDIS_ERR_OTHER;
                 snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
+                c->reader->fn->freeObject(reply);
                 __redisAsyncDisconnect(ac);
                 return;
             }
@@ -437,12 +489,12 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
 }
 
 /* Internal helper function to detect socket status the first time a read or
- * write event fires. When connecting was not succesful, the connect callback
+ * write event fires. When connecting was not successful, the connect callback
  * is called with a REDIS_ERR status and the context is free'd. */
 static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
 
-    if (redisCheckSocketError(c,c->fd) == REDIS_ERR) {
+    if (redisCheckSocketError(c) == REDIS_ERR) {
         /* Try again later when connect(2) is still in progress. */
         if (errno == EINPROGRESS)
             return REDIS_OK;
@@ -511,8 +563,8 @@ void redisAsyncHandleWrite(redisAsyncContext *ac) {
 
 /* Sets a pointer to the first argument and its length starting at p. Returns
  * the number of bytes to skip to get to the following argument. */
-static char *nextArgument(char *start, char **str, size_t *len) {
-    char *p = start;
+static const char *nextArgument(const char *start, const char **str, size_t *len) {
+    const char *p = start;
     if (p[0] != '$') {
         p = strchr(p,'$');
         if (p == NULL) return NULL;
@@ -528,14 +580,15 @@ static char *nextArgument(char *start, char **str, size_t *len) {
 /* Helper function for the redisAsyncCommand* family of functions. Writes a
  * formatted command to the output buffer and registers the provided callback
  * function with the context. */
-static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, char *cmd, size_t len) {
+static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *cmd, size_t len) {
     redisContext *c = &(ac->c);
     redisCallback cb;
     int pvariant, hasnext;
-    char *cstr, *astr;
+    const char *cstr, *astr;
     size_t clen, alen;
-    char *p;
+    const char *p;
     sds sname;
+    int ret;
 
     /* Don't accept new commands when the connection is about to be closed. */
     if (c->flags & (REDIS_DISCONNECTING | REDIS_FREEING)) return REDIS_ERR;
@@ -559,9 +612,11 @@ static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void
         while ((p = nextArgument(p,&astr,&alen)) != NULL) {
             sname = sdsnewlen(astr,alen);
             if (pvariant)
-                dictReplace(ac->sub.patterns,sname,&cb);
+                ret = dictReplace(ac->sub.patterns,sname,&cb);
             else
-                dictReplace(ac->sub.channels,sname,&cb);
+                ret = dictReplace(ac->sub.channels,sname,&cb);
+
+            if (ret == 0) sdsfree(sname);
         }
     } else if (strncasecmp(cstr,"unsubscribe\r\n",13) == 0) {
         /* It is only useful to call (P)UNSUBSCRIBE when the context is
@@ -597,6 +652,11 @@ int redisvAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdat
     int len;
     int status;
     len = redisvFormatCommand(&cmd,format,ap);
+
+    /* We don't want to pass -1 or -2 to future functions as a length. */
+    if (len < 0)
+        return REDIS_ERR;
+
     status = __redisAsyncCommand(ac,fn,privdata,cmd,len);
     free(cmd);
     return status;
@@ -612,11 +672,16 @@ int redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata
 }
 
 int redisAsyncCommandArgv(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, int argc, const char **argv, const size_t *argvlen) {
-    char *cmd;
+    sds cmd;
     int len;
     int status;
-    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
+    len = redisFormatSdsCommandArgv(&cmd,argc,argv,argvlen);
     status = __redisAsyncCommand(ac,fn,privdata,cmd,len);
-    free(cmd);
+    sdsfree(cmd);
+    return status;
+}
+
+int redisAsyncFormattedCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, const char *cmd, size_t len) {
+    int status = __redisAsyncCommand(ac,fn,privdata,cmd,len);
     return status;
 }