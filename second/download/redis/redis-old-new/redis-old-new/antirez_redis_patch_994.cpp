@@ -2510,6 +2510,82 @@ void clusterSetMaster(clusterNode *n) {
  * CLUSTER command
  * -------------------------------------------------------------------------- */
 
+/* Generate a csv-alike representation of the specified cluster node.
+ * See clusterGenNodesDescription() top comment for more information.
+ *
+ * The function returns the string representation as an SDS string. */
+sds clusterGenNodeDescription(clusterNode *node) {
+    int j, start;
+    sds ci;
+
+    /* Node coordinates */
+    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
+        node->name,
+        node->ip,
+        node->port);
+
+    /* Flags */
+    if (node->flags == 0) ci = sdscat(ci,"noflags,");
+    if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
+    if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
+    if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
+    if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
+    if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
+    if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
+    if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
+    if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
+
+    /* Slave of... or just "-" */
+    if (node->slaveof)
+        ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
+    else
+        ci = sdscatprintf(ci,"- ");
+
+    /* Latency from the POV of this node, link status */
+    ci = sdscatprintf(ci,"%lld %lld %llu %s",
+        (long long) node->ping_sent,
+        (long long) node->pong_received,
+        (unsigned long long) node->configEpoch,
+        (node->link || node->flags & REDIS_NODE_MYSELF) ?
+                    "connected" : "disconnected");
+
+    /* Slots served by this instance */
+    start = -1;
+    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        int bit;
+
+        if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
+            if (start == -1) start = j;
+        }
+        if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
+            if (j == REDIS_CLUSTER_SLOTS-1) j++;
+
+            if (start == j-1) {
+                ci = sdscatprintf(ci," %d",start);
+            } else {
+                ci = sdscatprintf(ci," %d-%d",start,j-1);
+            }
+            start = -1;
+        }
+    }
+
+    /* Just for MYSELF node we also dump info about slots that
+     * we are migrating to other instances or importing from other
+     * instances. */
+    if (node->flags & REDIS_NODE_MYSELF) {
+        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+            if (server.cluster->migrating_slots_to[j]) {
+                ci = sdscatprintf(ci," [%d->-%.40s]",j,
+                    server.cluster->migrating_slots_to[j]->name);
+            } else if (server.cluster->importing_slots_from[j]) {
+                ci = sdscatprintf(ci," [%d-<-%.40s]",j,
+                    server.cluster->importing_slots_from[j]->name);
+            }
+        }
+    }
+    return ci;
+}
+
 /* Generate a csv-alike representation of the nodes we are aware of,
  * including the "myself" node, and return an SDS string containing the
  * representation (it is up to the caller to free it).
@@ -2523,82 +2599,18 @@ void clusterSetMaster(clusterNode *n) {
  * of the CLUSTER NODES function, and as format for the cluster
  * configuration file (nodes.conf) for a given node. */
 sds clusterGenNodesDescription(int filter) {
-    sds ci = sdsempty();
+    sds ci = sdsempty(), ni;
     dictIterator *di;
     dictEntry *de;
-    int j, start;
 
     di = dictGetSafeIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
         if (node->flags & filter) continue;
-
-        /* Node coordinates */
-        ci = sdscatprintf(ci,"%.40s %s:%d ",
-            node->name,
-            node->ip,
-            node->port);
-
-        /* Flags */
-        if (node->flags == 0) ci = sdscat(ci,"noflags,");
-        if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
-        if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
-        if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
-        if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
-        if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
-        if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
-        if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
-
-        /* Slave of... or just "-" */
-        if (node->slaveof)
-            ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
-        else
-            ci = sdscatprintf(ci,"- ");
-
-        /* Latency from the POV of this node, link status */
-        ci = sdscatprintf(ci,"%lld %lld %llu %s",
-            (long long) node->ping_sent,
-            (long long) node->pong_received,
-            (unsigned long long) node->configEpoch,
-            (node->link || node->flags & REDIS_NODE_MYSELF) ?
-                        "connected" : "disconnected");
-
-        /* Slots served by this instance */
-        start = -1;
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-            int bit;
-
-            if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
-                if (start == -1) start = j;
-            }
-            if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
-                if (j == REDIS_CLUSTER_SLOTS-1) j++;
-
-                if (start == j-1) {
-                    ci = sdscatprintf(ci," %d",start);
-                } else {
-                    ci = sdscatprintf(ci," %d-%d",start,j-1);
-                }
-                start = -1;
-            }
-        }
-
-        /* Just for MYSELF node we also dump info about slots that
-         * we are migrating to other instances or importing from other
-         * instances. */
-        if (node->flags & REDIS_NODE_MYSELF) {
-            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-                if (server.cluster->migrating_slots_to[j]) {
-                    ci = sdscatprintf(ci," [%d->-%.40s]",j,
-                        server.cluster->migrating_slots_to[j]->name);
-                } else if (server.cluster->importing_slots_from[j]) {
-                    ci = sdscatprintf(ci," [%d-<-%.40s]",j,
-                        server.cluster->importing_slots_from[j]->name);
-                }
-            }
-        }
+        ni = clusterGenNodeDescription(node);
+        ci = sdscatsds(ci,ni);
+        sdsfree(ni);
         ci = sdscatlen(ci,"\n",1);
     }
     dictReleaseIterator(di);