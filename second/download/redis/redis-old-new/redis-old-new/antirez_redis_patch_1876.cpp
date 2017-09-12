@@ -28,13 +28,11 @@ redisClient *createClient(int fd) {
     selectDb(c,0);
     c->fd = fd;
     c->querybuf = sdsempty();
-    c->newline = NULL;
+    c->reqtype = 0;
     c->argc = 0;
     c->argv = NULL;
+    c->multibulklen = 0;
     c->bulklen = -1;
-    c->multibulk = 0;
-    c->mbargc = 0;
-    c->mbargv = NULL;
     c->sentlen = 0;
     c->flags = 0;
     c->lastinteraction = time(NULL);
@@ -57,7 +55,12 @@ redisClient *createClient(int fd) {
     return c;
 }
 
+/* Set the event loop to listen for write events on the client's socket.
+ * Typically gets called every time a reply is built. */
 int _installWriteEvent(redisClient *c) {
+    /* When CLOSE_AFTER_REPLY is set, no more replies may be added! */
+    redisAssert(!(c->flags & REDIS_CLOSE_AFTER_REPLY));
+
     if (c->fd <= 0) return REDIS_ERR;
     if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
@@ -374,13 +377,9 @@ void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
 static void freeClientArgv(redisClient *c) {
     int j;
-
     for (j = 0; j < c->argc; j++)
         decrRefCount(c->argv[j]);
-    for (j = 0; j < c->mbargc; j++)
-        decrRefCount(c->mbargv[j]);
     c->argc = 0;
-    c->mbargc = 0;
 }
 
 void freeClient(redisClient *c) {
@@ -461,7 +460,6 @@ void freeClient(redisClient *c) {
     }
     /* Release memory */
     zfree(c->argv);
-    zfree(c->mbargv);
     freeClientMultiState(c);
     zfree(c);
 }
@@ -546,6 +544,9 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (listLength(c->reply) == 0) {
         c->sentlen = 0;
         aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
+
+        /* Close connection after entire reply has been sent. */
+        if (c->flags & REDIS_CLOSE_AFTER_REPLY) freeClient(c);
     }
 }
 
@@ -630,9 +631,9 @@ void sendReplyToClientWritev(aeEventLoop *el, int fd, void *privdata, int mask)
 /* resetClient prepare the client to process the next command */
 void resetClient(redisClient *c) {
     freeClientArgv(c);
+    c->reqtype = 0;
+    c->multibulklen = 0;
     c->bulklen = -1;
-    c->multibulk = 0;
-    c->newline = NULL;
 }
 
 void closeTimedoutClients(void) {
@@ -663,90 +664,172 @@ void closeTimedoutClients(void) {
     }
 }
 
-void processInputBuffer(redisClient *c) {
-    int seeknewline = 0;
-
-again:
-    /* Before to process the input buffer, make sure the client is not
-     * waitig for a blocking operation such as BLPOP. Note that the first
-     * iteration the client is never blocked, otherwise the processInputBuffer
-     * would not be called at all, but after the execution of the first commands
-     * in the input buffer the client may be blocked, and the "goto again"
-     * will try to reiterate. The following line will make it return asap. */
-    if (c->flags & REDIS_BLOCKED || c->flags & REDIS_IO_WAIT) return;
-
-    if (seeknewline && c->bulklen == -1) c->newline = strchr(c->querybuf,'\n');
-    seeknewline = 1;
-    if (c->bulklen == -1) {
-        /* Read the first line of the query */
-        size_t querylen;
-
-        if (c->newline) {
-            char *p = c->newline;
-            sds query, *argv;
-            int argc, j;
-
-            c->newline = NULL;
-            query = c->querybuf;
-            c->querybuf = sdsempty();
-            querylen = 1+(p-(query));
-            if (sdslen(query) > querylen) {
-                /* leave data after the first line of the query in the buffer */
-                c->querybuf = sdscatlen(c->querybuf,query+querylen,sdslen(query)-querylen);
-            }
-            *p = '\0'; /* remove "\n" */
-            if (*(p-1) == '\r') *(p-1) = '\0'; /* and "\r" if any */
-            sdsupdatelen(query);
-
-            /* Now we can split the query in arguments */
-            argv = sdssplitlen(query,sdslen(query)," ",1,&argc);
-            sdsfree(query);
-
-            if (c->argv) zfree(c->argv);
-            c->argv = zmalloc(sizeof(robj*)*argc);
-
-            for (j = 0; j < argc; j++) {
-                if (sdslen(argv[j])) {
-                    c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
-                    c->argc++;
-                } else {
-                    sdsfree(argv[j]);
+int processInlineBuffer(redisClient *c) {
+    char *newline = strstr(c->querybuf,"\r\n");
+    int argc, j;
+    sds *argv;
+    size_t querylen;
+
+    /* Nothing to do without a \r\n */
+    if (newline == NULL)
+        return REDIS_ERR;
+
+    /* Split the input buffer up to the \r\n */
+    querylen = newline-(c->querybuf);
+    argv = sdssplitlen(c->querybuf,querylen," ",1,&argc);
+
+    /* Leave data after the first line of the query in the buffer */
+    c->querybuf = sdsrange(c->querybuf,querylen+2,-1);
+
+    /* Setup argv array on client structure */
+    if (c->argv) zfree(c->argv);
+    c->argv = zmalloc(sizeof(robj*)*argc);
+
+    /* Create redis objects for all arguments. */
+    for (c->argc = 0, j = 0; j < argc; j++) {
+        if (sdslen(argv[j])) {
+            c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
+            c->argc++;
+        } else {
+            sdsfree(argv[j]);
+        }
+    }
+    zfree(argv);
+    return REDIS_OK;
+}
+
+/* Helper function. Trims query buffer to make the function that processes
+ * multi bulk requests idempotent. */
+static void setProtocolError(redisClient *c, int pos) {
+    c->flags |= REDIS_CLOSE_AFTER_REPLY;
+    c->querybuf = sdsrange(c->querybuf,pos,-1);
+}
+
+int processMultibulkBuffer(redisClient *c) {
+    char *newline = NULL;
+    char *eptr;
+    int pos = 0, tolerr;
+    long bulklen;
+
+    if (c->multibulklen == 0) {
+        /* The client should have been reset */
+        redisAssert(c->argc == 0);
+
+        /* Multi bulk length cannot be read without a \r\n */
+        newline = strstr(c->querybuf,"\r\n");
+        if (newline == NULL)
+            return REDIS_ERR;
+
+        /* We know for sure there is a whole line since newline != NULL,
+         * so go ahead and find out the multi bulk length. */
+        redisAssert(c->querybuf[0] == '*');
+        c->multibulklen = strtol(c->querybuf+1,&eptr,10);
+        pos = (newline-c->querybuf)+2;
+        if (c->multibulklen <= 0) {
+            c->querybuf = sdsrange(c->querybuf,pos,-1);
+            return REDIS_OK;
+        } else if (c->multibulklen > 1024*1024) {
+            addReplyError(c,"Protocol error: invalid multibulk length");
+            setProtocolError(c,pos);
+            return REDIS_ERR;
+        }
+
+        /* Setup argv array on client structure */
+        if (c->argv) zfree(c->argv);
+        c->argv = zmalloc(sizeof(robj*)*c->multibulklen);
+
+        /* Search new newline */
+        newline = strstr(c->querybuf+pos,"\r\n");
+    }
+
+    redisAssert(c->multibulklen > 0);
+    while(c->multibulklen) {
+        /* Read bulk length if unknown */
+        if (c->bulklen == -1) {
+            newline = strstr(c->querybuf+pos,"\r\n");
+            if (newline != NULL) {
+                if (c->querybuf[pos] != '$') {
+                    addReplyErrorFormat(c,
+                        "Protocol error: expected '$', got '%c'",
+                        c->querybuf[pos]);
+                    setProtocolError(c,pos);
+                    return REDIS_ERR;
                 }
+
+                bulklen = strtol(c->querybuf+pos+1,&eptr,10);
+                tolerr = (eptr[0] != '\r');
+                if (tolerr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
+                    bulklen < 0 || bulklen > 1024*1024*1024)
+                {
+                    addReplyError(c,"Protocol error: invalid bulk length");
+                    setProtocolError(c,pos);
+                    return REDIS_ERR;
+                }
+                pos += eptr-(c->querybuf+pos)+2;
+                c->bulklen = bulklen;
+            } else {
+                /* No newline in current buffer, so wait for more data */
+                break;
             }
-            zfree(argv);
-            if (c->argc) {
-                /* Execute the command. If the client is still valid
-                 * after processCommand() return and there is something
-                 * on the query buffer try to process the next command. */
-                if (processCommand(c) && sdslen(c->querybuf)) goto again;
+        }
+
+        /* Read bulk argument */
+        if (sdslen(c->querybuf)-pos < (unsigned)(c->bulklen+2)) {
+            /* Not enough data (+2 == trailing \r\n) */
+            break;
+        } else {
+            c->argv[c->argc++] = createStringObject(c->querybuf+pos,c->bulklen);
+            pos += c->bulklen+2;
+            c->bulklen = -1;
+            c->multibulklen--;
+        }
+    }
+
+    /* Trim to pos */
+    c->querybuf = sdsrange(c->querybuf,pos,-1);
+
+    /* We're done when c->multibulk == 0 */
+    if (c->multibulklen == 0) {
+        return REDIS_OK;
+    }
+    return REDIS_ERR;
+}
+
+void processInputBuffer(redisClient *c) {
+    /* Keep processing while there is something in the input buffer */
+    while(sdslen(c->querybuf)) {
+        /* Immediately abort if the client is in the middle of something. */
+        if (c->flags & REDIS_BLOCKED || c->flags & REDIS_IO_WAIT) return;
+
+        /* REDIS_CLOSE_AFTER_REPLY closes the connection once the reply is
+         * written to the client. Make sure to not let the reply grow after
+         * this flag has been set (i.e. don't process more commands). */
+        if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+
+        /* Determine request type when unknown. */
+        if (!c->reqtype) {
+            if (c->querybuf[0] == '*') {
+                c->reqtype = REDIS_REQ_MULTIBULK;
             } else {
-                /* Nothing to process, argc == 0. Just process the query
-                 * buffer if it's not empty or return to the caller */
-                if (sdslen(c->querybuf)) goto again;
+                c->reqtype = REDIS_REQ_INLINE;
             }
-            return;
-        } else if (sdslen(c->querybuf) >= REDIS_REQUEST_MAX_SIZE) {
-            redisLog(REDIS_VERBOSE, "Client protocol error");
-            freeClient(c);
-            return;
         }
-    } else {
-        /* Bulk read handling. Note that if we are at this point
-           the client already sent a command terminated with a newline,
-           we are reading the bulk data that is actually the last
-           argument of the command. */
-        int qbl = sdslen(c->querybuf);
-
-        if (c->bulklen <= qbl) {
-            /* Copy everything but the final CRLF as final argument */
-            c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
-            c->argc++;
-            c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
-            /* Process the command. If the client is still valid after
-             * the processing and there is more data in the buffer
-             * try to parse it. */
-            if (processCommand(c) && sdslen(c->querybuf)) goto again;
-            return;
+
+        if (c->reqtype == REDIS_REQ_INLINE) {
+            if (processInlineBuffer(c) != REDIS_OK) break;
+        } else if (c->reqtype == REDIS_REQ_MULTIBULK) {
+            if (processMultibulkBuffer(c) != REDIS_OK) break;
+        } else {
+            redisPanic("Unknown request type");
+        }
+
+        /* Multibulk processing could see a <= 0 length. */
+        if (c->argc == 0) {
+            resetClient(c);
+        } else {
+            /* Only reset the client when the command was executed. */
+            if (processCommand(c) == REDIS_OK)
+                resetClient(c);
         }
     }
 }
@@ -773,14 +856,8 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     if (nread) {
-        size_t oldlen = sdslen(c->querybuf);
-        c->querybuf = sdscatlen(c->querybuf, buf, nread);
+        c->querybuf = sdscatlen(c->querybuf,buf,nread);
         c->lastinteraction = time(NULL);
-        /* Scan this new piece of the query for the newline. We do this
-         * here in order to make sure we perform this scan just one time
-         * per piece of buffer, leading to an O(N) scan instead of O(N*N) */
-        if (c->bulklen == -1 && c->newline == NULL)
-            c->newline = strchr(c->querybuf+oldlen,'\n');
     } else {
         return;
     }