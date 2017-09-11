@@ -567,11 +567,12 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
  * node, so that no election was possible. */
 void clearNodeFailureIfNeeded(clusterNode *node) {
     if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
-        node->flags &= ~REDIS_NODE_FAIL;
-        clusterUpdateState();
         redisLog(REDIS_NOTICE,
             "Clear FAIL state for node %.40s: is reachable and has no slaves.",
                 node->name);
+        node->flags &= ~REDIS_NODE_FAIL;
+        clusterUpdateState();
+        clusterSaveConfigOrDie();
     }
 }
 
@@ -618,7 +619,9 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
                 node->pong_received = ntohl(g->pong_received);
             }
             /* Handle failure reports, only when the sender is a master. */
-            if (sender && sender->flags & REDIS_NODE_MASTER) {
+            if (sender && sender->flags & REDIS_NODE_MASTER &&
+                node != server.cluster->myself)
+            {
                 if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                     if (clusterNodeAddFailureReport(node,sender)) {
                         redisLog(REDIS_NOTICE,
@@ -1239,7 +1242,14 @@ void clusterCron(void) {
         if (node->ping_sent == 0 ||
             node->ping_sent <= node->pong_received) continue;
 
-        delay = time(NULL) - node->pong_received;
+        /* If we never received a pong, use the ping time to compute
+         * the delay. */
+        if (node->pong_received) {
+            delay = time(NULL) - node->pong_received;
+        } else {
+            delay = time(NULL) - node->ping_sent;
+        }
+
         if (delay < server.cluster->node_timeout) {
             /* The PFAIL condition can be reversed without external
              * help if it is not transitive (that is, if it does not