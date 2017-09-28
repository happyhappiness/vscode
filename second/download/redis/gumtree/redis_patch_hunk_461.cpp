     ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
         node->name,
         node->ip,
         node->port);
 
     /* Flags */
-    ci = representRedisNodeFlags(ci, node->flags);
+    ci = representClusterNodeFlags(ci, node->flags);
 
     /* Slave of... or just "-" */
     if (node->slaveof)
         ci = sdscatprintf(ci," %.40s ",node->slaveof->name);
     else
         ci = sdscatlen(ci," - ",3);
 
     /* Latency from the POV of this node, config epoch, link status */
     ci = sdscatprintf(ci,"%lld %lld %llu %s",
         (long long) node->ping_sent,
         (long long) node->pong_received,
         (unsigned long long) node->configEpoch,
-        (node->link || node->flags & REDIS_NODE_MYSELF) ?
+        (node->link || node->flags & CLUSTER_NODE_MYSELF) ?
                     "connected" : "disconnected");
 
     /* Slots served by this instance */
     start = -1;
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         int bit;
 
         if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
             if (start == -1) start = j;
         }
-        if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
-            if (bit && j == REDIS_CLUSTER_SLOTS-1) j++;
+        if (start != -1 && (!bit || j == CLUSTER_SLOTS-1)) {
+            if (bit && j == CLUSTER_SLOTS-1) j++;
 
             if (start == j-1) {
                 ci = sdscatprintf(ci," %d",start);
             } else {
                 ci = sdscatprintf(ci," %d-%d",start,j-1);
             }
