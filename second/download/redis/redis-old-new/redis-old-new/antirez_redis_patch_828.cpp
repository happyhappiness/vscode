@@ -62,7 +62,8 @@ void __redisAppendCommand(redisContext *c, char *cmd, size_t len);
 
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
@@ -142,15 +148,45 @@ static void __redisAsyncCopyError(redisAsyncContext *ac) {
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
 
 redisAsyncContext *redisAsyncConnectUnix(const char *path) {
-    redisContext *c = redisConnectUnixNonBlock(path);
-    redisAsyncContext *ac = redisAsyncInitialize(c);
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
     __redisAsyncCopyError(ac);
     return ac;
 }
@@ -182,6 +218,9 @@ static int __redisPushCallback(redisCallbackList *list, redisCallback *source) {
 
     /* Copy callback from stack to heap */
     cb = malloc(sizeof(*cb));
+    if (cb == NULL)
+        return REDIS_ERR_OOM;
+
     if (source != NULL) {
         memcpy(cb,source,sizeof(*cb));
         cb->next = NULL;
@@ -360,7 +399,7 @@ static int __redisGetSubscribeCallback(redisAsyncContext *ac, redisReply *reply,
 
 void redisProcessCallbacks(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
-    redisCallback cb;
+    redisCallback cb = {NULL, NULL, NULL};
     void *reply = NULL;
     int status;
 
@@ -372,7 +411,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
                 __redisAsyncDisconnect(ac);
                 return;
             }
-            
+
             /* If monitor mode, repush callback */
             if(c->flags & REDIS_MONITORING) {
                 __redisPushCallback(&ac->replies,&cb);
@@ -442,7 +481,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
 static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
 
-    if (redisCheckSocketError(c,c->fd) == REDIS_ERR) {
+    if (redisCheckSocketError(c) == REDIS_ERR) {
         /* Try again later when connect(2) is still in progress. */
         if (errno == EINPROGRESS)
             return REDIS_OK;