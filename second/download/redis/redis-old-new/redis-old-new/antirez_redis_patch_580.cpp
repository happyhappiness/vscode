@@ -3547,28 +3547,30 @@ sds representRedisNodeFlags(sds ci, uint16_t flags) {
 /* Generate a csv-alike representation of the specified cluster node.
  * See clusterGenNodesDescription() top comment for more information.
  *
- * The function returns the string representation as an SDS string. */
-sds clusterGenNodeDescription(clusterNode *node) {
+ * The function appends the node representation to the SDS string 'ci' and
+ * returns it (that may point to a different string as usually with the
+ * SDS-style API). */
+sds clusterGenNodeDescription(sds ci, clusterNode *node) {
     int j, start;
-    sds ci;
 
     /* Node coordinates */
-    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
-        node->name,
-        node->ip,
-        node->port);
+    ci = sdscatlen(ci,node->name,40);
+    ci = sdscatfmt(ci," %s:%i ",node->ip,node->port);
 
     /* Flags */
     ci = representRedisNodeFlags(ci, node->flags);
 
     /* Slave of... or just "-" */
-    if (node->slaveof)
-        ci = sdscatprintf(ci," %.40s ",node->slaveof->name);
-    else
+    if (node->slaveof) {
+        ci = sdscatlen(ci," ",1);
+        ci = sdscatlen(ci,node->slaveof->name,40);
+        ci = sdscatlen(ci," ",1);
+    } else {
         ci = sdscatlen(ci," - ",3);
+    }
 
     /* Latency from the POV of this node, link status */
-    ci = sdscatprintf(ci,"%lld %lld %llu %s",
+    ci = sdscatfmt(ci,"%I %I %U %s",
         (long long) node->ping_sent,
         (long long) node->pong_received,
         (unsigned long long) node->configEpoch,
@@ -3580,6 +3582,19 @@ sds clusterGenNodeDescription(clusterNode *node) {
     for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
         int bit;
 
+        /* It is common for a node to have pretty contiguous slots, so
+         * optimize this loop by skipping whole 32bit words if they have
+         * no set bits. We stop to the penultimate word because last word
+         * has special handling when start != -1 (later in the loop). */
+        if ((j&31)==0 && j < REDIS_CLUSTER_SLOTS-32) {
+            uint32_t *slotword = ((uint32_t*)node->slots)+(j/32);
+            if ((start == -1 && *slotword == 0) ||
+                (start != -1 && *slotword == UINT32_MAX)) {
+                j += 32;
+                continue;
+            }
+        }
+
         if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
             if (start == -1) start = j;
         }
@@ -3625,18 +3640,19 @@ sds clusterGenNodeDescription(clusterNode *node) {
  * of the CLUSTER NODES function, and as format for the cluster
  * configuration file (nodes.conf) for a given node. */
 sds clusterGenNodesDescription(int filter) {
-    sds ci = sdsempty(), ni;
+    sds ci = sdsempty();
     dictIterator *di;
     dictEntry *de;
 
+    /* Make room to avoid multiple resizes of the buffer. */
+    ci = sdsMakeRoomFor(ci,256*dictSize(server.cluster->nodes));
+
     di = dictGetSafeIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
         if (node->flags & filter) continue;
-        ni = clusterGenNodeDescription(node);
-        ci = sdscatsds(ci,ni);
-        sdsfree(ni);
+        ci = clusterGenNodeDescription(ci,node);
         ci = sdscatlen(ci,"\n",1);
     }
     dictReleaseIterator(di);
@@ -4093,7 +4109,7 @@ void clusterCommand(redisClient *c) {
 
         addReplyMultiBulkLen(c,n->numslaves);
         for (j = 0; j < n->numslaves; j++) {
-            sds ni = clusterGenNodeDescription(n->slaves[j]);
+            sds ni = clusterGenNodeDescription(sdsempty(),n->slaves[j]);
             addReplyBulkCString(c,ni);
             sdsfree(ni);
         }