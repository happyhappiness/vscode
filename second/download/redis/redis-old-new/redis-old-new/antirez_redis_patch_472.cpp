@@ -69,7 +69,7 @@ char *replicationGetSlaveName(client *c) {
 /* ---------------------------------- MASTER -------------------------------- */
 
 void createReplicationBacklog(void) {
-    redisAssert(server.repl_backlog == NULL);
+    serverAssert(server.repl_backlog == NULL);
     server.repl_backlog = zmalloc(server.repl_backlog_size);
     server.repl_backlog_histlen = 0;
     server.repl_backlog_idx = 0;
@@ -113,7 +113,7 @@ void resizeReplicationBacklog(long long newsize) {
 }
 
 void freeReplicationBacklog(void) {
-    redisAssert(listLength(server.slaves) == 0);
+    serverAssert(listLength(server.slaves) == 0);
     zfree(server.repl_backlog);
     server.repl_backlog = NULL;
 }
@@ -175,7 +175,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     if (server.repl_backlog == NULL && listLength(slaves) == 0) return;
 
     /* We can't have slaves attached and no backlog. */
-    redisAssert(!(listLength(slaves) != 0 && server.repl_backlog == NULL));
+    serverAssert(!(listLength(slaves) != 0 && server.repl_backlog == NULL));
 
     /* Send SELECT command to every slave if needed. */
     if (server.slaveseldb != dictid) {
@@ -821,7 +821,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
 /* Abort the async download of the bulk dataset while SYNC-ing with master */
 void replicationAbortSyncTransfer(void) {
-    redisAssert(server.repl_state == REDIS_REPL_TRANSFER);
+    serverAssert(server.repl_state == REDIS_REPL_TRANSFER);
 
     aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
     close(server.repl_transfer_s);
@@ -1411,7 +1411,7 @@ int connectWithMaster(void) {
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    redisAssert(server.repl_state == REDIS_REPL_CONNECTING ||
+    serverAssert(server.repl_state == REDIS_REPL_CONNECTING ||
                 server.repl_state == REDIS_REPL_RECEIVE_PONG);
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
@@ -1603,13 +1603,13 @@ void replicationSendAck(void) {
 void replicationCacheMaster(client *c) {
     listNode *ln;
 
-    redisAssert(server.master != NULL && server.cached_master == NULL);
+    serverAssert(server.master != NULL && server.cached_master == NULL);
     serverLog(REDIS_NOTICE,"Caching the disconnected master state.");
 
     /* Remove from the list of clients, we don't want this client to be
      * listed by CLIENT LIST or processed in any way by batch operations. */
     ln = listSearchKey(server.clients,c);
-    redisAssert(ln != NULL);
+    serverAssert(ln != NULL);
     listDelNode(server.clients,ln);
 
     /* Save the master. Server.master will be set to null later by
@@ -1774,14 +1774,14 @@ void replicationScriptCacheAdd(sds sha1) {
         sds oldest = listNodeValue(ln);
 
         retval = dictDelete(server.repl_scriptcache_dict,oldest);
-        redisAssert(retval == DICT_OK);
+        serverAssert(retval == DICT_OK);
         listDelNode(server.repl_scriptcache_fifo,ln);
     }
 
     /* Add current. */
     retval = dictAdd(server.repl_scriptcache_dict,key,NULL);
     listAddNodeHead(server.repl_scriptcache_fifo,key);
-    redisAssert(retval == DICT_OK);
+    serverAssert(retval == DICT_OK);
 }
 
 /* Returns non-zero if the specified entry exists inside the cache, that is,
@@ -1880,7 +1880,7 @@ void waitCommand(client *c) {
  * instead. */
 void unblockClientWaitingReplicas(client *c) {
     listNode *ln = listSearchKey(server.clients_waiting_acks,c);
-    redisAssert(ln != NULL);
+    serverAssert(ln != NULL);
     listDelNode(server.clients_waiting_acks,ln);
 }
 