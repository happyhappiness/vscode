@@ -917,7 +917,8 @@ void clusterRenameNode(clusterNode *node, char *newname) {
  * CLUSTER config epoch handling
  * -------------------------------------------------------------------------- */
 
-/* Return the greatest configEpoch found in the cluster. */
+/* Return the greatest configEpoch found in the cluster, or the current
+ * epoch if greater than any node configEpoch. */
 uint64_t clusterGetMaxEpoch(void) {
     uint64_t max = 0;
     dictIterator *di;
@@ -3634,7 +3635,7 @@ sds clusterGenNodeDescription(clusterNode *node) {
     else
         ci = sdscatlen(ci," - ",3);
 
-    /* Latency from the POV of this node, link status */
+    /* Latency from the POV of this node, config epoch, link status */
     ci = sdscatprintf(ci,"%lld %lld %llu %s",
         (long long) node->ping_sent,
         (long long) node->pong_received,