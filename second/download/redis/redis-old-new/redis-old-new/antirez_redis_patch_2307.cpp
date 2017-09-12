@@ -344,6 +344,7 @@ static int processCommand(redisClient *c);
 static void setupSigSegvAction(void);
 static void rdbRemoveTempFile(pid_t childpid);
 static size_t stringObjectLen(robj *o);
+static void processInputBuffer(redisClient *c);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1359,6 +1360,10 @@ static int processCommand(redisClient *c) {
                 }
                 c->argc--;
                 c->bulklen = bulklen+2; /* add two bytes for CR+LF */
+                /*
+                if (sdslen(c->querybuf) > 0)
+                    processInputBuffer(c);
+                    */
                 return 1;
             }
         } else {
@@ -1389,6 +1394,10 @@ static int processCommand(redisClient *c) {
                 /* continue below and process the command */
             } else {
                 c->bulklen = -1;
+                /*
+                if (sdslen(c->querybuf) > 0)
+                    processInputBuffer(c);
+                    */
                 return 1;
             }
         }
@@ -1542,34 +1551,7 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
     if (outv != static_outv) zfree(outv);
 }
 
-static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
-    redisClient *c = (redisClient*) privdata;
-    char buf[REDIS_IOBUF_LEN];
-    int nread;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
-
-    nread = read(fd, buf, REDIS_IOBUF_LEN);
-    if (nread == -1) {
-        if (errno == EAGAIN) {
-            nread = 0;
-        } else {
-            redisLog(REDIS_DEBUG, "Reading from client: %s",strerror(errno));
-            freeClient(c);
-            return;
-        }
-    } else if (nread == 0) {
-        redisLog(REDIS_DEBUG, "Client closed connection");
-        freeClient(c);
-        return;
-    }
-    if (nread) {
-        c->querybuf = sdscatlen(c->querybuf, buf, nread);
-        c->lastinteraction = time(NULL);
-    } else {
-        return;
-    }
-
+static void processInputBuffer(redisClient *c) {
 again:
     if (c->bulklen == -1) {
         /* Read the first line of the query */
@@ -1636,12 +1618,45 @@ static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mas
             c->argv[c->argc] = createStringObject(c->querybuf,c->bulklen-2);
             c->argc++;
             c->querybuf = sdsrange(c->querybuf,c->bulklen,-1);
-            processCommand(c);
+            /* Process the command. If the client is still valid after
+             * the processing and there is more data in the buffer
+             * try to parse it. */
+            if (processCommand(c) && sdslen(c->querybuf)) goto again;
             return;
         }
     }
 }
 
+static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
+    redisClient *c = (redisClient*) privdata;
+    char buf[REDIS_IOBUF_LEN];
+    int nread;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(mask);
+
+    nread = read(fd, buf, REDIS_IOBUF_LEN);
+    if (nread == -1) {
+        if (errno == EAGAIN) {
+            nread = 0;
+        } else {
+            redisLog(REDIS_DEBUG, "Reading from client: %s",strerror(errno));
+            freeClient(c);
+            return;
+        }
+    } else if (nread == 0) {
+        redisLog(REDIS_DEBUG, "Client closed connection");
+        freeClient(c);
+        return;
+    }
+    if (nread) {
+        c->querybuf = sdscatlen(c->querybuf, buf, nread);
+        c->lastinteraction = time(NULL);
+    } else {
+        return;
+    }
+    processInputBuffer(c);
+}
+
 static int selectDb(redisClient *c, int id) {
     if (id < 0 || id >= server.dbnum)
         return REDIS_ERR;