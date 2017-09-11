@@ -4768,10 +4768,10 @@ void readwriteCommand(redisClient *c) {
  * belonging to the same slot, but the slot is not stable (in migration or
  * importing state, likely because a resharding is in progress).
  *
- * REDIS_CLUSTER_REDIR_DOWN if the request addresses a slot which is not
- * bound to any node. In this case the cluster global state should be already
- * "down" but it is fragile to rely on the update of the global state, so
- * we also handle it here. */
+ * REDIS_CLUSTER_REDIR_DOWN_UNBOUND if the request addresses a slot which is
+ * not bound to any node. In this case the cluster global state should be
+ * already "down" but it is fragile to rely on the update of the global state,
+ * so we also handle it here. */
 clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **argv, int argc, int *hashslot, int *error_code) {
     clusterNode *n = NULL;
     robj *firstkey = NULL;
@@ -4833,7 +4833,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
                 if (n == NULL) {
                     getKeysFreeResult(keyindex);
                     if (error_code)
-                        *error_code = REDIS_CLUSTER_REDIR_DOWN;
+                        *error_code = REDIS_CLUSTER_REDIR_DOWN_UNBOUND;
                     return NULL;
                 }
 
@@ -4925,3 +4925,83 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     if (n != myself && error_code) *error_code = REDIS_CLUSTER_REDIR_MOVED;
     return n;
 }
+
+/* Send the client the right redirection code, according to error_code
+ * that should be set to one of REDIS_CLUSTER_REDIR_* macros.
+ *
+ * If REDIS_CLUSTER_REDIR_ASK or REDIS_CLUSTER_REDIR_MOVED error codes
+ * are used, then the node 'n' should not be NULL, but should be the
+ * node we want to mention in the redirection. Moreover hashslot should
+ * be set to the hash slot that caused the redirection. */
+void clusterRedirectClient(redisClient *c, clusterNode *n, int hashslot, int error_code) {
+    if (error_code == REDIS_CLUSTER_REDIR_CROSS_SLOT) {
+        addReplySds(c,sdsnew("-CROSSSLOT Keys in request don't hash to the same slot\r\n"));
+    } else if (error_code == REDIS_CLUSTER_REDIR_UNSTABLE) {
+        /* The request spawns mutliple keys in the same slot,
+         * but the slot is not "stable" currently as there is
+         * a migration or import in progress. */
+        addReplySds(c,sdsnew("-TRYAGAIN Multiple keys request during rehashing of slot\r\n"));
+    } else if (error_code == REDIS_CLUSTER_REDIR_DOWN_STATE) {
+        addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down\r\n"));
+    } else if (error_code == REDIS_CLUSTER_REDIR_DOWN_UNBOUND) {
+        addReplySds(c,sdsnew("-CLUSTERDOWN Hash slot not served\r\n"));
+    } else if (error_code == REDIS_CLUSTER_REDIR_MOVED ||
+               error_code == REDIS_CLUSTER_REDIR_ASK)
+    {
+        addReplySds(c,sdscatprintf(sdsempty(),
+            "-%s %d %s:%d\r\n",
+            (error_code == REDIS_CLUSTER_REDIR_ASK) ? "ASK" : "MOVED",
+            hashslot,n->ip,n->port));
+    } else {
+        redisPanic("getNodeByQuery() unknown error.");
+    }
+}
+
+/* This function is called by the function processing clients incrementally
+ * to detect timeouts, in order to handle the following case:
+ *
+ * 1) A client blocks with BLPOP or similar blocking operation.
+ * 2) The master migrates the hash slot elsewhere or turns into a slave.
+ * 3) The client may remain blocked forever (or up to the max timeout time)
+ *    waiting for a key change that will never happen.
+ *
+ * If the client is found to be blocked into an hash slot this node no
+ * longer handles, the client is sent a redirection error, and the function
+ * returns 1. Otherwise 0 is returned and no operation is performed. */
+int clusterRedirectBlockedClientIfNeeded(redisClient *c) {
+    if (c->flags & REDIS_BLOCKED && c->btype == REDIS_BLOCKED_LIST) {
+        dictEntry *de;
+        dictIterator *di;
+
+        /* If the cluster is down, unblock the client with the right error. */
+        if (server.cluster->state == REDIS_CLUSTER_FAIL) {
+            clusterRedirectClient(c,NULL,0,REDIS_CLUSTER_REDIR_DOWN_STATE);
+            return 1;
+        }
+
+        di = dictGetIterator(c->bpop.keys);
+        while((de = dictNext(di)) != NULL) {
+            robj *key = dictGetKey(de);
+            int slot = keyHashSlot((char*)key->ptr, sdslen(key->ptr));
+            clusterNode *node = server.cluster->slots[slot];
+
+            /* We send an error and unblock the client if:
+             * 1) The slot is unassigned, emitting a cluster down error.
+             * 2) The slot is not handled by this node, nor being imported. */
+            if (node != myself &&
+                server.cluster->importing_slots_from[slot] == NULL)
+            {
+                if (node == NULL) {
+                    clusterRedirectClient(c,NULL,0,
+                        REDIS_CLUSTER_REDIR_DOWN_UNBOUND);
+                } else {
+                    clusterRedirectClient(c,node,slot,
+                        REDIS_CLUSTER_REDIR_MOVED);
+                }
+                return 1;
+            }
+        }
+        dictReleaseIterator(di);
+    }
+    return 0;
+}