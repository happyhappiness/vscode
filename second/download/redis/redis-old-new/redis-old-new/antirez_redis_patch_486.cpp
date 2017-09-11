@@ -32,13 +32,13 @@
 /* ================================ MULTI/EXEC ============================== */
 
 /* Client state initialization for MULTI/EXEC */
-void initClientMultiState(redisClient *c) {
+void initClientMultiState(client *c) {
     c->mstate.commands = NULL;
     c->mstate.count = 0;
 }
 
 /* Release all the resources associated with MULTI/EXEC state */
-void freeClientMultiState(redisClient *c) {
+void freeClientMultiState(client *c) {
     int j;
 
     for (j = 0; j < c->mstate.count; j++) {
@@ -53,7 +53,7 @@ void freeClientMultiState(redisClient *c) {
 }
 
 /* Add a new command into the MULTI commands queue */
-void queueMultiCommand(redisClient *c) {
+void queueMultiCommand(client *c) {
     multiCmd *mc;
     int j;
 
@@ -69,7 +69,7 @@ void queueMultiCommand(redisClient *c) {
     c->mstate.count++;
 }
 
-void discardTransaction(redisClient *c) {
+void discardTransaction(client *c) {
     freeClientMultiState(c);
     initClientMultiState(c);
     c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
@@ -78,12 +78,12 @@ void discardTransaction(redisClient *c) {
 
 /* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
  * Should be called every time there is an error while queueing a command. */
-void flagTransaction(redisClient *c) {
+void flagTransaction(client *c) {
     if (c->flags & REDIS_MULTI)
         c->flags |= REDIS_DIRTY_EXEC;
 }
 
-void multiCommand(redisClient *c) {
+void multiCommand(client *c) {
     if (c->flags & REDIS_MULTI) {
         addReplyError(c,"MULTI calls can not be nested");
         return;
@@ -92,7 +92,7 @@ void multiCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
-void discardCommand(redisClient *c) {
+void discardCommand(client *c) {
     if (!(c->flags & REDIS_MULTI)) {
         addReplyError(c,"DISCARD without MULTI");
         return;
@@ -103,15 +103,15 @@ void discardCommand(redisClient *c) {
 
 /* Send a MULTI command to all the slaves and AOF file. Check the execCommand
  * implementation for more information. */
-void execCommandPropagateMulti(redisClient *c) {
+void execCommandPropagateMulti(client *c) {
     robj *multistring = createStringObject("MULTI",5);
 
     propagate(server.multiCommand,c->db->id,&multistring,1,
               REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);
     decrRefCount(multistring);
 }
 
-void execCommand(redisClient *c) {
+void execCommand(client *c) {
     int j;
     robj **orig_argv;
     int orig_argc;
@@ -199,7 +199,7 @@ typedef struct watchedKey {
 } watchedKey;
 
 /* Watch for the specified key */
-void watchForKey(redisClient *c, robj *key) {
+void watchForKey(client *c, robj *key) {
     list *clients = NULL;
     listIter li;
     listNode *ln;
@@ -230,7 +230,7 @@ void watchForKey(redisClient *c, robj *key) {
 
 /* Unwatch all the keys watched by this client. To clean the EXEC dirty
  * flag is up to the caller. */
-void unwatchAllKeys(redisClient *c) {
+void unwatchAllKeys(client *c) {
     listIter li;
     listNode *ln;
 
@@ -271,7 +271,7 @@ void touchWatchedKey(redisDb *db, robj *key) {
     /* Check if we are already watching for this key */
     listRewind(clients,&li);
     while((ln = listNext(&li))) {
-        redisClient *c = listNodeValue(ln);
+        client *c = listNodeValue(ln);
 
         c->flags |= REDIS_DIRTY_CAS;
     }
@@ -288,7 +288,7 @@ void touchWatchedKeysOnFlush(int dbid) {
     /* For every client, check all the waited keys */
     listRewind(server.clients,&li1);
     while((ln = listNext(&li1))) {
-        redisClient *c = listNodeValue(ln);
+        client *c = listNodeValue(ln);
         listRewind(c->watched_keys,&li2);
         while((ln = listNext(&li2))) {
             watchedKey *wk = listNodeValue(ln);
@@ -304,7 +304,7 @@ void touchWatchedKeysOnFlush(int dbid) {
     }
 }
 
-void watchCommand(redisClient *c) {
+void watchCommand(client *c) {
     int j;
 
     if (c->flags & REDIS_MULTI) {
@@ -316,7 +316,7 @@ void watchCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
-void unwatchCommand(redisClient *c) {
+void unwatchCommand(client *c) {
     unwatchAllKeys(c);
     c->flags &= (~REDIS_DIRTY_CAS);
     addReply(c,shared.ok);