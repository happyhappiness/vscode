@@ -271,14 +271,17 @@ static int processLineItem(redisReader *r) {
     int len;
 
     if ((p = readLine(r,&len)) != NULL) {
-        if (r->fn) {
-            if (cur->type == REDIS_REPLY_INTEGER) {
+        if (cur->type == REDIS_REPLY_INTEGER) {
+            if (r->fn && r->fn->createInteger)
                 obj = r->fn->createInteger(cur,readLongLong(p));
-            } else {
-                obj = r->fn->createString(cur,p,len);
-            }
+            else
+                obj = (void*)REDIS_REPLY_INTEGER;
         } else {
-            obj = (void*)(size_t)(cur->type);
+            /* Type will be error or status. */
+            if (r->fn && r->fn->createString)
+                obj = r->fn->createString(cur,p,len);
+            else
+                obj = (void*)(size_t)(cur->type);
         }
 
         /* Set reply if this is the root object. */
@@ -306,15 +309,19 @@ static int processBulkItem(redisReader *r) {
 
         if (len < 0) {
             /* The nil object can always be created. */
-            obj = r->fn ? r->fn->createNil(cur) :
-                (void*)REDIS_REPLY_NIL;
+            if (r->fn && r->fn->createNil)
+                obj = r->fn->createNil(cur);
+            else
+                obj = (void*)REDIS_REPLY_NIL;
             success = 1;
         } else {
             /* Only continue when the buffer contains the entire bulk item. */
             bytelen += len+2; /* include \r\n */
             if (r->pos+bytelen <= r->len) {
-                obj = r->fn ? r->fn->createString(cur,s+2,len) :
-                    (void*)REDIS_REPLY_STRING;
+                if (r->fn && r->fn->createString)
+                    obj = r->fn->createString(cur,s+2,len);
+                else
+                    obj = (void*)REDIS_REPLY_STRING;
                 success = 1;
             }
         }
@@ -351,12 +358,16 @@ static int processMultiBulkItem(redisReader *r) {
         root = (r->ridx == 0);
 
         if (elements == -1) {
-            obj = r->fn ? r->fn->createNil(cur) :
-                (void*)REDIS_REPLY_NIL;
+            if (r->fn && r->fn->createNil)
+                obj = r->fn->createNil(cur);
+            else
+                obj = (void*)REDIS_REPLY_NIL;
             moveToNextTask(r);
         } else {
-            obj = r->fn ? r->fn->createArray(cur,elements) :
-                (void*)REDIS_REPLY_ARRAY;
+            if (r->fn && r->fn->createArray)
+                obj = r->fn->createArray(cur,elements);
+            else
+                obj = (void*)REDIS_REPLY_ARRAY;
 
             /* Modify task stack when there are more than 0 elements. */
             if (elements > 0) {
@@ -434,7 +445,7 @@ static int processItem(redisReader *r) {
     }
 }
 
-void *redisReplyReaderCreate() {
+void *redisReplyReaderCreate(void) {
     redisReader *r = calloc(sizeof(redisReader),1);
     r->error = NULL;
     r->fn = &defaultFunctions;
@@ -493,7 +504,7 @@ static void redisSetReplyReaderError(redisReader *r, sds err) {
     if (r->buf != NULL) {
         sdsfree(r->buf);
         r->buf = sdsempty();
-        r->pos = 0;
+        r->pos = r->len = 0;
     }
     r->ridx = -1;
     r->error = err;
@@ -504,11 +515,18 @@ char *redisReplyReaderGetError(void *reader) {
     return r->error;
 }
 
-void redisReplyReaderFeed(void *reader, char *buf, size_t len) {
+void redisReplyReaderFeed(void *reader, const char *buf, size_t len) {
     redisReader *r = reader;
 
     /* Copy the provided buffer. */
     if (buf != NULL && len >= 1) {
+        /* Destroy internal buffer when it is empty and is quite large. */
+        if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
+            sdsfree(r->buf);
+            r->buf = sdsempty();
+            r->pos = 0;
+        }
+
         r->buf = sdscatlen(r->buf,buf,len);
         r->len = sdslen(r->buf);
     }
@@ -538,15 +556,10 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
         if (processItem(r) < 0)
             break;
 
-    /* Discard the consumed part of the buffer. */
-    if (r->pos > 0) {
-        if (r->pos == r->len) {
-            /* sdsrange has a quirck on this edge case. */
-            sdsfree(r->buf);
-            r->buf = sdsempty();
-        } else {
-            r->buf = sdsrange(r->buf,r->pos,r->len);
-        }
+    /* Discard part of the buffer when we've consumed at least 1k, to avoid
+     * doing unnecessary calls to memmove() in sds.c. */
+    if (r->pos >= 1024) {
+        r->buf = sdsrange(r->buf,r->pos,-1);
         r->pos = 0;
         r->len = sdslen(r->buf);
     }
@@ -556,13 +569,6 @@ int redisReplyReaderGetReply(void *reader, void **reply) {
         void *aux = r->reply;
         r->reply = NULL;
 
-        /* Destroy the buffer when it is empty and is quite large. */
-        if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
-            sdsfree(r->buf);
-            r->buf = sdsempty();
-            r->pos = 0;
-        }
-
         /* Check if there actually *is* a reply. */
         if (r->error != NULL) {
             return REDIS_ERR;
@@ -601,7 +607,7 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     char *cmd = NULL; /* final command */
     int pos; /* position in final command */
     sds current; /* current argument */
-    int interpolated = 0; /* did we do interpolation on an argument? */
+    int touched = 0; /* was the current argument touched? */
     char **argv = NULL;
     int argc = 0, j;
     int totlen = 0;
@@ -615,13 +621,14 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
     while(*c != '\0') {
         if (*c != '%' || c[1] == '\0') {
             if (*c == ' ') {
-                if (sdslen(current) != 0) {
+                if (touched) {
                     addArgument(current, &argv, &argc, &totlen);
                     current = sdsempty();
-                    interpolated = 0;
+                    touched = 0;
                 }
             } else {
                 current = sdscatlen(current,c,1);
+                touched = 1;
             }
         } else {
             switch(c[1]) {
@@ -630,14 +637,12 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                 size = strlen(arg);
                 if (size > 0)
                     current = sdscatlen(current,arg,size);
-                interpolated = 1;
                 break;
             case 'b':
                 arg = va_arg(ap,char*);
                 size = va_arg(ap,size_t);
                 if (size > 0)
                     current = sdscatlen(current,arg,size);
-                interpolated = 1;
                 break;
             case '%':
                 current = sdscat(current,"%");
@@ -683,7 +688,6 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                             _format[_l] = '\0';
                             va_copy(_cpy,ap);
                             current = sdscatvprintf(current,_format,_cpy);
-                            interpolated = 1;
                             va_end(_cpy);
 
                             /* Update current position (note: outer blocks
@@ -696,13 +700,14 @@ int redisvFormatCommand(char **target, const char *format, va_list ap) {
                     va_arg(ap,void);
                 }
             }
+            touched = 1;
             c++;
         }
         c++;
     }
 
     /* Add the last argument if needed */
-    if (interpolated || sdslen(current) != 0) {
+    if (touched) {
         addArgument(current, &argv, &argc, &totlen);
     } else {
         sdsfree(current);
@@ -798,7 +803,7 @@ void __redisSetError(redisContext *c, int type, const sds errstr) {
     }
 }
 
-static redisContext *redisContextInit() {
+static redisContext *redisContextInit(void) {
     redisContext *c = calloc(sizeof(redisContext),1);
     c->err = 0;
     c->errstr = NULL;
@@ -809,8 +814,7 @@ static redisContext *redisContextInit() {
 }
 
 void redisFree(redisContext *c) {
-    /* Disconnect before free'ing if not yet disconnected. */
-    if (c->flags & REDIS_CONNECTED)
+    if (c->fd > 0)
         close(c->fd);
     if (c->errstr != NULL)
         sdsfree(c->errstr);
@@ -827,31 +831,52 @@ void redisFree(redisContext *c) {
 redisContext *redisConnect(const char *ip, int port) {
     redisContext *c = redisContextInit();
     c->flags |= REDIS_BLOCK;
-    redisContextConnectTcp(c,ip,port);
+    redisContextConnectTcp(c,ip,port,NULL);
+    return c;
+}
+
+redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv) {
+    redisContext *c = redisContextInit();
+    c->flags |= REDIS_BLOCK;
+    redisContextConnectTcp(c,ip,port,&tv);
     return c;
 }
 
 redisContext *redisConnectNonBlock(const char *ip, int port) {
     redisContext *c = redisContextInit();
     c->flags &= ~REDIS_BLOCK;
-    redisContextConnectTcp(c,ip,port);
+    redisContextConnectTcp(c,ip,port,NULL);
     return c;
 }
 
 redisContext *redisConnectUnix(const char *path) {
     redisContext *c = redisContextInit();
     c->flags |= REDIS_BLOCK;
-    redisContextConnectUnix(c,path);
+    redisContextConnectUnix(c,path,NULL);
+    return c;
+}
+
+redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv) {
+    redisContext *c = redisContextInit();
+    c->flags |= REDIS_BLOCK;
+    redisContextConnectUnix(c,path,&tv);
     return c;
 }
 
 redisContext *redisConnectUnixNonBlock(const char *path) {
     redisContext *c = redisContextInit();
     c->flags &= ~REDIS_BLOCK;
-    redisContextConnectUnix(c,path);
+    redisContextConnectUnix(c,path,NULL);
     return c;
 }
 
+/* Set read/write timeout on a blocking socket. */
+int redisSetTimeout(redisContext *c, struct timeval tv) {
+    if (c->flags & REDIS_BLOCK)
+        return redisContextSetTimeout(c,tv);
+    return REDIS_ERR;
+}
+
 /* Set the replyObjectFunctions to use. Returns REDIS_ERR when the reader
  * was already initialized and the function set could not be re-set.
  * Return REDIS_OK when they could be set. */
@@ -879,7 +904,7 @@ int redisBufferRead(redisContext *c) {
     char buf[2048];
     int nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
-        if (errno == EAGAIN) {
+        if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
             /* Try again later */
         } else {
             __redisSetError(c,REDIS_ERR_IO,NULL);
@@ -910,7 +935,7 @@ int redisBufferWrite(redisContext *c, int *done) {
     if (sdslen(c->obuf) > 0) {
         nwritten = write(c->fd,c->obuf,sdslen(c->obuf));
         if (nwritten == -1) {
-            if (errno == EAGAIN) {
+            if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
                 /* Try again later */
             } else {
                 __redisSetError(c,REDIS_ERR_IO,NULL);