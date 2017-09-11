@@ -65,7 +65,7 @@ client *createClient(int fd) {
     client *c = zmalloc(sizeof(client));
 
     /* passing -1 as fd it is possible to create a non connected client.
-     * This is useful since all the Redis commands needs to be executed
+     * This is useful since all the commands needs to be executed
      * in the context of a client. When commands are executed in other
      * contexts (for instance a Lua script) we need a non connected client. */
     if (fd != -1) {
@@ -99,7 +99,7 @@ client *createClient(int fd) {
     c->flags = 0;
     c->ctime = c->lastinteraction = server.unixtime;
     c->authenticated = 0;
-    c->replstate = REDIS_REPL_NONE;
+    c->replstate = REPL_STATE_NONE;
     c->repl_put_online_on_ack = 0;
     c->reploff = 0;
     c->repl_ack_off = 0;
@@ -110,7 +110,7 @@ client *createClient(int fd) {
     c->obuf_soft_limit_reached_time = 0;
     listSetFreeMethod(c->reply,decrRefCountVoid);
     listSetDupMethod(c->reply,dupClientReplyValue);
-    c->btype = REDIS_BLOCKED_NONE;
+    c->btype = BLOCKED_NONE;
     c->bpop.timeout = 0;
     c->bpop.keys = dictCreate(&setDictType,NULL);
     c->bpop.target = NULL;
@@ -153,20 +153,20 @@ client *createClient(int fd) {
 int prepareClientToWrite(client *c) {
     /* If it's the Lua client we always return ok without installing any
      * handler since there is no socket at all. */
-    if (c->flags & REDIS_LUA_CLIENT) return C_OK;
+    if (c->flags & CLIENT_LUA) return C_OK;
 
-    /* Masters don't receive replies, unless REDIS_MASTER_FORCE_REPLY flag
+    /* Masters don't receive replies, unless CLIENT_MASTER_FORCE_REPLY flag
      * is set. */
-    if ((c->flags & REDIS_MASTER) &&
-        !(c->flags & REDIS_MASTER_FORCE_REPLY)) return C_ERR;
+    if ((c->flags & CLIENT_MASTER) &&
+        !(c->flags & CLIENT_MASTER_FORCE_REPLY)) return C_ERR;
 
     if (c->fd <= 0) return C_ERR; /* Fake client for AOF loading. */
 
     /* Only install the handler if not already installed and, in case of
      * slaves, if the client can actually receive writes. */
     if (c->bufpos == 0 && listLength(c->reply) == 0 &&
-        (c->replstate == REDIS_REPL_NONE ||
-         (c->replstate == REDIS_REPL_ONLINE && !c->repl_put_online_on_ack)))
+        (c->replstate == REPL_STATE_NONE ||
+         (c->replstate == SLAVE_STATE_ONLINE && !c->repl_put_online_on_ack)))
     {
         /* Try to install the write handler. */
         if (aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
@@ -204,7 +204,7 @@ robj *dupLastObjectIfNeeded(list *reply) {
 int _addReplyToBuffer(client *c, const char *s, size_t len) {
     size_t available = sizeof(c->buf)-c->bufpos;
 
-    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return C_OK;
+    if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return C_OK;
 
     /* If there already are entries in the reply list, we cannot
      * add anything more to the static buffer. */
@@ -221,7 +221,7 @@ int _addReplyToBuffer(client *c, const char *s, size_t len) {
 void _addReplyObjectToList(client *c, robj *o) {
     robj *tail;
 
-    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+    if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
         incrRefCount(o);
@@ -233,7 +233,7 @@ void _addReplyObjectToList(client *c, robj *o) {
         /* Append to this object when possible. */
         if (tail->ptr != NULL &&
             tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+sdslen(o->ptr) <= REDIS_REPLY_CHUNK_BYTES)
+            sdslen(tail->ptr)+sdslen(o->ptr) <= PROTO_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
@@ -253,7 +253,7 @@ void _addReplyObjectToList(client *c, robj *o) {
 void _addReplySdsToList(client *c, sds s) {
     robj *tail;
 
-    if (c->flags & REDIS_CLOSE_AFTER_REPLY) {
+    if (c->flags & CLIENT_CLOSE_AFTER_REPLY) {
         sdsfree(s);
         return;
     }
@@ -266,7 +266,7 @@ void _addReplySdsToList(client *c, sds s) {
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+sdslen(s) <= REDIS_REPLY_CHUNK_BYTES)
+            sdslen(tail->ptr)+sdslen(s) <= PROTO_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
@@ -284,7 +284,7 @@ void _addReplySdsToList(client *c, sds s) {
 void _addReplyStringToList(client *c, const char *s, size_t len) {
     robj *tail;
 
-    if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
+    if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return;
 
     if (listLength(c->reply) == 0) {
         robj *o = createStringObject(s,len);
@@ -296,7 +296,7 @@ void _addReplyStringToList(client *c, const char *s, size_t len) {
 
         /* Append to this object when possible. */
         if (tail->ptr != NULL && tail->encoding == OBJ_ENCODING_RAW &&
-            sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
+            sdslen(tail->ptr)+len <= PROTO_REPLY_CHUNK_BYTES)
         {
             c->reply_bytes -= sdsZmallocSize(tail->ptr);
             tail = dupLastObjectIfNeeded(c->reply);
@@ -349,7 +349,7 @@ void addReply(client *c, robj *obj) {
             _addReplyObjectToList(c,obj);
         decrRefCount(obj);
     } else {
-        redisPanic("Wrong obj->encoding in addReply()");
+        serverPanic("Wrong obj->encoding in addReply()");
     }
 }
 
@@ -480,10 +480,10 @@ void addReplyLongLongWithPrefix(client *c, long long ll, char prefix) {
     /* Things like $3\r\n or *2\r\n are emitted very often by the protocol
      * so we have a few shared objects to use if the integer is small
      * like it is most of the times. */
-    if (prefix == '*' && ll < REDIS_SHARED_BULKHDR_LEN && ll >= 0) {
+    if (prefix == '*' && ll < OBJ_SHARED_BULKHDR_LEN && ll >= 0) {
         addReply(c,shared.mbulkhdr[ll]);
         return;
-    } else if (prefix == '$' && ll < REDIS_SHARED_BULKHDR_LEN && ll >= 0) {
+    } else if (prefix == '$' && ll < OBJ_SHARED_BULKHDR_LEN && ll >= 0) {
         addReply(c,shared.bulkhdr[ll]);
         return;
     }
@@ -505,7 +505,7 @@ void addReplyLongLong(client *c, long long ll) {
 }
 
 void addReplyMultiBulkLen(client *c, long length) {
-    if (length < REDIS_SHARED_BULKHDR_LEN)
+    if (length < OBJ_SHARED_BULKHDR_LEN)
         addReply(c,shared.mbulkhdr[length]);
     else
         addReplyLongLongWithPrefix(c,length,'*');
@@ -531,7 +531,7 @@ void addReplyBulkLen(client *c, robj *obj) {
         }
     }
 
-    if (len < REDIS_SHARED_BULKHDR_LEN)
+    if (len < OBJ_SHARED_BULKHDR_LEN)
         addReply(c,shared.bulkhdr[len]);
     else
         addReplyLongLongWithPrefix(c,len,'$');
@@ -592,7 +592,7 @@ void copyClientOutputBuffer(client *dst, client *src) {
 static void acceptCommonHandler(int fd, int flags) {
     client *c;
     if ((c = createClient(fd)) == NULL) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Error registering fd event for the new client: %s (fd=%d)",
             strerror(errno),fd);
         close(fd); /* May be already closed, just ignore errors */
@@ -619,40 +619,40 @@ static void acceptCommonHandler(int fd, int flags) {
 
 void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     int cport, cfd, max = MAX_ACCEPTS_PER_CALL;
-    char cip[REDIS_IP_STR_LEN];
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
-    REDIS_NOTUSED(privdata);
+    char cip[NET_IP_STR_LEN];
+    UNUSED(el);
+    UNUSED(mask);
+    UNUSED(privdata);
 
     while(max--) {
         cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
         if (cfd == ANET_ERR) {
             if (errno != EWOULDBLOCK)
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Accepting client connection: %s", server.neterr);
             return;
         }
-        serverLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
+        serverLog(LL_VERBOSE,"Accepted %s:%d", cip, cport);
         acceptCommonHandler(cfd,0);
     }
 }
 
 void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     int cfd, max = MAX_ACCEPTS_PER_CALL;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
-    REDIS_NOTUSED(privdata);
+    UNUSED(el);
+    UNUSED(mask);
+    UNUSED(privdata);
 
     while(max--) {
         cfd = anetUnixAccept(server.neterr, fd);
         if (cfd == ANET_ERR) {
             if (errno != EWOULDBLOCK)
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Accepting client connection: %s", server.neterr);
             return;
         }
-        serverLog(REDIS_VERBOSE,"Accepted connection to %s", server.unixsocket);
-        acceptCommonHandler(cfd,REDIS_UNIX_SOCKET);
+        serverLog(LL_VERBOSE,"Accepted connection to %s", server.unixsocket);
+        acceptCommonHandler(cfd,CLIENT_UNIX_SOCKET);
     }
 }
 
@@ -678,7 +678,7 @@ void disconnectSlaves(void) {
  * master into an unexpected way. */
 void replicationHandleMasterDisconnection(void) {
     server.master = NULL;
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
     server.repl_down_since = server.unixtime;
     /* We lost connection with our master, force our slaves to resync
      * with us as well to load the new data set.
@@ -699,21 +699,21 @@ void freeClient(client *c) {
      *
      * Note that before doing this we make sure that the client is not in
      * some unexpected state, by checking its flags. */
-    if (server.master && c->flags & REDIS_MASTER) {
-        serverLog(REDIS_WARNING,"Connection with master lost.");
-        if (!(c->flags & (REDIS_CLOSE_AFTER_REPLY|
-                          REDIS_CLOSE_ASAP|
-                          REDIS_BLOCKED|
-                          REDIS_UNBLOCKED)))
+    if (server.master && c->flags & CLIENT_MASTER) {
+        serverLog(LL_WARNING,"Connection with master lost.");
+        if (!(c->flags & (CLIENT_CLOSE_AFTER_REPLY|
+                          CLIENT_CLOSE_ASAP|
+                          CLIENT_BLOCKED|
+                          CLIENT_UNBLOCKED)))
         {
             replicationCacheMaster(c);
             return;
         }
     }
 
     /* Log link disconnection with slave */
-    if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR)) {
-        serverLog(REDIS_WARNING,"Connection with slave %s lost.",
+    if ((c->flags & CLIENT_SLAVE) && !(c->flags & CLIENT_MONITOR)) {
+        serverLog(LL_WARNING,"Connection with slave %s lost.",
             replicationGetSlaveName(c));
     }
 
@@ -722,7 +722,7 @@ void freeClient(client *c) {
     c->querybuf = NULL;
 
     /* Deallocate structures used to block on blocking ops. */
-    if (c->flags & REDIS_BLOCKED) unblockClient(c);
+    if (c->flags & CLIENT_BLOCKED) unblockClient(c);
     dictRelease(c->bpop.keys);
 
     /* UNWATCH all the keys */
@@ -754,38 +754,38 @@ void freeClient(client *c) {
 
     /* When client was just unblocked because of a blocking operation,
      * remove it from the list of unblocked clients. */
-    if (c->flags & REDIS_UNBLOCKED) {
+    if (c->flags & CLIENT_UNBLOCKED) {
         ln = listSearchKey(server.unblocked_clients,c);
         serverAssert(ln != NULL);
         listDelNode(server.unblocked_clients,ln);
     }
 
     /* Master/slave cleanup Case 1:
      * we lost the connection with a slave. */
-    if (c->flags & REDIS_SLAVE) {
-        if (c->replstate == REDIS_REPL_SEND_BULK) {
+    if (c->flags & CLIENT_SLAVE) {
+        if (c->replstate == SLAVE_STATE_SEND_BULK) {
             if (c->repldbfd != -1) close(c->repldbfd);
             if (c->replpreamble) sdsfree(c->replpreamble);
         }
-        list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
+        list *l = (c->flags & CLIENT_MONITOR) ? server.monitors : server.slaves;
         ln = listSearchKey(l,c);
         serverAssert(ln != NULL);
         listDelNode(l,ln);
         /* We need to remember the time when we started to have zero
          * attached slaves, as after some time we'll free the replication
          * backlog. */
-        if (c->flags & REDIS_SLAVE && listLength(server.slaves) == 0)
+        if (c->flags & CLIENT_SLAVE && listLength(server.slaves) == 0)
             server.repl_no_slaves_since = server.unixtime;
         refreshGoodSlavesCount();
     }
 
     /* Master/slave cleanup Case 2:
      * we lost the connection with the master. */
-    if (c->flags & REDIS_MASTER) replicationHandleMasterDisconnection();
+    if (c->flags & CLIENT_MASTER) replicationHandleMasterDisconnection();
 
     /* If this client was scheduled for async freeing we need to remove it
      * from the queue. */
-    if (c->flags & REDIS_CLOSE_ASAP) {
+    if (c->flags & CLIENT_CLOSE_ASAP) {
         ln = listSearchKey(server.clients_to_close,c);
         serverAssert(ln != NULL);
         listDelNode(server.clients_to_close,ln);
@@ -805,8 +805,8 @@ void freeClient(client *c) {
  * a context where calling freeClient() is not possible, because the client
  * should be valid for the continuation of the flow of the program. */
 void freeClientAsync(client *c) {
-    if (c->flags & REDIS_CLOSE_ASAP || c->flags & REDIS_LUA_CLIENT) return;
-    c->flags |= REDIS_CLOSE_ASAP;
+    if (c->flags & CLIENT_CLOSE_ASAP || c->flags & CLIENT_LUA) return;
+    c->flags |= CLIENT_CLOSE_ASAP;
     listAddNodeTail(server.clients_to_close,c);
 }
 
@@ -815,7 +815,7 @@ void freeClientsInAsyncFreeQueue(void) {
         listNode *ln = listFirst(server.clients_to_close);
         client *c = listNodeValue(ln);
 
-        c->flags &= ~REDIS_CLOSE_ASAP;
+        c->flags &= ~CLIENT_CLOSE_ASAP;
         freeClient(c);
         listDelNode(server.clients_to_close,ln);
     }
@@ -827,8 +827,8 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     size_t objlen;
     size_t objmem;
     robj *o;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(mask);
 
     while(c->bufpos > 0 || listLength(c->reply)) {
         if (c->bufpos > 0) {
@@ -866,7 +866,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
                 c->reply_bytes -= objmem;
             }
         }
-        /* Note that we avoid to send more than REDIS_MAX_WRITE_PER_EVENT
+        /* Note that we avoid to send more than NET_MAX_WRITES_PER_EVENT
          * bytes, in a single threaded server it's a good idea to serve
          * other clients as well, even if a very large request comes from
          * super fast link that is always able to accept data (in real world
@@ -875,15 +875,15 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
          * However if we are over the maxmemory limit we ignore that and
          * just deliver as much data as it is possible to deliver. */
         server.stat_net_output_bytes += totwritten;
-        if (totwritten > REDIS_MAX_WRITE_PER_EVENT &&
+        if (totwritten > NET_MAX_WRITES_PER_EVENT &&
             (server.maxmemory == 0 ||
              zmalloc_used_memory() < server.maxmemory)) break;
     }
     if (nwritten == -1) {
         if (errno == EAGAIN) {
             nwritten = 0;
         } else {
-            serverLog(REDIS_VERBOSE,
+            serverLog(LL_VERBOSE,
                 "Error writing to client: %s", strerror(errno));
             freeClient(c);
             return;
@@ -894,14 +894,14 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
          * as an interaction, since we always send REPLCONF ACK commands
          * that take some time to just fill the socket output buffer.
          * We just rely on data / pings received for timeout detection. */
-        if (!(c->flags & REDIS_MASTER)) c->lastinteraction = server.unixtime;
+        if (!(c->flags & CLIENT_MASTER)) c->lastinteraction = server.unixtime;
     }
     if (c->bufpos == 0 && listLength(c->reply) == 0) {
         c->sentlen = 0;
         aeDeleteFileEvent(server.el,c->fd,AE_WRITABLE);
 
         /* Close connection after entire reply has been sent. */
-        if (c->flags & REDIS_CLOSE_AFTER_REPLY) freeClient(c);
+        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) freeClient(c);
     }
 }
 
@@ -915,8 +915,8 @@ void resetClient(client *c) {
     c->bulklen = -1;
     /* We clear the ASKING flag as well if we are not inside a MULTI, and
      * if what we just executed is not the ASKING command itself. */
-    if (!(c->flags & REDIS_MULTI) && prevcmd != askingCommand)
-        c->flags &= (~REDIS_ASKING);
+    if (!(c->flags & CLIENT_MULTI) && prevcmd != askingCommand)
+        c->flags &= (~CLIENT_ASKING);
 }
 
 int processInlineBuffer(client *c) {
@@ -930,7 +930,7 @@ int processInlineBuffer(client *c) {
 
     /* Nothing to do without a \r\n */
     if (newline == NULL) {
-        if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+        if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
             addReplyError(c,"Protocol error: too big inline request");
             setProtocolError(c,0);
         }
@@ -955,7 +955,7 @@ int processInlineBuffer(client *c) {
     /* Newline from slaves can be used to refresh the last ACK time.
      * This is useful for a slave to ping back while loading a big
      * RDB file. */
-    if (querylen == 0 && c->flags & REDIS_SLAVE)
+    if (querylen == 0 && c->flags & CLIENT_SLAVE)
         c->repl_ack_time = server.unixtime;
 
     /* Leave data after the first line of the query in the buffer */
@@ -983,13 +983,13 @@ int processInlineBuffer(client *c) {
 /* Helper function. Trims query buffer to make the function that processes
  * multi bulk requests idempotent. */
 static void setProtocolError(client *c, int pos) {
-    if (server.verbosity <= REDIS_VERBOSE) {
+    if (server.verbosity <= LL_VERBOSE) {
         sds client = catClientInfoString(sdsempty(),c);
-        serverLog(REDIS_VERBOSE,
+        serverLog(LL_VERBOSE,
             "Protocol error from client: %s", client);
         sdsfree(client);
     }
-    c->flags |= REDIS_CLOSE_AFTER_REPLY;
+    c->flags |= CLIENT_CLOSE_AFTER_REPLY;
     sdsrange(c->querybuf,pos,-1);
 }
 
@@ -1005,7 +1005,7 @@ int processMultibulkBuffer(client *c) {
         /* Multi bulk length cannot be read without a \r\n */
         newline = strchr(c->querybuf,'\r');
         if (newline == NULL) {
-            if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+            if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
                 addReplyError(c,"Protocol error: too big mbulk count string");
                 setProtocolError(c,0);
             }
@@ -1045,7 +1045,7 @@ int processMultibulkBuffer(client *c) {
         if (c->bulklen == -1) {
             newline = strchr(c->querybuf+pos,'\r');
             if (newline == NULL) {
-                if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+                if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
                     addReplyError(c,
                         "Protocol error: too big bulk count string");
                     setProtocolError(c,0);
@@ -1074,7 +1074,7 @@ int processMultibulkBuffer(client *c) {
             }
 
             pos += newline-(c->querybuf+pos)+2;
-            if (ll >= REDIS_MBULK_BIG_ARG) {
+            if (ll >= PROTO_MBULK_BIG_ARG) {
                 size_t qblen;
 
                 /* If we are going to read a large object from network
@@ -1101,7 +1101,7 @@ int processMultibulkBuffer(client *c) {
              * instead of creating a new object by *copying* the sds we
              * just use the current sds string. */
             if (pos == 0 &&
-                c->bulklen >= REDIS_MBULK_BIG_ARG &&
+                c->bulklen >= PROTO_MBULK_BIG_ARG &&
                 (signed) sdslen(c->querybuf) == c->bulklen+2)
             {
                 c->argv[c->argc++] = createObject(OBJ_STRING,c->querybuf);
@@ -1136,31 +1136,31 @@ void processInputBuffer(client *c) {
     /* Keep processing while there is something in the input buffer */
     while(sdslen(c->querybuf)) {
         /* Return if clients are paused. */
-        if (!(c->flags & REDIS_SLAVE) && clientsArePaused()) break;
+        if (!(c->flags & CLIENT_SLAVE) && clientsArePaused()) break;
 
         /* Immediately abort if the client is in the middle of something. */
-        if (c->flags & REDIS_BLOCKED) break;
+        if (c->flags & CLIENT_BLOCKED) break;
 
-        /* REDIS_CLOSE_AFTER_REPLY closes the connection once the reply is
+        /* CLIENT_CLOSE_AFTER_REPLY closes the connection once the reply is
          * written to the client. Make sure to not let the reply grow after
          * this flag has been set (i.e. don't process more commands). */
-        if (c->flags & REDIS_CLOSE_AFTER_REPLY) break;
+        if (c->flags & CLIENT_CLOSE_AFTER_REPLY) break;
 
         /* Determine request type when unknown. */
         if (!c->reqtype) {
             if (c->querybuf[0] == '*') {
-                c->reqtype = REDIS_REQ_MULTIBULK;
+                c->reqtype = PROTO_REQ_MULTIBULK;
             } else {
-                c->reqtype = REDIS_REQ_INLINE;
+                c->reqtype = PROTO_REQ_INLINE;
             }
         }
 
-        if (c->reqtype == REDIS_REQ_INLINE) {
+        if (c->reqtype == PROTO_REQ_INLINE) {
             if (processInlineBuffer(c) != C_OK) break;
-        } else if (c->reqtype == REDIS_REQ_MULTIBULK) {
+        } else if (c->reqtype == PROTO_REQ_MULTIBULK) {
             if (processMultibulkBuffer(c) != C_OK) break;
         } else {
-            redisPanic("Unknown request type");
+            serverPanic("Unknown request type");
         }
 
         /* Multibulk processing could see a <= 0 length. */
@@ -1179,18 +1179,18 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     client *c = (client*) privdata;
     int nread, readlen;
     size_t qblen;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(mask);
 
-    readlen = REDIS_IOBUF_LEN;
+    readlen = PROTO_IOBUF_LEN;
     /* If this is a multi bulk request, and we are processing a bulk reply
      * that is large enough, try to maximize the probability that the query
      * buffer contains exactly the SDS string representing the object, even
      * at the risk of requiring more read(2) calls. This way the function
      * processMultiBulkBuffer() can avoid copying buffers to create the
      * Redis Object representing the argument. */
-    if (c->reqtype == REDIS_REQ_MULTIBULK && c->multibulklen && c->bulklen != -1
-        && c->bulklen >= REDIS_MBULK_BIG_ARG)
+    if (c->reqtype == PROTO_REQ_MULTIBULK && c->multibulklen && c->bulklen != -1
+        && c->bulklen >= PROTO_MBULK_BIG_ARG)
     {
         int remaining = (unsigned)(c->bulklen+2)-sdslen(c->querybuf);
 
@@ -1205,25 +1205,25 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (errno == EAGAIN) {
             return;
         } else {
-            serverLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
+            serverLog(LL_VERBOSE, "Reading from client: %s",strerror(errno));
             freeClient(c);
             return;
         }
     } else if (nread == 0) {
-        serverLog(REDIS_VERBOSE, "Client closed connection");
+        serverLog(LL_VERBOSE, "Client closed connection");
         freeClient(c);
         return;
     }
 
     sdsIncrLen(c->querybuf,nread);
     c->lastinteraction = server.unixtime;
-    if (c->flags & REDIS_MASTER) c->reploff += nread;
+    if (c->flags & CLIENT_MASTER) c->reploff += nread;
     server.stat_net_input_bytes += nread;
     if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
         sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
 
         bytes = sdscatrepr(bytes,c->querybuf,64);
-        serverLog(REDIS_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
+        serverLog(LL_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
         sdsfree(ci);
         sdsfree(bytes);
         freeClient(c);
@@ -1255,15 +1255,15 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
  * For IPv6 addresses we use [] around the IP part, like in "[::1]:1234".
  * For Unix sockets we use path:0, like in "/tmp/redis:0".
  *
- * A Peer ID always fits inside a buffer of REDIS_PEER_ID_LEN bytes, including
+ * A Peer ID always fits inside a buffer of NET_PEER_ID_LEN bytes, including
  * the null term.
  *
  * On failure the function still populates 'peerid' with the "?:0" string
  * in case you want to relax error checking or need to display something
  * anyway (see anetPeerToString implementation for more info). */
 void genClientPeerId(client *client, char *peerid,
                             size_t peerid_len) {
-    if (client->flags & REDIS_UNIX_SOCKET) {
+    if (client->flags & CLIENT_UNIX_SOCKET) {
         /* Unix socket client. */
         snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
     } else {
@@ -1277,7 +1277,7 @@ void genClientPeerId(client *client, char *peerid,
  * The Peer ID never changes during the life of the client, however it
  * is expensive to compute. */
 char *getClientPeerId(client *c) {
-    char peerid[REDIS_PEER_ID_LEN];
+    char peerid[NET_PEER_ID_LEN];
 
     if (c->peerid == NULL) {
         genClientPeerId(c,peerid,sizeof(peerid));
@@ -1293,21 +1293,21 @@ sds catClientInfoString(sds s, client *client) {
     int emask;
 
     p = flags;
-    if (client->flags & REDIS_SLAVE) {
-        if (client->flags & REDIS_MONITOR)
+    if (client->flags & CLIENT_SLAVE) {
+        if (client->flags & CLIENT_MONITOR)
             *p++ = 'O';
         else
             *p++ = 'S';
     }
-    if (client->flags & REDIS_MASTER) *p++ = 'M';
-    if (client->flags & REDIS_MULTI) *p++ = 'x';
-    if (client->flags & REDIS_BLOCKED) *p++ = 'b';
-    if (client->flags & REDIS_DIRTY_CAS) *p++ = 'd';
-    if (client->flags & REDIS_CLOSE_AFTER_REPLY) *p++ = 'c';
-    if (client->flags & REDIS_UNBLOCKED) *p++ = 'u';
-    if (client->flags & REDIS_CLOSE_ASAP) *p++ = 'A';
-    if (client->flags & REDIS_UNIX_SOCKET) *p++ = 'U';
-    if (client->flags & REDIS_READONLY) *p++ = 'r';
+    if (client->flags & CLIENT_MASTER) *p++ = 'M';
+    if (client->flags & CLIENT_MULTI) *p++ = 'x';
+    if (client->flags & CLIENT_BLOCKED) *p++ = 'b';
+    if (client->flags & CLIENT_DIRTY_CAS) *p++ = 'd';
+    if (client->flags & CLIENT_CLOSE_AFTER_REPLY) *p++ = 'c';
+    if (client->flags & CLIENT_UNBLOCKED) *p++ = 'u';
+    if (client->flags & CLIENT_CLOSE_ASAP) *p++ = 'A';
+    if (client->flags & CLIENT_UNIX_SOCKET) *p++ = 'U';
+    if (client->flags & CLIENT_READONLY) *p++ = 'r';
     if (p == flags) *p++ = 'N';
     *p++ = '\0';
 
@@ -1328,7 +1328,7 @@ sds catClientInfoString(sds s, client *client) {
         client->db->id,
         (int) dictSize(client->pubsub_channels),
         (int) listLength(client->pubsub_patterns),
-        (client->flags & REDIS_MULTI) ? client->mstate.count : -1,
+        (client->flags & CLIENT_MULTI) ? client->mstate.count : -1,
         (unsigned long long) sdslen(client->querybuf),
         (unsigned long long) sdsavail(client->querybuf),
         (unsigned long long) client->bufpos,
@@ -1425,7 +1425,7 @@ void clientCommand(client *c) {
             client = listNodeValue(ln);
             if (addr && strcmp(getClientPeerId(client),addr) != 0) continue;
             if (type != -1 &&
-                (client->flags & REDIS_MASTER ||
+                (client->flags & CLIENT_MASTER ||
                  getClientType(client) != type)) continue;
             if (id != 0 && client->id != id) continue;
             if (c == client && skipme) continue;
@@ -1451,7 +1451,7 @@ void clientCommand(client *c) {
 
         /* If this client has to be closed, flag it as CLOSE_AFTER_REPLY
          * only after we queued the reply to its output buffers. */
-        if (close_this_client) c->flags |= REDIS_CLOSE_AFTER_REPLY;
+        if (close_this_client) c->flags |= CLIENT_CLOSE_AFTER_REPLY;
     } else if (!strcasecmp(c->argv[1]->ptr,"setname") && c->argc == 3) {
         int j, len = sdslen(c->argv[2]->ptr);
         char *p = c->argv[2]->ptr;
@@ -1578,30 +1578,30 @@ unsigned long getClientOutputBufferMemoryUsage(client *c) {
  * classes of clients.
  *
  * The function will return one of the following:
- * REDIS_CLIENT_TYPE_NORMAL -> Normal client
- * REDIS_CLIENT_TYPE_SLAVE  -> Slave or client executing MONITOR command
- * REDIS_CLIENT_TYPE_PUBSUB -> Client subscribed to Pub/Sub channels
+ * CLIENT_TYPE_NORMAL -> Normal client
+ * CLIENT_TYPE_SLAVE  -> Slave or client executing MONITOR command
+ * CLIENT_TYPE_PUBSUB -> Client subscribed to Pub/Sub channels
  */
 int getClientType(client *c) {
-    if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR))
-        return REDIS_CLIENT_TYPE_SLAVE;
-    if (c->flags & REDIS_PUBSUB)
-        return REDIS_CLIENT_TYPE_PUBSUB;
-    return REDIS_CLIENT_TYPE_NORMAL;
+    if ((c->flags & CLIENT_SLAVE) && !(c->flags & CLIENT_MONITOR))
+        return CLIENT_TYPE_SLAVE;
+    if (c->flags & CLIENT_PUBSUB)
+        return CLIENT_TYPE_PUBSUB;
+    return CLIENT_TYPE_NORMAL;
 }
 
 int getClientTypeByName(char *name) {
-    if (!strcasecmp(name,"normal")) return REDIS_CLIENT_TYPE_NORMAL;
-    else if (!strcasecmp(name,"slave")) return REDIS_CLIENT_TYPE_SLAVE;
-    else if (!strcasecmp(name,"pubsub")) return REDIS_CLIENT_TYPE_PUBSUB;
+    if (!strcasecmp(name,"normal")) return CLIENT_TYPE_NORMAL;
+    else if (!strcasecmp(name,"slave")) return CLIENT_TYPE_SLAVE;
+    else if (!strcasecmp(name,"pubsub")) return CLIENT_TYPE_PUBSUB;
     else return -1;
 }
 
 char *getClientTypeName(int class) {
     switch(class) {
-    case REDIS_CLIENT_TYPE_NORMAL: return "normal";
-    case REDIS_CLIENT_TYPE_SLAVE:  return "slave";
-    case REDIS_CLIENT_TYPE_PUBSUB: return "pubsub";
+    case CLIENT_TYPE_NORMAL: return "normal";
+    case CLIENT_TYPE_SLAVE:  return "slave";
+    case CLIENT_TYPE_PUBSUB: return "pubsub";
     default:                       return NULL;
     }
 }
@@ -1648,19 +1648,19 @@ int checkClientOutputBufferLimits(client *c) {
 
 /* Asynchronously close a client if soft or hard limit is reached on the
  * output buffer size. The caller can check if the client will be closed
- * checking if the client REDIS_CLOSE_ASAP flag is set.
+ * checking if the client CLIENT_CLOSE_ASAP flag is set.
  *
  * Note: we need to close the client asynchronously because this function is
  * called from contexts where the client can't be freed safely, i.e. from the
  * lower level functions pushing data inside the client output buffers. */
 void asyncCloseClientOnOutputBufferLimitReached(client *c) {
     serverAssert(c->reply_bytes < SIZE_MAX-(1024*64));
-    if (c->reply_bytes == 0 || c->flags & REDIS_CLOSE_ASAP) return;
+    if (c->reply_bytes == 0 || c->flags & CLIENT_CLOSE_ASAP) return;
     if (checkClientOutputBufferLimits(c)) {
         sds client = catClientInfoString(sdsempty(),c);
 
         freeClientAsync(c);
-        serverLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
+        serverLog(LL_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
         sdsfree(client);
     }
 }
@@ -1678,7 +1678,7 @@ void flushSlavesOutputBuffers(void) {
 
         events = aeGetFileEvents(server.el,slave->fd);
         if (events & AE_WRITABLE &&
-            slave->replstate == REDIS_REPL_ONLINE &&
+            slave->replstate == SLAVE_STATE_ONLINE &&
             listLength(slave->reply))
         {
             sendReplyToClient(server.el,slave->fd,slave,0);
@@ -1729,8 +1729,8 @@ int clientsArePaused(void) {
 
             /* Don't touch slaves and blocked clients. The latter pending
              * requests be processed when unblocked. */
-            if (c->flags & (REDIS_SLAVE|REDIS_BLOCKED)) continue;
-            c->flags |= REDIS_UNBLOCKED;
+            if (c->flags & (CLIENT_SLAVE|CLIENT_BLOCKED)) continue;
+            c->flags |= CLIENT_UNBLOCKED;
             listAddNodeTail(server.unblocked_clients,c);
         }
     }