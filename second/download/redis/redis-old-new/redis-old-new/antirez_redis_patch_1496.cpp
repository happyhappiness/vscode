@@ -377,7 +377,7 @@ clusterNode *clusterLookupNode(char *name) {
     de = dictFind(server.cluster.nodes,s);
     sdsfree(s);
     if (de == NULL) return NULL;
-    return dictGetEntryVal(de);
+    return dictGetVal(de);
 }
 
 /* This is only used after the handshake. When we connect a given IP/PORT
@@ -793,7 +793,7 @@ void clusterBroadcastMessage(void *buf, size_t len) {
 
     di = dictGetIterator(server.cluster.nodes);
     while((de = dictNext(di)) != NULL) {
-        clusterNode *node = dictGetEntryVal(de);
+        clusterNode *node = dictGetVal(de);
 
         if (!node->link) continue;
         if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR)) continue;
@@ -849,7 +849,7 @@ void clusterSendPing(clusterLink *link, int type) {
     /* Populate the gossip fields */
     while(freshnodes > 0 && gossipcount < 3) {
         struct dictEntry *de = dictGetRandomKey(server.cluster.nodes);
-        clusterNode *this = dictGetEntryVal(de);
+        clusterNode *this = dictGetVal(de);
         clusterMsgDataGossip *gossip;
         int j;
 
@@ -970,7 +970,7 @@ void clusterCron(void) {
     /* Check if we have disconnected nodes and reestablish the connection. */
     di = dictGetIterator(server.cluster.nodes);
     while((de = dictNext(di)) != NULL) {
-        clusterNode *node = dictGetEntryVal(de);
+        clusterNode *node = dictGetVal(de);
 
         if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR)) continue;
         if (node->link == NULL) {
@@ -1005,7 +1005,7 @@ void clusterCron(void) {
      * the oldest ping_sent time */
     for (j = 0; j < 5; j++) {
         de = dictGetRandomKey(server.cluster.nodes);
-        clusterNode *this = dictGetEntryVal(de);
+        clusterNode *this = dictGetVal(de);
 
         if (this->link == NULL) continue;
         if (this->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE)) continue;
@@ -1022,7 +1022,7 @@ void clusterCron(void) {
     /* Iterate nodes to check if we need to flag something as failing */
     di = dictGetIterator(server.cluster.nodes);
     while((de = dictNext(di)) != NULL) {
-        clusterNode *node = dictGetEntryVal(de);
+        clusterNode *node = dictGetVal(de);
         int delay;
 
         if (node->flags &
@@ -1153,7 +1153,7 @@ sds clusterGenNodesDescription(void) {
 
     di = dictGetIterator(server.cluster.nodes);
     while((de = dictNext(di)) != NULL) {
-        clusterNode *node = dictGetEntryVal(de);
+        clusterNode *node = dictGetVal(de);
 
         /* Node coordinates */
         ci = sdscatprintf(ci,"%.40s %s:%d ",