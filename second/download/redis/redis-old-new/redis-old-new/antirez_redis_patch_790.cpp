@@ -72,39 +72,7 @@ void resetManualFailover(void);
 void clusterCloseAllSlots(void);
 void clusterSetNodeAsMaster(clusterNode *n);
 void clusterDelNode(clusterNode *delnode);
-
-struct redisNodeFlags {
-    uint16_t flag;
-    char     *attr;
-};
-
-static struct redisNodeFlags nodeflags[] = {
-    {REDIS_NODE_MYSELF,    "myself,"},
-    {REDIS_NODE_MASTER,    "master,"},
-    {REDIS_NODE_SLAVE,     "slave,"},
-    {REDIS_NODE_PFAIL,     "fail?,"},
-    {REDIS_NODE_FAIL,      "fail,"},
-    {REDIS_NODE_HANDSHAKE, "handshake,"},
-    {REDIS_NODE_NOADDR,    "noaddr,"}
-};
-
-sds representRedisNodeFlags(sds ci, uint16_t flags) {
-    if (flags == 0) {
-        ci = sdscat(ci,"noflags");
-    } else {
-        int size = sizeof(nodeflags) / sizeof(struct redisNodeFlags);
-        for (int i=0; i < size; i++) {
-            struct redisNodeFlags *nodeflag = nodeflags + i;
-            if (flags & nodeflag->flag) {
-                ci = sdscat(ci, nodeflag->attr);
-            }
-        }
-
-        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
-    }
-
-    return ci;
-}
+sds representRedisNodeFlags(sds ci, uint16_t flags);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -1180,9 +1148,9 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
     while(count--) {
         uint16_t flags = ntohs(g->flags);
         clusterNode *node;
+        sds ci;
 
-        sds ci = sdsempty();
-        ci = representRedisNodeFlags(ci, flags);
+        ci = representRedisNodeFlags(sdsempty(), flags);
         redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
             g->nodename,
             g->ip,
@@ -3361,9 +3329,40 @@ void clusterSetMaster(clusterNode *n) {
 }
 
 /* -----------------------------------------------------------------------------
- * CLUSTER command
+ * Nodes to string representation functions.
  * -------------------------------------------------------------------------- */
 
+struct redisNodeFlags {
+    uint16_t flag;
+    char *name;
+};
+
+static struct redisNodeFlags redisNodeFlagsTable[] = {
+    {REDIS_NODE_MYSELF,    "myself,"},
+    {REDIS_NODE_MASTER,    "master,"},
+    {REDIS_NODE_SLAVE,     "slave,"},
+    {REDIS_NODE_PFAIL,     "fail?,"},
+    {REDIS_NODE_FAIL,      "fail,"},
+    {REDIS_NODE_HANDSHAKE, "handshake,"},
+    {REDIS_NODE_NOADDR,    "noaddr,"}
+};
+
+/* Concatenate the comma separated list of node flags to the given SDS
+ * string 'ci'. */
+sds representRedisNodeFlags(sds ci, uint16_t flags) {
+    if (flags == 0) {
+        ci = sdscat(ci,"noflags,");
+    } else {
+        int i, size = sizeof(redisNodeFlagsTable)/sizeof(struct redisNodeFlags);
+        for (i = 0; i < size; i++) {
+            struct redisNodeFlags *nodeflag = redisNodeFlagsTable + i;
+            if (flags & nodeflag->flag) ci = sdscat(ci, nodeflag->name);
+        }
+    }
+    sdsIncrLen(ci,-1); /* Remove trailing comma. */
+    return ci;
+}
+
 /* Generate a csv-alike representation of the specified cluster node.
  * See clusterGenNodesDescription() top comment for more information.
  *
@@ -3383,9 +3382,9 @@ sds clusterGenNodeDescription(clusterNode *node) {
 
     /* Slave of... or just "-" */
     if (node->slaveof)
-        ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
+        ci = sdscatprintf(ci," %.40s ",node->slaveof->name);
     else
-        ci = sdscatprintf(ci,"- ");
+        ci = sdscatlen(ci," - ",3);
 
     /* Latency from the POV of this node, link status */
     ci = sdscatprintf(ci,"%lld %lld %llu %s",
@@ -3463,6 +3462,10 @@ sds clusterGenNodesDescription(int filter) {
     return ci;
 }
 
+/* -----------------------------------------------------------------------------
+ * CLUSTER command
+ * -------------------------------------------------------------------------- */
+
 int getSlotOrReply(redisClient *c, robj *o) {
     long long slot;
 