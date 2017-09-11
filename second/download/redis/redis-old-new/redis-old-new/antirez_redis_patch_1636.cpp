@@ -16,7 +16,6 @@ redisClient *createClient(int fd) {
 
     anetNonBlock(NULL,fd);
     anetTcpNoDelay(NULL,fd);
-    if (!c) return NULL;
     if (aeCreateFileEvent(server.el,fd,AE_READABLE,
         readQueryFromClient, c) == AE_ERR)
     {
@@ -60,9 +59,6 @@ redisClient *createClient(int fd) {
 /* Set the event loop to listen for write events on the client's socket.
  * Typically gets called every time a reply is built. */
 int _installWriteEvent(redisClient *c) {
-    /* When CLOSE_AFTER_REPLY is set, no more replies may be added! */
-    redisAssert(!(c->flags & REDIS_CLOSE_AFTER_REPLY));
-
     if (c->fd <= 0) return REDIS_ERR;
     if (c->bufpos == 0 && listLength(c->reply) == 0 &&
         (c->replstate == REDIS_REPL_NONE ||
@@ -88,9 +84,15 @@ robj *dupLastObjectIfNeeded(list *reply) {
     return listNodeValue(ln);
 }
 
+/* -----------------------------------------------------------------------------
+ * Low level functions to add more data to output buffers.
+ * -------------------------------------------------------------------------- */
+
 int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
     size_t available = sizeof(c->buf)-c->bufpos;
 
+    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return REDIS_OK;
+
     /* If there already are entries in the reply list, we cannot
      * add anything more to the static buffer. */
     if (listLength(c->reply) > 0) return REDIS_ERR;
@@ -105,6 +107,9 @@ int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
 
 void _addReplyObjectToList(redisClient *c, robj *o) {
     robj *tail;
+
+    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+
     if (listLength(c->reply) == 0) {
         incrRefCount(o);
         listAddNodeTail(c->reply,o);
@@ -128,6 +133,12 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
  * needed it will be free'd, otherwise it ends up in a robj. */
 void _addReplySdsToList(redisClient *c, sds s) {
     robj *tail;
+
+    if (c->flags & REDIS_CLOSE_AFTER_REPLY) {
+        sdsfree(s);
+        return;
+    }
+
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createObject(REDIS_STRING,s));
     } else {
@@ -148,6 +159,9 @@ void _addReplySdsToList(redisClient *c, sds s) {
 
 void _addReplyStringToList(redisClient *c, char *s, size_t len) {
     robj *tail;
+
+    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+
     if (listLength(c->reply) == 0) {
         listAddNodeTail(c->reply,createStringObject(s,len));
     } else {
@@ -165,6 +179,11 @@ void _addReplyStringToList(redisClient *c, char *s, size_t len) {
     }
 }
 
+/* -----------------------------------------------------------------------------
+ * Higher level functions to queue data on the client output buffer.
+ * The following functions are the ones that commands implementations will call.
+ * -------------------------------------------------------------------------- */
+
 void addReply(redisClient *c, robj *obj) {
     if (_installWriteEvent(c) != REDIS_OK) return;
 
@@ -301,7 +320,12 @@ void _addReplyLongLong(redisClient *c, long long ll, char prefix) {
 }
 
 void addReplyLongLong(redisClient *c, long long ll) {
-    _addReplyLongLong(c,ll,':');
+    if (ll == 0)
+        addReply(c,shared.czero);
+    else if (ll == 1)
+        addReply(c,shared.cone);
+    else
+        _addReplyLongLong(c,ll,':');
 }
 
 void addReplyMultiBulkLen(redisClient *c, long length) {
@@ -395,7 +419,7 @@ void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     cfd = anetTcpAccept(server.neterr, fd, cip, &cport);
     if (cfd == AE_ERR) {
-        redisLog(REDIS_VERBOSE,"Accepting client connection: %s", server.neterr);
+        redisLog(REDIS_WARNING,"Accepting client connection: %s", server.neterr);
         return;
     }
     redisLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
@@ -410,7 +434,7 @@ void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     cfd = anetUnixAccept(server.neterr, fd);
     if (cfd == AE_ERR) {
-        redisLog(REDIS_VERBOSE,"Accepting client connection: %s", server.neterr);
+        redisLog(REDIS_WARNING,"Accepting client connection: %s", server.neterr);
         return;
     }
     redisLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
@@ -502,10 +526,16 @@ void freeClient(redisClient *c) {
          * close the connection with all our slaves if we have any, so
          * when we'll resync with the master the other slaves will sync again
          * with us as well. Note that also when the slave is not connected
-         * to the master it will keep refusing connections by other slaves. */
-        while (listLength(server.slaves)) {
-            ln = listFirst(server.slaves);
-            freeClient((redisClient*)ln->value);
+         * to the master it will keep refusing connections by other slaves.
+         *
+         * We do this only if server.masterhost != NULL. If it is NULL this
+         * means the user called SLAVEOF NO ONE and we are freeing our
+         * link with the master, so no need to close link with slaves. */
+        if (server.masterhost != NULL) {
+            while (listLength(server.slaves)) {
+                ln = listFirst(server.slaves);
+                freeClient((redisClient*)ln->value);
+            }
         }
     }
     /* Release memory */
@@ -670,70 +700,74 @@ static void setProtocolError(redisClient *c, int pos) {
 
 int processMultibulkBuffer(redisClient *c) {
     char *newline = NULL;
-    char *eptr;
-    int pos = 0, tolerr;
-    long bulklen;
+    int pos = 0, ok;
+    long long ll;
 
     if (c->multibulklen == 0) {
         /* The client should have been reset */
         redisAssert(c->argc == 0);
 
         /* Multi bulk length cannot be read without a \r\n */
-        newline = strstr(c->querybuf,"\r\n");
+        newline = strchr(c->querybuf,'\r');
         if (newline == NULL)
             return REDIS_ERR;
 
+        /* Buffer should also contain \n */
+        if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
+            return REDIS_ERR;
+
         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
         redisAssert(c->querybuf[0] == '*');
-        c->multibulklen = strtol(c->querybuf+1,&eptr,10);
-        pos = (newline-c->querybuf)+2;
-        if (c->multibulklen <= 0) {
-            c->querybuf = sdsrange(c->querybuf,pos,-1);
-            return REDIS_OK;
-        } else if (c->multibulklen > 1024*1024) {
+        ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
+        if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
             setProtocolError(c,pos);
             return REDIS_ERR;
         }
 
+        pos = (newline-c->querybuf)+2;
+        if (ll <= 0) {
+            c->querybuf = sdsrange(c->querybuf,pos,-1);
+            return REDIS_OK;
+        }
+
+        c->multibulklen = ll;
+
         /* Setup argv array on client structure */
         if (c->argv) zfree(c->argv);
         c->argv = zmalloc(sizeof(robj*)*c->multibulklen);
-
-        /* Search new newline */
-        newline = strstr(c->querybuf+pos,"\r\n");
     }
 
     redisAssert(c->multibulklen > 0);
     while(c->multibulklen) {
         /* Read bulk length if unknown */
         if (c->bulklen == -1) {
-            newline = strstr(c->querybuf+pos,"\r\n");
-            if (newline != NULL) {
-                if (c->querybuf[pos] != '$') {
-                    addReplyErrorFormat(c,
-                        "Protocol error: expected '$', got '%c'",
-                        c->querybuf[pos]);
-                    setProtocolError(c,pos);
-                    return REDIS_ERR;
-                }
+            newline = strchr(c->querybuf+pos,'\r');
+            if (newline == NULL)
+                break;
 
-                bulklen = strtol(c->querybuf+pos+1,&eptr,10);
-                tolerr = (eptr[0] != '\r');
-                if (tolerr || bulklen == LONG_MIN || bulklen == LONG_MAX ||
-                    bulklen < 0 || bulklen > 512*1024*1024)
-                {
-                    addReplyError(c,"Protocol error: invalid bulk length");
-                    setProtocolError(c,pos);
-                    return REDIS_ERR;
-                }
-                pos += eptr-(c->querybuf+pos)+2;
-                c->bulklen = bulklen;
-            } else {
-                /* No newline in current buffer, so wait for more data */
+            /* Buffer should also contain \n */
+            if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
                 break;
+
+            if (c->querybuf[pos] != '$') {
+                addReplyErrorFormat(c,
+                    "Protocol error: expected '$', got '%c'",
+                    c->querybuf[pos]);
+                setProtocolError(c,pos);
+                return REDIS_ERR;
+            }
+
+            ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
+            if (!ok || ll < 0 || ll > 512*1024*1024) {
+                addReplyError(c,"Protocol error: invalid bulk length");
+                setProtocolError(c,pos);
+                return REDIS_ERR;
             }
+
+            pos += newline-(c->querybuf+pos)+2;
+            c->bulklen = ll;
         }
 
         /* Read bulk argument */
@@ -845,3 +879,70 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
     *biggest_input_buffer = bib;
 }
 
+void clientCommand(redisClient *c) {
+    listNode *ln;
+    listIter li;
+    redisClient *client;
+
+    if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
+        sds o = sdsempty();
+        time_t now = time(NULL);
+
+        listRewind(server.clients,&li);
+        while ((ln = listNext(&li)) != NULL) {
+            char ip[32], flags[16], *p;
+            int port;
+
+            client = listNodeValue(ln);
+            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
+            p = flags;
+            if (client->flags & REDIS_SLAVE) {
+                if (client->flags & REDIS_MONITOR)
+                    *p++ = 'O';
+                else
+                    *p++ = 'S';
+            }
+            if (client->flags & REDIS_MASTER) *p++ = 'M';
+            if (p == flags) *p++ = 'N';
+            if (client->flags & REDIS_MULTI) *p++ = 'x';
+            if (client->flags & REDIS_BLOCKED) *p++ = 'b';
+            if (client->flags & REDIS_IO_WAIT) *p++ = 'i';
+            if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
+            if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
+            if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
+            *p++ = '\0';
+            o = sdscatprintf(o,
+                "addr=%s:%d fd=%d idle=%ld flags=%s db=%d sub=%d psub=%d\n",
+                ip,port,client->fd,
+                (long)(now - client->lastinteraction),
+                flags,
+                client->db->id,
+                (int) dictSize(client->pubsub_channels),
+                (int) listLength(client->pubsub_patterns));
+        }
+        addReplyBulkCBuffer(c,o,sdslen(o));
+        sdsfree(o);
+    } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
+        listRewind(server.clients,&li);
+        while ((ln = listNext(&li)) != NULL) {
+            char ip[32], addr[64];
+            int port;
+
+            client = listNodeValue(ln);
+            if (anetPeerToString(client->fd,ip,&port) == -1) continue;
+            snprintf(addr,sizeof(addr),"%s:%d",ip,port);
+            if (strcmp(addr,c->argv[2]->ptr) == 0) {
+                addReply(c,shared.ok);
+                if (c == client) {
+                    client->flags |= REDIS_CLOSE_AFTER_REPLY;
+                } else {
+                    freeClient(client);
+                }
+                return;
+            }
+        }
+        addReplyError(c,"No such client");
+    } else {
+        addReplyError(c, "Syntax error, try CLIENT (LIST | KILL ip:port)");
+    }
+}