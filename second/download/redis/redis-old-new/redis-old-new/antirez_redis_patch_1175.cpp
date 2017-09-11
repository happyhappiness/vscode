@@ -611,11 +611,38 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
  * Currently we only revert the FAIL state if there are no slaves for this
  * node, so that no election was possible. */
 void clearNodeFailureIfNeeded(clusterNode *node) {
-    if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
+    int changes = 0;
+    time_t now = time(NULL);
+
+    redisAssert(node->flags & REDIS_NODE_FAIL);
+
+    /* For slaves we always clear the FAIL flag if we can contact the
+     * node again. */
+    if (node->flags & REDIS_NODE_SLAVE) {
         redisLog(REDIS_NOTICE,
-            "Clear FAIL state for node %.40s: is reachable and has no slaves.",
+            "Clear FAIL state for node %.40s: slave is already reachable.",
                 node->name);
         node->flags &= ~REDIS_NODE_FAIL;
+        changes++;
+    }
+
+    /* If it is a master and...
+     * 1) The FAIL state was set more than 2 times the node timeout + 10 sec.
+     * 2) It is yet serving slots from our point of view (not failed over).
+     * Apparently no one is going to fix these slots, clear the FAIL flag. */
+    if (node->flags & REDIS_NODE_MASTER &&
+        node->numslots > 0 &&
+        (now - node->fail_time) > (server.cluster->node_timeout*2+10))
+    {
+        redisLog(REDIS_NOTICE,
+            "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
+                node->name);
+        node->flags &= ~REDIS_NODE_FAIL;
+        changes++;
+    }
+
+    /* Update state and save config. */
+    if (changes) {
         clusterUpdateState();
         clusterSaveConfigOrDie();
     }