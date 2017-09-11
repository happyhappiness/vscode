@@ -44,7 +44,7 @@ size_t sdsZmallocSize(sds s) {
 /* Return the amount of memory used by the sds string at object->ptr
  * for a string object. */
 size_t getStringObjectSdsUsedMemory(robj *o) {
-    redisAssertWithInfo(NULL,o,o->type == OBJ_STRING);
+    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
     switch(o->encoding) {
     case OBJ_ENCODING_RAW: return sdsZmallocSize(o->ptr);
     case OBJ_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
@@ -186,7 +186,7 @@ int prepareClientToWrite(client *c) {
 robj *dupLastObjectIfNeeded(list *reply) {
     robj *new, *cur;
     listNode *ln;
-    redisAssert(listLength(reply) > 0);
+    serverAssert(listLength(reply) > 0);
     ln = listLast(reply);
     cur = listNodeValue(ln);
     if (cur->refcount > 1) {
@@ -748,15 +748,15 @@ void freeClient(client *c) {
     /* Remove from the list of clients */
     if (c->fd != -1) {
         ln = listSearchKey(server.clients,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(server.clients,ln);
     }
 
     /* When client was just unblocked because of a blocking operation,
      * remove it from the list of unblocked clients. */
     if (c->flags & REDIS_UNBLOCKED) {
         ln = listSearchKey(server.unblocked_clients,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(server.unblocked_clients,ln);
     }
 
@@ -769,7 +769,7 @@ void freeClient(client *c) {
         }
         list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
         ln = listSearchKey(l,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(l,ln);
         /* We need to remember the time when we started to have zero
          * attached slaves, as after some time we'll free the replication
@@ -787,7 +787,7 @@ void freeClient(client *c) {
      * from the queue. */
     if (c->flags & REDIS_CLOSE_ASAP) {
         ln = listSearchKey(server.clients_to_close,c);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         listDelNode(server.clients_to_close,ln);
     }
 
@@ -1000,7 +1000,7 @@ int processMultibulkBuffer(client *c) {
 
     if (c->multibulklen == 0) {
         /* The client should have been reset */
-        redisAssertWithInfo(c,NULL,c->argc == 0);
+        serverAssertWithInfo(c,NULL,c->argc == 0);
 
         /* Multi bulk length cannot be read without a \r\n */
         newline = strchr(c->querybuf,'\r');
@@ -1018,7 +1018,7 @@ int processMultibulkBuffer(client *c) {
 
         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
-        redisAssertWithInfo(c,NULL,c->querybuf[0] == '*');
+        serverAssertWithInfo(c,NULL,c->querybuf[0] == '*');
         ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
         if (!ok || ll > 1024*1024) {
             addReplyError(c,"Protocol error: invalid multibulk length");
@@ -1039,7 +1039,7 @@ int processMultibulkBuffer(client *c) {
         c->argv = zmalloc(sizeof(robj*)*c->multibulklen);
     }
 
-    redisAssertWithInfo(c,NULL,c->multibulklen > 0);
+    serverAssertWithInfo(c,NULL,c->multibulklen > 0);
     while(c->multibulklen) {
         /* Read bulk length if unknown */
         if (c->bulklen == -1) {
@@ -1523,7 +1523,7 @@ void rewriteClientCommandVector(client *c, int argc, ...) {
     c->argv = argv;
     c->argc = argc;
     c->cmd = lookupCommandOrOriginal(c->argv[0]->ptr);
-    redisAssertWithInfo(c,NULL,c->cmd != NULL);
+    serverAssertWithInfo(c,NULL,c->cmd != NULL);
     va_end(ap);
 }
 
@@ -1534,15 +1534,15 @@ void replaceClientCommandVector(client *c, int argc, robj **argv) {
     c->argv = argv;
     c->argc = argc;
     c->cmd = lookupCommandOrOriginal(c->argv[0]->ptr);
-    redisAssertWithInfo(c,NULL,c->cmd != NULL);
+    serverAssertWithInfo(c,NULL,c->cmd != NULL);
 }
 
 /* Rewrite a single item in the command vector.
  * The new val ref count is incremented, and the old decremented. */
 void rewriteClientCommandArgument(client *c, int i, robj *newval) {
     robj *oldval;
 
-    redisAssertWithInfo(c,NULL,i < c->argc);
+    serverAssertWithInfo(c,NULL,i < c->argc);
     oldval = c->argv[i];
     c->argv[i] = newval;
     incrRefCount(newval);
@@ -1551,7 +1551,7 @@ void rewriteClientCommandArgument(client *c, int i, robj *newval) {
     /* If this is the command name make sure to fix c->cmd. */
     if (i == 0) {
         c->cmd = lookupCommandOrOriginal(c->argv[0]->ptr);
-        redisAssertWithInfo(c,NULL,c->cmd != NULL);
+        serverAssertWithInfo(c,NULL,c->cmd != NULL);
     }
 }
 
@@ -1654,7 +1654,7 @@ int checkClientOutputBufferLimits(client *c) {
  * called from contexts where the client can't be freed safely, i.e. from the
  * lower level functions pushing data inside the client output buffers. */
 void asyncCloseClientOnOutputBufferLimitReached(client *c) {
-    redisAssert(c->reply_bytes < SIZE_MAX-(1024*64));
+    serverAssert(c->reply_bytes < SIZE_MAX-(1024*64));
     if (c->reply_bytes == 0 || c->flags & REDIS_CLOSE_ASAP) return;
     if (checkClientOutputBufferLimits(c)) {
         sds client = catClientInfoString(sdsempty(),c);