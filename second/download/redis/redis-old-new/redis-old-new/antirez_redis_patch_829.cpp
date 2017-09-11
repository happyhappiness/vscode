@@ -917,7 +917,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
  * %b represents a binary safe string
  *
  * When using %b you need to provide both the pointer to the string
- * and the length in bytes. Examples:
+ * and the length in bytes as a size_t. Examples:
  *
  * len = redisFormatCommand(target, "GET %s", mykey);
  * len = redisFormatCommand(target, "SET %s %b", mykey, myval, myvallen);
@@ -1010,58 +1010,122 @@ void redisFree(redisContext *c) {
     free(c);
 }
 
+int redisFreeKeepFd(redisContext *c) {
+	int fd = c->fd;
+	c->fd = -1;
+	redisFree(c);
+	return fd;
+}
+
 /* Connect to a Redis instance. On error the field error in the returned
  * context will be set to the return value of the error function.
  * When no set of reply functions is given, the default set will be used. */
 redisContext *redisConnect(const char *ip, int port) {
-    redisContext *c = redisContextInit();
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags |= REDIS_BLOCK;
     redisContextConnectTcp(c,ip,port,NULL);
     return c;
 }
 
-redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv) {
-    redisContext *c = redisContextInit();
+redisContext *redisConnectWithTimeout(const char *ip, int port, const struct timeval tv) {
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags |= REDIS_BLOCK;
     redisContextConnectTcp(c,ip,port,&tv);
     return c;
 }
 
 redisContext *redisConnectNonBlock(const char *ip, int port) {
-    redisContext *c = redisContextInit();
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags &= ~REDIS_BLOCK;
     redisContextConnectTcp(c,ip,port,NULL);
     return c;
 }
 
-redisContext *redisConnectUnix(const char *path) {
+redisContext *redisConnectBindNonBlock(const char *ip, int port,
+                                       const char *source_addr) {
     redisContext *c = redisContextInit();
+    c->flags &= ~REDIS_BLOCK;
+    redisContextConnectBindTcp(c,ip,port,NULL,source_addr);
+    return c;
+}
+
+redisContext *redisConnectUnix(const char *path) {
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags |= REDIS_BLOCK;
     redisContextConnectUnix(c,path,NULL);
     return c;
 }
 
-redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv) {
-    redisContext *c = redisContextInit();
+redisContext *redisConnectUnixWithTimeout(const char *path, const struct timeval tv) {
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags |= REDIS_BLOCK;
     redisContextConnectUnix(c,path,&tv);
     return c;
 }
 
 redisContext *redisConnectUnixNonBlock(const char *path) {
-    redisContext *c = redisContextInit();
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
     c->flags &= ~REDIS_BLOCK;
     redisContextConnectUnix(c,path,NULL);
     return c;
 }
 
+redisContext *redisConnectFd(int fd) {
+    redisContext *c;
+
+    c = redisContextInit();
+    if (c == NULL)
+        return NULL;
+
+    c->fd = fd;
+    c->flags |= REDIS_BLOCK | REDIS_CONNECTED;
+    return c;
+}
+
 /* Set read/write timeout on a blocking socket. */
-int redisSetTimeout(redisContext *c, struct timeval tv) {
+int redisSetTimeout(redisContext *c, const struct timeval tv) {
     if (c->flags & REDIS_BLOCK)
         return redisContextSetTimeout(c,tv);
     return REDIS_ERR;
 }
 
+/* Enable connection KeepAlive. */
+int redisEnableKeepAlive(redisContext *c) {
+    if (redisKeepAlive(c, REDIS_KEEPALIVE_INTERVAL) != REDIS_OK)
+        return REDIS_ERR;
+    return REDIS_OK;
+}
+
 /* Use this function to handle a read event on the descriptor. It will try
  * and read some bytes from the socket and feed them to the reply parser.
  *
@@ -1077,7 +1141,7 @@ int redisBufferRead(redisContext *c) {
 
     nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
-        if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
+        if ((errno == EAGAIN && !(c->flags & REDIS_BLOCK)) || (errno == EINTR)) {
             /* Try again later */
         } else {
             __redisSetError(c,REDIS_ERR_IO,NULL);
@@ -1114,7 +1178,7 @@ int redisBufferWrite(redisContext *c, int *done) {
     if (sdslen(c->obuf) > 0) {
         nwritten = write(c->fd,c->obuf,sdslen(c->obuf));
         if (nwritten == -1) {
-            if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
+            if ((errno == EAGAIN && !(c->flags & REDIS_BLOCK)) || (errno == EINTR)) {
                 /* Try again later */
             } else {
                 __redisSetError(c,REDIS_ERR_IO,NULL);
@@ -1180,7 +1244,7 @@ int redisGetReply(redisContext *c, void **reply) {
  * is used, you need to call redisGetReply yourself to retrieve
  * the reply (or replies in pub/sub).
  */
-int __redisAppendCommand(redisContext *c, char *cmd, size_t len) {
+int __redisAppendCommand(redisContext *c, const char *cmd, size_t len) {
     sds newbuf;
 
     newbuf = sdscatlen(c->obuf,cmd,len);
@@ -1193,6 +1257,15 @@ int __redisAppendCommand(redisContext *c, char *cmd, size_t len) {
     return REDIS_OK;
 }
 
+int redisAppendFormattedCommand(redisContext *c, const char *cmd, size_t len) {
+
+    if (__redisAppendCommand(c, cmd, len) != REDIS_OK) {
+        return REDIS_ERR;
+    }
+
+    return REDIS_OK;
+}
+
 int redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
     char *cmd;
     int len;