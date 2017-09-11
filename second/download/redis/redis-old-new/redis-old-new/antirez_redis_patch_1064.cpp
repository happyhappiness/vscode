@@ -594,25 +594,36 @@ void clusterRenameNode(clusterNode *node, char *newname) {
 /* This function checks if a given node should be marked as FAIL.
  * It happens if the following conditions are met:
  *
- * 1) We are a master node. Only master nodes can mark a node as failing.
- * 2) We received enough failure reports from other nodes via gossip.
- *    Enough means that the majority of the masters believe the node is
- *    down.
- * 3) We believe this node is in PFAIL state.
+ * 1) We received enough failure reports from other master nodes via gossip.
+ *    Enough means that the majority of the masters signaled the node is
+ *    down recently.
+ * 2) We believe this node is in PFAIL state.
  *
  * If a failure is detected we also inform the whole cluster about this
  * event trying to force every other node to set the FAIL flag for the node.
+ *
+ * Note that the form of agreement used here is weak, as we collect the majority
+ * of masters state during some time, and even if we force agreement by
+ * propagating the FAIL message, because of partitions we may not reach every
+ * node. However:
+ *
+ * 1) Either we reach the majority and eventually the FAIL state will propagate
+ *    to all the cluster.
+ * 2) Or there is no majority so no slave promotion will be authorized and the
+ *    FAIL flag will be cleared after some time.
  */
 void markNodeAsFailingIfNeeded(clusterNode *node) {
     int failures;
     int needed_quorum = (server.cluster->size / 2) + 1;
 
-    if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return;
     if (!(node->flags & REDIS_NODE_PFAIL)) return; /* We can reach it. */
     if (node->flags & REDIS_NODE_FAIL) return; /* Already FAILing. */
 
-    failures = 1 + clusterNodeFailureReportsCount(node); /* +1 is for myself. */
-    if (failures < needed_quorum) return;
+    failures = clusterNodeFailureReportsCount(node);
+    /* Also count myself as a voter if I'm a master. */
+    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
+        failures += 1;
+    if (failures < needed_quorum) return; /* No weak agreement from masters. */
 
     redisLog(REDIS_NOTICE,
         "Marking node %.40s as failing (quorum reached).", node->name);
@@ -622,8 +633,10 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
     node->flags |= REDIS_NODE_FAIL;
     node->fail_time = time(NULL);
 
-    /* Broadcast the failing node name to everybody */
-    clusterSendFail(node->name);
+    /* Broadcast the failing node name to everybody, forcing all the other
+     * reachable nodes to flag the node as FAIL. */
+    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
+        clusterSendFail(node->name);
     clusterUpdateState();
     clusterSaveConfigOrDie();
 }