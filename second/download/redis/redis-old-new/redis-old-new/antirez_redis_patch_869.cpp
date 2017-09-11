@@ -118,6 +118,7 @@ redisClient *createClient(int fd) {
     c->watched_keys = listCreate();
     c->pubsub_channels = dictCreate(&setDictType,NULL);
     c->pubsub_patterns = listCreate();
+    c->peerid = NULL;
     listSetFreeMethod(c->pubsub_patterns,decrRefCountVoid);
     listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
     if (fd != -1) listAddNodeTail(server.clients,c);
@@ -763,6 +764,7 @@ void freeClient(redisClient *c) {
     if (c->name) decrRefCount(c->name);
     zfree(c->argv);
     freeClientMultiState(c);
+    sdsfree(c->peerid);
     zfree(c);
 }
 
@@ -946,7 +948,7 @@ int processInlineBuffer(redisClient *c) {
  * multi bulk requests idempotent. */
 static void setProtocolError(redisClient *c, int pos) {
     if (server.verbosity >= REDIS_VERBOSE) {
-        sds client = getClientInfoString(c);
+        sds client = catClientInfoString(sdsempty(),c);
         redisLog(REDIS_VERBOSE,
             "Protocol error from client: %s", client);
         sdsfree(client);
@@ -1184,7 +1186,7 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
-        sds ci = getClientInfoString(c), bytes = sdsempty();
+        sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();
 
         bytes = sdscatrepr(bytes,c->querybuf,64);
         redisLog(REDIS_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
@@ -1215,7 +1217,7 @@ void getClientsMaxBuffers(unsigned long *longest_output_list,
     *biggest_input_buffer = bib;
 }
 
-/* This is a helper function for getClientPeerId().
+/* This is a helper function for genClientPeerId().
  * It writes the specified ip/port to "peerid" as a null termiated string
  * in the form ip:port if ip does not contain ":" itself, otherwise
  * [ip]:port format is used (for IPv6 addresses basically). */
@@ -1239,7 +1241,7 @@ void formatPeerId(char *peerid, size_t peerid_len, char *ip, int port) {
  * On failure the function still populates 'peerid' with the "?:0" string
  * in case you want to relax error checking or need to display something
  * anyway (see anetPeerToString implementation for more info). */
-int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
+int genClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
     char ip[REDIS_IP_STR_LEN];
     int port;
 
@@ -1255,12 +1257,26 @@ int getClientPeerId(redisClient *client, char *peerid, size_t peerid_len) {
     }
 }
 
-/* Turn a Redis client into an sds string representing its state. */
-sds getClientInfoString(redisClient *client) {
-    char peerid[REDIS_PEER_ID_LEN], flags[16], events[3], *p;
+/* This function returns the client peer id, by creating and caching it
+ * if client->perrid is NULL, otherwise returning the cached value.
+ * The Peer ID never changes during the life of the client, however it
+ * is expensive to compute. */
+char *getClientPeerId(redisClient *c) {
+    char peerid[REDIS_PEER_ID_LEN];
+
+    if (c->peerid == NULL) {
+        genClientPeerId(c,peerid,sizeof(peerid));
+        c->peerid = sdsnew(peerid);
+    }
+    return c->peerid;
+}
+
+/* Concatenate a string representing the state of a client in an human
+ * readable format, into the sds string 's'. */
+sds catClientInfoString(sds s, redisClient *client) {
+    char flags[16], events[3], *p;
     int emask;
 
-    getClientPeerId(client,peerid,sizeof(peerid));
     p = flags;
     if (client->flags & REDIS_SLAVE) {
         if (client->flags & REDIS_MONITOR)
@@ -1285,9 +1301,9 @@ sds getClientInfoString(redisClient *client) {
     if (emask & AE_READABLE) *p++ = 'r';
     if (emask & AE_WRITABLE) *p++ = 'w';
     *p = '\0';
-    return sdscatfmt(sdsempty(),
+    return sdscatfmt(s,
         "addr=%s fd=%i name=%s age=%I idle=%I flags=%s db=%i sub=%i psub=%i multi=%i qbuf=%U qbuf-free=%U obl=%U oll=%U omem=%U events=%s cmd=%s",
-        peerid,
+        getClientPeerId(client),
         client->fd,
         client->name ? (char*)client->name->ptr : "",
         (long long)(server.unixtime - client->ctime),
@@ -1312,14 +1328,11 @@ sds getAllClientsInfoString(void) {
     redisClient *client;
     sds o = sdsempty();
 
+    o = sdsMakeRoomFor(o,200*listLength(server.clients));
     listRewind(server.clients,&li);
     while ((ln = listNext(&li)) != NULL) {
-        sds cs;
-
         client = listNodeValue(ln);
-        cs = getClientInfoString(client);
-        o = sdscatsds(o,cs);
-        sdsfree(cs);
+        o = catClientInfoString(o,client);
         o = sdscatlen(o,"\n",1);
     }
     return o;
@@ -1337,11 +1350,10 @@ void clientCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"kill") && c->argc == 3) {
         listRewind(server.clients,&li);
         while ((ln = listNext(&li)) != NULL) {
-            char peerid[REDIS_PEER_ID_LEN];
+            char *peerid;
 
             client = listNodeValue(ln);
-            if (getClientPeerId(client,peerid,sizeof(peerid)) == REDIS_ERR)
-                continue;
+            peerid = getClientPeerId(client);
             if (strcmp(peerid,c->argv[2]->ptr) == 0) {
                 addReply(c,shared.ok);
                 if (c == client) {
@@ -1547,7 +1559,7 @@ void asyncCloseClientOnOutputBufferLimitReached(redisClient *c) {
     redisAssert(c->reply_bytes < ULONG_MAX-(1024*64));
     if (c->reply_bytes == 0 || c->flags & REDIS_CLOSE_ASAP) return;
     if (checkClientOutputBufferLimits(c)) {
-        sds client = getClientInfoString(c);
+        sds client = catClientInfoString(sdsempty(),c);
 
         freeClientAsync(c);
         redisLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);