  * should modify unblockClient() and replyToBlockedClientTimedOut() in order
  * to handle the btype-specific behavior of this two functions.
  * If the blocking operation waits for certain keys to change state, the
  * clusterRedirectBlockedClientIfNeeded() function should also be updated.
  */
 
-#include "redis.h"
+#include "server.h"
 
 /* Get a timeout value from an object and store it into 'timeout'.
  * The final timeout is always stored as milliseconds as a time where the
  * timeout will expire, however the parsing is performed according to
  * the 'unit' that can be seconds or milliseconds.
  *
  * Note that if the timeout is zero (usually from the point of view of
  * commands API this means no timeout) the value stored into 'timeout'
  * is zero. */
-int getTimeoutFromObjectOrReply(redisClient *c, robj *object, mstime_t *timeout, int unit) {
+int getTimeoutFromObjectOrReply(client *c, robj *object, mstime_t *timeout, int unit) {
     long long tval;
 
     if (getLongLongFromObjectOrReply(c,object,&tval,
-        "timeout is not an integer or out of range") != REDIS_OK)
-        return REDIS_ERR;
+        "timeout is not an integer or out of range") != C_OK)
+        return C_ERR;
 
     if (tval < 0) {
         addReplyError(c,"timeout is negative");
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (tval > 0) {
         if (unit == UNIT_SECONDS) tval *= 1000;
         tval += mstime();
     }
     *timeout = tval;
 
-    return REDIS_OK;
+    return C_OK;
 }
 
-/* Block a client for the specific operation type. Once the REDIS_BLOCKED
+/* Block a client for the specific operation type. Once the CLIENT_BLOCKED
  * flag is set client query buffer is not longer processed, but accumulated,
  * and will be processed when the client is unblocked. */
-void blockClient(redisClient *c, int btype) {
-    c->flags |= REDIS_BLOCKED;
+void blockClient(client *c, int btype) {
+    c->flags |= CLIENT_BLOCKED;
     c->btype = btype;
     server.bpop_blocked_clients++;
 }
 
 /* This function is called in the beforeSleep() function of the event loop
  * in order to process the pending input buffer of clients that were
  * unblocked after a blocking operation. */
 void processUnblockedClients(void) {
     listNode *ln;
-    redisClient *c;
+    client *c;
 
     while (listLength(server.unblocked_clients)) {
         ln = listFirst(server.unblocked_clients);
-        redisAssert(ln != NULL);
+        serverAssert(ln != NULL);
         c = ln->value;
         listDelNode(server.unblocked_clients,ln);
-        c->flags &= ~REDIS_UNBLOCKED;
+        c->flags &= ~CLIENT_UNBLOCKED;
 
-        /* Process remaining data in the input buffer. */
-        if (c->querybuf && sdslen(c->querybuf) > 0) {
-            server.current_client = c;
-            processInputBuffer(c);
-            server.current_client = NULL;
+        /* Process remaining data in the input buffer, unless the client
+         * is blocked again. Actually processInputBuffer() checks that the
+         * client is not blocked before to proceed, but things may change and
+         * the code is conceptually more correct this way. */
+        if (!(c->flags & CLIENT_BLOCKED)) {
+            if (c->querybuf && sdslen(c->querybuf) > 0) {
+                processInputBuffer(c);
+            }
         }
     }
 }
 
 /* Unblock a client calling the right function depending on the kind
  * of operation the client is blocking for. */
-void unblockClient(redisClient *c) {
-    if (c->btype == REDIS_BLOCKED_LIST) {
+void unblockClient(client *c) {
+    if (c->btype == BLOCKED_LIST) {
         unblockClientWaitingData(c);
-    } else if (c->btype == REDIS_BLOCKED_WAIT) {
+    } else if (c->btype == BLOCKED_WAIT) {
         unblockClientWaitingReplicas(c);
     } else {
-        redisPanic("Unknown btype in unblockClient().");
+        serverPanic("Unknown btype in unblockClient().");
     }
     /* Clear the flags, and put the client in the unblocked list so that
      * we'll process new commands in its query buffer ASAP. */
-    c->flags &= ~REDIS_BLOCKED;
-    c->flags |= REDIS_UNBLOCKED;
-    c->btype = REDIS_BLOCKED_NONE;
+    c->flags &= ~CLIENT_BLOCKED;
+    c->btype = BLOCKED_NONE;
     server.bpop_blocked_clients--;
-    listAddNodeTail(server.unblocked_clients,c);
+    /* The client may already be into the unblocked list because of a previous
+     * blocking operation, don't add back it into the list multiple times. */
+    if (!(c->flags & CLIENT_UNBLOCKED)) {
+        c->flags |= CLIENT_UNBLOCKED;
+        listAddNodeTail(server.unblocked_clients,c);
+    }
 }
 
 /* This function gets called when a blocked client timed out in order to
  * send it a reply of some kind. */
-void replyToBlockedClientTimedOut(redisClient *c) {
-    if (c->btype == REDIS_BLOCKED_LIST) {
+void replyToBlockedClientTimedOut(client *c) {
+    if (c->btype == BLOCKED_LIST) {
         addReply(c,shared.nullmultibulk);
-    } else if (c->btype == REDIS_BLOCKED_WAIT) {
+    } else if (c->btype == BLOCKED_WAIT) {
         addReplyLongLong(c,replicationCountAcksByOffset(c->bpop.reploffset));
     } else {
-        redisPanic("Unknown btype in replyToBlockedClientTimedOut().");
+        serverPanic("Unknown btype in replyToBlockedClientTimedOut().");
     }
 }
 
 /* Mass-unblock clients because something changed in the instance that makes
  * blocking no longer safe. For example clients blocked in list operations
  * in an instance which turns from master to slave is unsafe, so this function
