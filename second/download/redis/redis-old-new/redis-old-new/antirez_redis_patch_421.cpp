@@ -73,7 +73,7 @@ void resetManualFailover(void);
 void clusterCloseAllSlots(void);
 void clusterSetNodeAsMaster(clusterNode *n);
 void clusterDelNode(clusterNode *delnode);
-sds representRedisNodeFlags(sds ci, uint16_t flags);
+sds representClusterNodeFlags(sds ci, uint16_t flags);
 uint64_t clusterGetMaxEpoch(void);
 int clusterBumpConfigEpochWithoutConsensus(void);
 
@@ -1303,7 +1303,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         clusterNode *node;
         sds ci;
 
-        ci = representRedisNodeFlags(sdsempty(), flags);
+        ci = representClusterNodeFlags(sdsempty(), flags);
         serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d %s",
             g->nodename,
             g->ip,
@@ -3605,7 +3605,7 @@ static struct redisNodeFlags redisNodeFlagsTable[] = {
 
 /* Concatenate the comma separated list of node flags to the given SDS
  * string 'ci'. */
-sds representRedisNodeFlags(sds ci, uint16_t flags) {
+sds representClusterNodeFlags(sds ci, uint16_t flags) {
     if (flags == 0) {
         ci = sdscat(ci,"noflags,");
     } else {
@@ -3634,7 +3634,7 @@ sds clusterGenNodeDescription(clusterNode *node) {
         node->port);
 
     /* Flags */
-    ci = representRedisNodeFlags(ci, node->flags);
+    ci = representClusterNodeFlags(ci, node->flags);
 
     /* Slave of... or just "-" */
     if (node->slaveof)