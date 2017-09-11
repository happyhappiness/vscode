@@ -31,7 +31,7 @@
 #include <sys/uio.h>
 #include <math.h>
 
-static void setProtocolError(redisClient *c, int pos);
+static void setProtocolError(client *c, int pos);
 
 /* Return the size consumed from the allocator, for the specified SDS string,
  * including internal fragmentation. This function is used in order to compute
@@ -61,8 +61,8 @@ int listMatchObjects(void *a, void *b) {
     return equalStringObjects(a,b);
 }
 
-redisClient *createClient(int fd) {
-    redisClient *c = zmalloc(sizeof(redisClient));
+client *createClient(int fd) {
+    client *c = zmalloc(sizeof(client));
 
     /* passing -1 as fd it is possible to create a non connected client.
      * This is useful since all the Redis commands needs to be executed
@@ -150,7 +150,7 @@ redisClient *createClient(int fd) {
  * Typically gets called every time a reply is built, before adding more
  * data to the clients output buffers. If the function returns REDIS_ERR no
  * data should be appended to the output buffers. */
-int prepareClientToWrite(redisClient *c) {
+int prepareClientToWrite(client *c) {
     /* If it's the Lua client we always return ok without installing any
      * handler since there is no socket at all. */
     if (c->flags & REDIS_LUA_CLIENT) return REDIS_OK;
@@ -201,7 +201,7 @@ robj *dupLastObjectIfNeeded(list *reply) {
  * Low level functions to add more data to output buffers.
  * -------------------------------------------------------------------------- */
 
-int _addReplyToBuffer(redisClient *c, const char *s, size_t len) {
+int _addReplyToBuffer(client *c, const char *s, size_t len) {
     size_t available = sizeof(c->buf)-c->bufpos;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return REDIS_OK;
@@ -218,7 +218,7 @@ int _addReplyToBuffer(redisClient *c, const char *s, size_t len) {
     return REDIS_OK;
 }
 
-void _addReplyObjectToList(redisClient *c, robj *o) {
+void _addReplyObjectToList(client *c, robj *o) {
     robj *tail;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
@@ -250,7 +250,7 @@ void _addReplyObjectToList(redisClient *c, robj *o) {
 
 /* This method takes responsibility over the sds. When it is no longer
  * needed it will be free'd, otherwise it ends up in a robj. */
-void _addReplySdsToList(redisClient *c, sds s) {
+void _addReplySdsToList(client *c, sds s) {
     robj *tail;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) {
@@ -281,7 +281,7 @@ void _addReplySdsToList(redisClient *c, sds s) {
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
-void _addReplyStringToList(redisClient *c, const char *s, size_t len) {
+void _addReplyStringToList(client *c, const char *s, size_t len) {
     robj *tail;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
@@ -317,7 +317,7 @@ void _addReplyStringToList(redisClient *c, const char *s, size_t len) {
  * The following functions are the ones that commands implementations will call.
  * -------------------------------------------------------------------------- */
 
-void addReply(redisClient *c, robj *obj) {
+void addReply(client *c, robj *obj) {
     if (prepareClientToWrite(c) != REDIS_OK) return;
 
     /* This is an important place where we can avoid copy-on-write
@@ -353,7 +353,7 @@ void addReply(redisClient *c, robj *obj) {
     }
 }
 
-void addReplySds(redisClient *c, sds s) {
+void addReplySds(client *c, sds s) {
     if (prepareClientToWrite(c) != REDIS_OK) {
         /* The caller expects the sds to be free'd. */
         sdsfree(s);
@@ -367,23 +367,23 @@ void addReplySds(redisClient *c, sds s) {
     }
 }
 
-void addReplyString(redisClient *c, const char *s, size_t len) {
+void addReplyString(client *c, const char *s, size_t len) {
     if (prepareClientToWrite(c) != REDIS_OK) return;
     if (_addReplyToBuffer(c,s,len) != REDIS_OK)
         _addReplyStringToList(c,s,len);
 }
 
-void addReplyErrorLength(redisClient *c, const char *s, size_t len) {
+void addReplyErrorLength(client *c, const char *s, size_t len) {
     addReplyString(c,"-ERR ",5);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyError(redisClient *c, const char *err) {
+void addReplyError(client *c, const char *err) {
     addReplyErrorLength(c,err,strlen(err));
 }
 
-void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
+void addReplyErrorFormat(client *c, const char *fmt, ...) {
     size_t l, j;
     va_list ap;
     va_start(ap,fmt);
@@ -399,17 +399,17 @@ void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
     sdsfree(s);
 }
 
-void addReplyStatusLength(redisClient *c, const char *s, size_t len) {
+void addReplyStatusLength(client *c, const char *s, size_t len) {
     addReplyString(c,"+",1);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyStatus(redisClient *c, const char *status) {
+void addReplyStatus(client *c, const char *status) {
     addReplyStatusLength(c,status,strlen(status));
 }
 
-void addReplyStatusFormat(redisClient *c, const char *fmt, ...) {
+void addReplyStatusFormat(client *c, const char *fmt, ...) {
     va_list ap;
     va_start(ap,fmt);
     sds s = sdscatvprintf(sdsempty(),fmt,ap);
@@ -420,7 +420,7 @@ void addReplyStatusFormat(redisClient *c, const char *fmt, ...) {
 
 /* Adds an empty object to the reply list that will contain the multi bulk
  * length, which is not known when this function is called. */
-void *addDeferredMultiBulkLength(redisClient *c) {
+void *addDeferredMultiBulkLength(client *c) {
     /* Note that we install the write event here even if the object is not
      * ready to be sent, since we are sure that before returning to the
      * event loop setDeferredMultiBulkLength() will be called. */
@@ -430,7 +430,7 @@ void *addDeferredMultiBulkLength(redisClient *c) {
 }
 
 /* Populate the length object and try gluing it to the next chunk. */
-void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
+void setDeferredMultiBulkLength(client *c, void *node, long length) {
     listNode *ln = (listNode*)node;
     robj *len, *next;
 
@@ -457,7 +457,7 @@ void setDeferredMultiBulkLength(redisClient *c, void *node, long length) {
 }
 
 /* Add a double as a bulk reply */
-void addReplyDouble(redisClient *c, double d) {
+void addReplyDouble(client *c, double d) {
     char dbuf[128], sbuf[128];
     int dlen, slen;
     if (isinf(d)) {
@@ -473,7 +473,7 @@ void addReplyDouble(redisClient *c, double d) {
 
 /* Add a long long as integer reply or bulk len / multi bulk count.
  * Basically this is used to output <prefix><long long><crlf>. */
-void addReplyLongLongWithPrefix(redisClient *c, long long ll, char prefix) {
+void addReplyLongLongWithPrefix(client *c, long long ll, char prefix) {
     char buf[128];
     int len;
 
@@ -495,7 +495,7 @@ void addReplyLongLongWithPrefix(redisClient *c, long long ll, char prefix) {
     addReplyString(c,buf,len+3);
 }
 
-void addReplyLongLong(redisClient *c, long long ll) {
+void addReplyLongLong(client *c, long long ll) {
     if (ll == 0)
         addReply(c,shared.czero);
     else if (ll == 1)
@@ -504,15 +504,15 @@ void addReplyLongLong(redisClient *c, long long ll) {
         addReplyLongLongWithPrefix(c,ll,':');
 }
 
-void addReplyMultiBulkLen(redisClient *c, long length) {
+void addReplyMultiBulkLen(client *c, long length) {
     if (length < REDIS_SHARED_BULKHDR_LEN)
         addReply(c,shared.mbulkhdr[length]);
     else
         addReplyLongLongWithPrefix(c,length,'*');
 }
 
 /* Create the length prefix of a bulk reply, example: $2234 */
-void addReplyBulkLen(redisClient *c, robj *obj) {
+void addReplyBulkLen(client *c, robj *obj) {
     size_t len;
 
     if (sdsEncodedObject(obj)) {
@@ -538,29 +538,29 @@ void addReplyBulkLen(redisClient *c, robj *obj) {
 }
 
 /* Add a Redis Object as a bulk reply */
-void addReplyBulk(redisClient *c, robj *obj) {
+void addReplyBulk(client *c, robj *obj) {
     addReplyBulkLen(c,obj);
     addReply(c,obj);
     addReply(c,shared.crlf);
 }
 
 /* Add a C buffer as bulk reply */
-void addReplyBulkCBuffer(redisClient *c, const void *p, size_t len) {
+void addReplyBulkCBuffer(client *c, const void *p, size_t len) {
     addReplyLongLongWithPrefix(c,len,'$');
     addReplyString(c,p,len);
     addReply(c,shared.crlf);
 }
 
 /* Add sds to reply (takes ownership of sds and frees it) */
-void addReplyBulkSds(redisClient *c, sds s)  {
+void addReplyBulkSds(client *c, sds s)  {
     addReplySds(c,sdscatfmt(sdsempty(),"$%u\r\n",
         (unsigned long)sdslen(s)));
     addReplySds(c,s);
     addReply(c,shared.crlf);
 }
 
 /* Add a C nul term string as bulk reply */
-void addReplyBulkCString(redisClient *c, const char *s) {
+void addReplyBulkCString(client *c, const char *s) {
     if (s == NULL) {
         addReply(c,shared.nullbulk);
     } else {
@@ -569,7 +569,7 @@ void addReplyBulkCString(redisClient *c, const char *s) {
 }
 
 /* Add a long long as a bulk reply */
-void addReplyBulkLongLong(redisClient *c, long long ll) {
+void addReplyBulkLongLong(client *c, long long ll) {
     char buf[64];
     int len;
 
@@ -580,7 +580,7 @@ void addReplyBulkLongLong(redisClient *c, long long ll) {
 /* Copy 'src' client output buffers into 'dst' client output buffers.
  * The function takes care of freeing the old output buffers of the
  * destination client. */
-void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
+void copyClientOutputBuffer(client *dst, client *src) {
     listRelease(dst->reply);
     dst->reply = listDup(src->reply);
     memcpy(dst->buf,src->buf,src->bufpos);
@@ -590,7 +590,7 @@ void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
 
 #define MAX_ACCEPTS_PER_CALL 1000
 static void acceptCommonHandler(int fd, int flags) {
-    redisClient *c;
+    client *c;
     if ((c = createClient(fd)) == NULL) {
         serverLog(REDIS_WARNING,
             "Error registering fd event for the new client: %s (fd=%d)",
@@ -656,7 +656,7 @@ void acceptUnixHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-static void freeClientArgv(redisClient *c) {
+static void freeClientArgv(client *c) {
     int j;
     for (j = 0; j < c->argc; j++)
         decrRefCount(c->argv[j]);
@@ -670,7 +670,7 @@ static void freeClientArgv(redisClient *c) {
 void disconnectSlaves(void) {
     while (listLength(server.slaves)) {
         listNode *ln = listFirst(server.slaves);
-        freeClient((redisClient*)ln->value);
+        freeClient((client*)ln->value);
     }
 }
 
@@ -688,7 +688,7 @@ void replicationHandleMasterDisconnection(void) {
     if (server.masterhost != NULL) disconnectSlaves();
 }
 
-void freeClient(redisClient *c) {
+void freeClient(client *c) {
     listNode *ln;
 
     /* If this is marked as current client unset it */
@@ -804,7 +804,7 @@ void freeClient(redisClient *c) {
  * This function is useful when we need to terminate a client but we are in
  * a context where calling freeClient() is not possible, because the client
  * should be valid for the continuation of the flow of the program. */
-void freeClientAsync(redisClient *c) {
+void freeClientAsync(client *c) {
     if (c->flags & REDIS_CLOSE_ASAP || c->flags & REDIS_LUA_CLIENT) return;
     c->flags |= REDIS_CLOSE_ASAP;
     listAddNodeTail(server.clients_to_close,c);
@@ -813,7 +813,7 @@ void freeClientAsync(redisClient *c) {
 void freeClientsInAsyncFreeQueue(void) {
     while (listLength(server.clients_to_close)) {
         listNode *ln = listFirst(server.clients_to_close);
-        redisClient *c = listNodeValue(ln);
+        client *c = listNodeValue(ln);
 
         c->flags &= ~REDIS_CLOSE_ASAP;
         freeClient(c);
@@ -822,7 +822,7 @@ void freeClientsInAsyncFreeQueue(void) {
 }
 
 void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
-    redisClient *c = privdata;
+    client *c = privdata;
     ssize_t nwritten = 0, totwritten = 0;
     size_t objlen;
     size_t objmem;
@@ -906,7 +906,7 @@ void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask) {
 }
 
 /* resetClient prepare the client to process the next command */
-void resetClient(redisClient *c) {
+void resetClient(client *c) {
     redisCommandProc *prevcmd = c->cmd ? c->cmd->proc : NULL;
 
     freeClientArgv(c);
@@ -919,7 +919,7 @@ void resetClient(redisClient *c) {
         c->flags &= (~REDIS_ASKING);
 }
 
-int processInlineBuffer(redisClient *c) {
+int processInlineBuffer(client *c) {
     char *newline;
     int argc, j;
     sds *argv, aux;
@@ -982,7 +982,7 @@ int processInlineBuffer(redisClient *c) {
 
 /* Helper function. Trims query buffer to make the function that processes
  * multi bulk requests idempotent. */
-static void setProtocolError(redisClient *c, int pos) {
+static void setProtocolError(client *c, int pos) {
     if (server.verbosity <= REDIS_VERBOSE) {
         sds client = catClientInfoString(sdsempty(),c);
         serverLog(REDIS_VERBOSE,
@@ -993,7 +993,7 @@ static void setProtocolError(redisClient *c, int pos) {
     sdsrange(c->querybuf,pos,-1);
 }
 
-int processMultibulkBuffer(redisClient *c) {
+int processMultibulkBuffer(client *c) {
     char *newline = NULL;
     int pos = 0, ok;
     long long ll;
@@ -1131,7 +1131,7 @@ int processMultibulkBuffer(redisClient *c) {
     return REDIS_ERR;
 }
 
-void processInputBuffer(redisClient *c) {
+void processInputBuffer(client *c) {
     server.current_client = c;
     /* Keep processing while there is something in the input buffer */
     while(sdslen(c->querybuf)) {
@@ -1176,7 +1176,7 @@ void processInputBuffer(redisClient *c) {
 }
 
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
-    redisClient *c = (redisClient*) privdata;
+    client *c = (client*) privdata;
     int nread, readlen;
     size_t qblen;
     REDIS_NOTUSED(el);
@@ -1234,7 +1234,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
 
 void getClientsMaxBuffers(unsigned long *longest_output_list,
                           unsigned long *biggest_input_buffer) {
-    redisClient *c;
+    client *c;
     listNode *ln;
     listIter li;
     unsigned long lol = 0, bib = 0;
@@ -1261,7 +1261,7 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
  * On failure the function still populates 'peerid' with the "?:0" string
  * in case you want to relax error checking or need to display something
  * anyway (see anetPeerToString implementation for more info). */
-void genClientPeerId(redisClient *client, char *peerid,
+void genClientPeerId(client *client, char *peerid,
                             size_t peerid_len) {
     if (client->flags & REDIS_UNIX_SOCKET) {
         /* Unix socket client. */
@@ -1276,7 +1276,7 @@ void genClientPeerId(redisClient *client, char *peerid,
  * if client->peerid is NULL, otherwise returning the cached value.
  * The Peer ID never changes during the life of the client, however it
  * is expensive to compute. */
-char *getClientPeerId(redisClient *c) {
+char *getClientPeerId(client *c) {
     char peerid[REDIS_PEER_ID_LEN];
 
     if (c->peerid == NULL) {
@@ -1288,7 +1288,7 @@ char *getClientPeerId(redisClient *c) {
 
 /* Concatenate a string representing the state of a client in an human
  * readable format, into the sds string 's'. */
-sds catClientInfoString(sds s, redisClient *client) {
+sds catClientInfoString(sds s, client *client) {
     char flags[16], events[3], *p;
     int emask;
 
@@ -1341,7 +1341,7 @@ sds catClientInfoString(sds s, redisClient *client) {
 sds getAllClientsInfoString(void) {
     listNode *ln;
     listIter li;
-    redisClient *client;
+    client *client;
     sds o = sdsempty();
 
     o = sdsMakeRoomFor(o,200*listLength(server.clients));
@@ -1354,10 +1354,10 @@ sds getAllClientsInfoString(void) {
     return o;
 }
 
-void clientCommand(redisClient *c) {
+void clientCommand(client *c) {
     listNode *ln;
     listIter li;
-    redisClient *client;
+    client *client;
 
     if (!strcasecmp(c->argv[1]->ptr,"list") && c->argc == 2) {
         /* CLIENT LIST */
@@ -1500,7 +1500,7 @@ void clientCommand(redisClient *c) {
 /* Rewrite the command vector of the client. All the new objects ref count
  * is incremented. The old command vector is freed, and the old objects
  * ref count is decremented. */
-void rewriteClientCommandVector(redisClient *c, int argc, ...) {
+void rewriteClientCommandVector(client *c, int argc, ...) {
     va_list ap;
     int j;
     robj **argv; /* The new argument vector */
@@ -1528,7 +1528,7 @@ void rewriteClientCommandVector(redisClient *c, int argc, ...) {
 }
 
 /* Completely replace the client command vector with the provided one. */
-void replaceClientCommandVector(redisClient *c, int argc, robj **argv) {
+void replaceClientCommandVector(client *c, int argc, robj **argv) {
     freeClientArgv(c);
     zfree(c->argv);
     c->argv = argv;
@@ -1539,7 +1539,7 @@ void replaceClientCommandVector(redisClient *c, int argc, robj **argv) {
 
 /* Rewrite a single item in the command vector.
  * The new val ref count is incremented, and the old decremented. */
-void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
+void rewriteClientCommandArgument(client *c, int i, robj *newval) {
     robj *oldval;
 
     redisAssertWithInfo(c,NULL,i < c->argc);
@@ -1568,7 +1568,7 @@ void rewriteClientCommandArgument(redisClient *c, int i, robj *newval) {
  * Note: this function is very fast so can be called as many time as
  * the caller wishes. The main usage of this function currently is
  * enforcing the client output length limits. */
-unsigned long getClientOutputBufferMemoryUsage(redisClient *c) {
+unsigned long getClientOutputBufferMemoryUsage(client *c) {
     unsigned long list_item_size = sizeof(listNode)+sizeof(robj);
 
     return c->reply_bytes + (list_item_size*listLength(c->reply));
@@ -1582,7 +1582,7 @@ unsigned long getClientOutputBufferMemoryUsage(redisClient *c) {
  * REDIS_CLIENT_TYPE_SLAVE  -> Slave or client executing MONITOR command
  * REDIS_CLIENT_TYPE_PUBSUB -> Client subscribed to Pub/Sub channels
  */
-int getClientType(redisClient *c) {
+int getClientType(client *c) {
     if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR))
         return REDIS_CLIENT_TYPE_SLAVE;
     if (c->flags & REDIS_PUBSUB)
@@ -1612,7 +1612,7 @@ char *getClientTypeName(int class) {
  *
  * Return value: non-zero if the client reached the soft or the hard limit.
  *               Otherwise zero is returned. */
-int checkClientOutputBufferLimits(redisClient *c) {
+int checkClientOutputBufferLimits(client *c) {
     int soft = 0, hard = 0, class;
     unsigned long used_mem = getClientOutputBufferMemoryUsage(c);
 
@@ -1653,7 +1653,7 @@ int checkClientOutputBufferLimits(redisClient *c) {
  * Note: we need to close the client asynchronously because this function is
  * called from contexts where the client can't be freed safely, i.e. from the
  * lower level functions pushing data inside the client output buffers. */
-void asyncCloseClientOnOutputBufferLimitReached(redisClient *c) {
+void asyncCloseClientOnOutputBufferLimitReached(client *c) {
     redisAssert(c->reply_bytes < SIZE_MAX-(1024*64));
     if (c->reply_bytes == 0 || c->flags & REDIS_CLOSE_ASAP) return;
     if (checkClientOutputBufferLimits(c)) {
@@ -1673,7 +1673,7 @@ void flushSlavesOutputBuffers(void) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = listNodeValue(ln);
+        client *slave = listNodeValue(ln);
         int events;
 
         events = aeGetFileEvents(server.el,slave->fd);
@@ -1717,7 +1717,7 @@ int clientsArePaused(void) {
     {
         listNode *ln;
         listIter li;
-        redisClient *c;
+        client *c;
 
         server.clients_paused = 0;
 