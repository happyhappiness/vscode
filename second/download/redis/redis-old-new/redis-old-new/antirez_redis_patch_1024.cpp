@@ -778,7 +778,7 @@ void rpoplpushCommand(redisClient *c) {
 
 /* Set a client in blocking mode for the specified key, with the specified
  * timeout */
-void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout, robj *target) {
+void blockForKeys(redisClient *c, robj **keys, int numkeys, mstime_t timeout, robj *target) {
     dictEntry *de;
     list *l;
     int j;
@@ -808,13 +808,11 @@ void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout, robj
         }
         listAddNodeTail(l,c);
     }
-
-    /* Mark the client as a blocked client */
-    c->flags |= REDIS_BLOCKED;
-    server.bpop_blocked_clients++;
+    blockClient(c,REDIS_BLOCKED_LIST);
 }
 
-/* Unblock a client that's waiting in a blocking operation such as BLPOP */
+/* Unblock a client that's waiting in a blocking operation such as BLPOP.
+ * You should never call this function directly, but unblockClient() instead. */
 void unblockClientWaitingData(redisClient *c) {
     dictEntry *de;
     dictIterator *di;
@@ -842,10 +840,6 @@ void unblockClientWaitingData(redisClient *c) {
         decrRefCount(c->bpop.target);
         c->bpop.target = NULL;
     }
-    c->flags &= ~REDIS_BLOCKED;
-    c->flags |= REDIS_UNBLOCKED;
-    server.bpop_blocked_clients--;
-    listAddNodeTail(server.unblocked_clients,c);
 }
 
 /* If the specified key has clients blocked waiting for list pushes, this
@@ -1000,10 +994,10 @@ void handleClientsBlockedOnLists(void) {
 
                         if (value) {
                             /* Protect receiver->bpop.target, that will be
-                             * freed by the next unblockClientWaitingData()
+                             * freed by the next unblockClient()
                              * call. */
                             if (dstkey) incrRefCount(dstkey);
-                            unblockClientWaitingData(receiver);
+                            unblockClient(receiver);
 
                             if (serveClientBlockedOnList(receiver,
                                 rl->key,dstkey,rl->db,value,
@@ -1036,32 +1030,14 @@ void handleClientsBlockedOnLists(void) {
     }
 }
 
-int getTimeoutFromObjectOrReply(redisClient *c, robj *object, time_t *timeout) {
-    long tval;
-
-    if (getLongFromObjectOrReply(c,object,&tval,
-        "timeout is not an integer or out of range") != REDIS_OK)
-        return REDIS_ERR;
-
-    if (tval < 0) {
-        addReplyError(c,"timeout is negative");
-        return REDIS_ERR;
-    }
-
-    if (tval > 0) tval += server.unixtime;
-    *timeout = tval;
-
-    return REDIS_OK;
-}
-
 /* Blocking RPOP/LPOP */
 void blockingPopGenericCommand(redisClient *c, int where) {
     robj *o;
-    time_t timeout;
+    mstime_t timeout;
     int j;
 
-    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout) != REDIS_OK)
-        return;
+    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout,UNIT_SECONDS)
+        != REDIS_OK) return;
 
     for (j = 1; j < c->argc-1; j++) {
         o = lookupKeyWrite(c->db,c->argv[j]);
@@ -1120,10 +1096,10 @@ void brpopCommand(redisClient *c) {
 }
 
 void brpoplpushCommand(redisClient *c) {
-    time_t timeout;
+    mstime_t timeout;
 
-    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout) != REDIS_OK)
-        return;
+    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout,UNIT_SECONDS)
+        != REDIS_OK) return;
 
     robj *key = lookupKeyWrite(c->db, c->argv[1]);
 