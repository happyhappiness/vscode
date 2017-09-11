@@ -58,7 +58,7 @@
     } while(0);
 
 /* Forward declaration of function in hiredis.c */
-void __redisAppendCommand(redisContext *c, char *cmd, size_t len);
+int __redisAppendCommand(redisContext *c, const char *cmd, size_t len);
 
 /* Functions managing dictionary of callbacks for pub/sub. */
 static unsigned int callbackHash(const void *key) {
@@ -142,6 +142,9 @@ static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
 /* We want the error field to be accessible directly instead of requiring
  * an indirection to the redisContext struct. */
 static void __redisAsyncCopyError(redisAsyncContext *ac) {
+    if (!ac)
+        return;
+
     redisContext *c = &(ac->c);
     ac->err = c->err;
     ac->errstr = c->errstr;
@@ -173,6 +176,14 @@ redisAsyncContext *redisAsyncConnectBind(const char *ip, int port,
     return ac;
 }
 
+redisAsyncContext *redisAsyncConnectBindWithReuse(const char *ip, int port,
+                                                  const char *source_addr) {
+    redisContext *c = redisConnectBindNonBlockWithReuse(ip,port,source_addr);
+    redisAsyncContext *ac = redisAsyncInitialize(c);
+    __redisAsyncCopyError(ac);
+    return ac;
+}
+
 redisAsyncContext *redisAsyncConnectUnix(const char *path) {
     redisContext *c;
     redisAsyncContext *ac;
@@ -407,7 +418,8 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
         if (reply == NULL) {
             /* When the connection is being disconnected and there are
              * no more replies, this is the cue to really disconnect. */
-            if (c->flags & REDIS_DISCONNECTING && sdslen(c->obuf) == 0) {
+            if (c->flags & REDIS_DISCONNECTING && sdslen(c->obuf) == 0
+                && ac->replies.head == NULL) {
                 __redisAsyncDisconnect(ac);
                 return;
             }
@@ -477,7 +489,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
 }
 
 /* Internal helper function to detect socket status the first time a read or
- * write event fires. When connecting was not succesful, the connect callback
+ * write event fires. When connecting was not successful, the connect callback
  * is called with a REDIS_ERR status and the context is free'd. */
 static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
@@ -551,8 +563,8 @@ void redisAsyncHandleWrite(redisAsyncContext *ac) {
 
 /* Sets a pointer to the first argument and its length starting at p. Returns
  * the number of bytes to skip to get to the following argument. */
-static char *nextArgument(char *start, char **str, size_t *len) {
-    char *p = start;
+static const char *nextArgument(const char *start, const char **str, size_t *len) {
+    const char *p = start;
     if (p[0] != '$') {
         p = strchr(p,'$');
         if (p == NULL) return NULL;
@@ -568,14 +580,15 @@ static char *nextArgument(char *start, char **str, size_t *len) {
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
@@ -599,9 +612,11 @@ static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void
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
@@ -637,6 +652,11 @@ int redisvAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdat
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
@@ -652,11 +672,16 @@ int redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata
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