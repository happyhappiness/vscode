@@ -45,7 +45,7 @@ void clusterSendFail(char *nodename);
 void clusterSendFailoverAuthIfNeeded(clusterNode *sender);
 void clusterUpdateState(void);
 int clusterNodeGetSlotBit(clusterNode *n, int slot);
-sds clusterGenNodesDescription(void);
+sds clusterGenNodesDescription(int filter);
 clusterNode *clusterLookupNode(char *name);
 int clusterNodeAddSlave(clusterNode *master, clusterNode *slave);
 int clusterAddSlot(clusterNode *n, int slot);
@@ -203,7 +203,7 @@ int clusterLoadConfig(char *filename) {
  * This function writes the node config and returns 0, on error -1
  * is returned. */
 int clusterSaveConfig(void) {
-    sds ci = clusterGenNodesDescription();
+    sds ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
     int fd;
     
     if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT|O_TRUNC,0644))
@@ -1972,7 +1972,19 @@ void clusterSetMaster(clusterNode *n) {
  * CLUSTER command
  * -------------------------------------------------------------------------- */
 
-sds clusterGenNodesDescription(void) {
+/* Generate a csv-alike representation of the nodes we are aware of,
+ * including the "myself" node, and return an SDS string containing the
+ * representation (it is up to the caller to free it).
+ *
+ * All the nodes matching at least one of the node flags specified in
+ * "filter" are excluded from the output, so using zero as a filter will
+ * include all the known nodes in the representation, including nodes in
+ * the HANDSHAKE state.
+ *
+ * The representation obtained using this function is used for the output
+ * of the CLUSTER NODES function, and as format for the cluster
+ * configuration file (nodes.conf) for a given node. */
+sds clusterGenNodesDescription(int filter) {
     sds ci = sdsempty();
     dictIterator *di;
     dictEntry *de;
@@ -1982,6 +1994,8 @@ sds clusterGenNodesDescription(void) {
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
+        if (node->flags & filter) continue;
+
         /* Node coordinates */
         ci = sdscatprintf(ci,"%.40s %s:%d ",
             node->name,
@@ -2117,7 +2131,7 @@ void clusterCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
         /* CLUSTER NODES */
         robj *o;
-        sds ci = clusterGenNodesDescription();
+        sds ci = clusterGenNodesDescription(0);
 
         o = createObject(REDIS_STRING,ci);
         addReplyBulk(c,o);