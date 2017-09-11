@@ -1099,7 +1099,8 @@ sds clusterGenNodesDescription(void) {
         ci = sdscatprintf(ci,"%ld %ld %s",
             (long) node->ping_sent,
             (long) node->pong_received,
-            node->link ? "connected" : "disconnected");
+            (node->link || node->flags & REDIS_NODE_MYSELF) ?
+                        "connected" : "disconnected");
 
         /* Slots served by this instance */
         start = -1;