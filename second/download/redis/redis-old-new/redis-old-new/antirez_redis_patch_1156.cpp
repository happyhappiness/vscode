@@ -888,7 +888,23 @@ int clusterProcessPacket(clusterLink *link) {
         }
 
         /* Update our info about the node */
-        if (link->node) link->node->pong_received = time(NULL);
+        if (link->node && type == CLUSTERMSG_TYPE_PONG) {
+            link->node->pong_received = time(NULL);
+            link->node->ping_sent = 0;
+
+            /* The PFAIL condition can be reversed without external
+             * help if it is not transitive (that is, if it does not
+             * turn into a FAIL state).
+             *
+             * The FAIL condition is also reversible under specific
+             * conditions detected by clearNodeFailureIfNeeded(). */
+            if (link->node->flags & REDIS_NODE_PFAIL) {
+                link->node->flags &= ~REDIS_NODE_PFAIL;
+                update_state = 1;
+            } else if (link->node->flags & REDIS_NODE_FAIL) {
+                clearNodeFailureIfNeeded(link->node);
+            }
+        }
 
         /* Update master/slave state */
         if (sender) {
@@ -1502,8 +1518,8 @@ void clusterCron(void) {
     dictIterator *di;
     dictEntry *de;
     int j, update_state = 0;
-    time_t min_ping_sent = 0;
-    clusterNode *min_ping_node = NULL;
+    time_t min_pong = 0;
+    clusterNode *min_pong_node = NULL;
 
     /* Check if we have disconnected nodes and re-establish the connection. */
     di = dictGetIterator(server.cluster->nodes);
@@ -1522,7 +1538,10 @@ void clusterCron(void) {
             link->fd = fd;
             node->link = link;
             aeCreateFileEvent(server.el,link->fd,AE_READABLE,clusterReadHandler,link);
-            /* If the node is flagged as MEET, we send a MEET message instead
+            /* Queue a PING in the new connection ASAP: this is crucial
+             * to avoid false positives in failure detection.
+             *
+             * If the node is flagged as MEET, we send a MEET message instead
              * of a PING one, to force the receiver to add us in its node
              * table. */
             clusterSendPing(link, node->flags & REDIS_NODE_MEET ?
@@ -1540,21 +1559,22 @@ void clusterCron(void) {
     dictReleaseIterator(di);
 
     /* Ping some random node. Check a few random nodes and ping the one with
-     * the oldest ping_sent time */
+     * the oldest pong_received time */
     for (j = 0; j < 5; j++) {
         de = dictGetRandomKey(server.cluster->nodes);
         clusterNode *this = dictGetVal(de);
 
-        if (this->link == NULL) continue;
+        /* Don't ping nodes disconnected or with a ping currently active. */
+        if (this->link == NULL || this->ping_sent != 0) continue;
         if (this->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE)) continue;
-        if (min_ping_node == NULL || min_ping_sent > this->ping_sent) {
-            min_ping_node = this;
-            min_ping_sent = this->ping_sent;
+        if (min_pong_node == NULL || min_pong > this->pong_received) {
+            min_pong_node = this;
+            min_pong = this->pong_received;
         }
     }
-    if (min_ping_node) {
-        redisLog(REDIS_DEBUG,"Pinging node %.40s", min_ping_node->name);
-        clusterSendPing(min_ping_node->link, CLUSTERMSG_TYPE_PING);
+    if (min_pong_node) {
+        redisLog(REDIS_DEBUG,"Pinging node %.40s", min_pong_node->name);
+        clusterSendPing(min_pong_node->link, CLUSTERMSG_TYPE_PING);
     }
 
     /* Iterate nodes to check if we need to flag something as failing */
@@ -1568,42 +1588,43 @@ void clusterCron(void) {
             (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR|REDIS_NODE_HANDSHAKE))
                 continue;
 
-        /* If our ping is older than half the cluster timeout (may happen
-         * in a cluster with many nodes), send a new ping. */
+#if 0
+        /* If we are waiting for the PONG more than half the cluster
+         * timeout, reconnect the link: maybe there is a connection
+         * issue even if the node is alive. */
+        if (node->link && /* is connected */
+            node->ping_sent && /* we already sent a ping */
+            node->pong_received < node->ping_sent && /* still waiting pong */
+            /* and we are waiting for the pong more than timeout/2 */
+            now - node->ping_sent > server.cluster_node_timeout/2)
+        {
+            /* Disconnect the link, it will be reconnected automatically. */
+            printf("DISCONNECT!\n");
+            freeClusterLink(node->link);
+        }
+#endif
+
+        /* If we have currently no active ping in this instance, and the
+         * received PONG is older than half the cluster timeout, send
+         * a new ping now, to ensure all the nodes are pinged without
+         * a too big delay. */
         if (node->link &&
-            (now - node->ping_sent) > server.cluster_node_timeout/2)
+            node->ping_sent == 0 &&
+            (now - node->pong_received) > server.cluster_node_timeout/2)
         {
             clusterSendPing(node->link, CLUSTERMSG_TYPE_PING);
             continue;
         }
 
-        /* Check only if we already sent a ping and did not received
-         * a reply yet. */
-        if (node->ping_sent == 0 ||
-            node->ping_sent <= node->pong_received) continue;
+        /* Check only if we have an active ping for this instance. */
+        if (node->ping_sent == 0) continue;
 
-        /* If we never received a pong, use the ping time to compute
-         * the delay. */
-        if (node->pong_received) {
-            delay = now - node->pong_received;
-        } else {
-            delay = now - node->ping_sent;
-        }
+        /* Compute the delay of the PONG. Note that if we already received
+         * the PONG, then node->ping_sent is zero, so can't reach this
+         * code at all. */
+        delay = now - node->ping_sent;
 
-        if (delay < server.cluster_node_timeout) {
-            /* The PFAIL condition can be reversed without external
-             * help if it is not transitive (that is, if it does not
-             * turn into a FAIL state).
-             *
-             * The FAIL condition is also reversible under specific
-             * conditions detected by clearNodeFailureIfNeeded(). */
-            if (node->flags & REDIS_NODE_PFAIL) {
-                node->flags &= ~REDIS_NODE_PFAIL;
-                update_state = 1;
-            } else if (node->flags & REDIS_NODE_FAIL) {
-                clearNodeFailureIfNeeded(node);
-            }
-        } else {
+        if (delay > server.cluster_node_timeout) {
             /* Timeout reached. Set the node as possibly failing if it is
              * not already in this state. */
             if (!(node->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL))) {