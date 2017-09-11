@@ -349,8 +349,12 @@ clusterNode *createClusterNode(char *nodename, int flags) {
  * the timestamp of an existing report).
  *
  * 'failing' is the node that is in failure state according to the
- * 'sender' node. */
-void clusterNodeAddFailureReport(clusterNode *failing, clusterNode *sender) {
+ * 'sender' node.
+ *
+ * The function returns 0 if it just updates a timestamp of an existing
+ * failure report from the same sender. 1 is returned if a new failure
+ * report is created. */
+int clusterNodeAddFailureReport(clusterNode *failing, clusterNode *sender) {
     list *l = failing->fail_reports;
     listNode *ln;
     listIter li;
@@ -363,7 +367,7 @@ void clusterNodeAddFailureReport(clusterNode *failing, clusterNode *sender) {
         fr = ln->value;
         if (fr->node == sender) {
             fr->time = time(NULL);
-            return;
+            return 0;
         }
     }
 
@@ -372,6 +376,7 @@ void clusterNodeAddFailureReport(clusterNode *failing, clusterNode *sender) {
     fr->node = sender;
     fr->time = time(NULL);
     listAddNodeTail(l,fr);
+    return 1;
 }
 
 /* Remove failure reports that are too old, where too old means reasonably
@@ -401,8 +406,11 @@ void clusterNodeCleanupFailureReports(clusterNode *node) {
  * Note that this function is called relatively often as it gets called even
  * when there are no nodes failing, and is O(N), however when the cluster is
  * fine the failure reports list is empty so the function runs in constant
- * time. */
-void clusterNodeDelFailureReport(clusterNode *node, clusterNode *sender) {
+ * time.
+ *
+ * The function returns 1 if the failure report was found and removed.
+ * Otherwise 0 is returned. */
+int clusterNodeDelFailureReport(clusterNode *node, clusterNode *sender) {
     list *l = node->fail_reports;
     listNode *ln;
     listIter li;
@@ -414,11 +422,12 @@ void clusterNodeDelFailureReport(clusterNode *node, clusterNode *sender) {
         fr = ln->value;
         if (fr->node == sender) break;
     }
-    if (!ln) return; /* No failure report from this sender. */
+    if (!ln) return 0; /* No failure report from this sender. */
 
     /* Remove the failure report. */
     listDelNode(l,ln);
     clusterNodeCleanupFailureReports(node);
+    return 1;
 }
 
 /* Return the number of external nodes that believe 'node' is failing,
@@ -514,6 +523,55 @@ void clusterRenameNode(clusterNode *node, char *newname) {
  * CLUSTER messages exchange - PING/PONG and gossip
  * -------------------------------------------------------------------------- */
 
+/* This function checks if a given node should be marked as FAIL.
+ * It happens if the following conditions are met:
+ *
+ * 1) We are a master node. Only master nodes can mark a node as failing.
+ * 2) We received enough failure reports from other nodes via gossip.
+ *    Enough means that the majority of the masters believe the node is
+ *    down.
+ * 3) We believe this node is in PFAIL state.
+ *
+ * If a failure is detected we also inform the whole cluster about this
+ * event trying to force every other node to set the FAIL flag for the node.
+ */
+void markNodeAsFailingIfNeeded(clusterNode *node) {
+    int failures;
+    int needed_quorum = (server.cluster->size / 2) + 1;
+
+    if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return;
+    if (!(node->flags & REDIS_NODE_PFAIL)) return; /* We can reach it. */
+    if (node->flags & REDIS_NODE_FAIL) return; /* Already FAILing. */
+
+    failures = 1 + clusterNodeFailureReportsCount(node); /* +1 is for myself. */
+    if (failures < needed_quorum) return;
+
+    redisLog(REDIS_NOTICE,
+        "Marking node %.40s as failing (quorum reached).", node->name);
+
+    /* Mark the node as failing. */
+    node->flags &= ~REDIS_NODE_PFAIL;
+    node->flags |= REDIS_NODE_FAIL;
+
+    /* Broadcast the failing node name to everybody */
+    clusterSendFail(node->name);
+    clusterUpdateState();
+    clusterSaveConfigOrDie();
+}
+
+/* This function is called only if a node is marked as FAIL, but we are able
+ * to reach it again. It checks if there are the conditions to undo the FAIL
+ * state.
+ *
+ * Currently we only revert the FAIL state if there are no slaves for this
+ * node, so that no election was possible. */
+void clearNodeFailureIfNeeded(clusterNode *node) {
+    if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
+        node->flags &= ~REDIS_NODE_FAIL;
+        clusterUpdateState();
+    }
+}
+
 /* Process the gossip section of PING or PONG packets.
  * Note that this function assumes that the packet is already sanity-checked
  * by the caller, not in the content of the gossip section, but in the
@@ -556,18 +614,22 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
                  redisLog(REDIS_DEBUG,"Node pong_received updated by gossip");
                 node->pong_received = ntohl(g->pong_received);
             }
-            /* Mark this node as FAILED if we think it is possibly failing
-             * and another node also thinks it's failing. */
-            if (node->flags & REDIS_NODE_PFAIL &&
-                (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)))
-            {
-                redisLog(REDIS_NOTICE,"Received a PFAIL acknowledge from node %.40s, marking node %.40s as FAIL!", hdr->sender, node->name);
-                node->flags &= ~REDIS_NODE_PFAIL;
-                node->flags |= REDIS_NODE_FAIL;
-                /* Broadcast the failing node name to everybody */
-                clusterSendFail(node->name);
-                clusterUpdateState();
-                clusterSaveConfigOrDie();
+            /* Handle failure reports, only when the sender is a master. */
+            if (sender && sender->flags & REDIS_NODE_MASTER) {
+                if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
+                    if (clusterNodeAddFailureReport(node,sender)) {
+                        redisLog(REDIS_NOTICE,
+                            "Node %.40s reported node %.40s as not reachable.",
+                            sender->name, node->name);
+                    }
+                    markNodeAsFailingIfNeeded(node);
+                } else {
+                    if (clusterNodeDelFailureReport(node,sender)) {
+                        redisLog(REDIS_NOTICE,
+                            "Node %.40s reported node %.40s is back online.",
+                            sender->name, node->name);
+                    }
+                }
             }
         } else {
             /* If it's not in NOADDR state and we don't have it, we
@@ -1187,9 +1249,8 @@ void clusterCron(void) {
              * FAIL node. */
             if (node->flags & REDIS_NODE_PFAIL) {
                 node->flags &= ~REDIS_NODE_PFAIL;
-            } else if (node->flags & REDIS_NODE_FAIL && !node->numslaves) {
-                node->flags &= ~REDIS_NODE_FAIL;
-                clusterUpdateState();
+            } else if (node->flags & REDIS_NODE_FAIL) {
+                clearNodeFailureIfNeeded(node);
             }
         } else {
             /* Timeout reached. Set the node as possibly failing if it is