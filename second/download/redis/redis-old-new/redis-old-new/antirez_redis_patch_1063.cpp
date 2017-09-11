@@ -59,6 +59,23 @@ int bitmapTestBit(unsigned char *bitmap, int pos);
  * Initialization
  * -------------------------------------------------------------------------- */
 
+/* This function is called at startup in order to set the currentEpoch
+ * (which is not saved on permanent storage) to the greatest configEpoch found
+ * in the loaded nodes (configEpoch is stored on permanent storage as soon as
+ * it changes for some node). */
+void clusterSetStartupEpoch() {
+    dictIterator *di;
+    dictEntry *de;
+
+    di = dictGetSafeIterator(server.cluster->nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetVal(de);
+        if (node->configEpoch > server.cluster->currentEpoch)
+            server.cluster->currentEpoch = node->configEpoch;
+    }
+    dictReleaseIterator(di);
+}
+
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
     char *line;
@@ -143,8 +160,11 @@ int clusterLoadConfig(char *filename) {
         if (atoi(argv[4])) n->ping_sent = time(NULL);
         if (atoi(argv[5])) n->pong_received = time(NULL);
 
+        /* Set configEpoch for this node. */
+        n->configEpoch = strtoull(argv[6],NULL,10);
+
         /* Populate hash slots served by this instance. */
-        for (j = 7; j < argc; j++) {
+        for (j = 8; j < argc; j++) {
             int start, stop;
 
             if (argv[j][0] == '[') {
@@ -189,6 +209,7 @@ int clusterLoadConfig(char *filename) {
     redisAssert(server.cluster->myself != NULL);
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
         server.cluster->myself->name);
+    clusterSetStartupEpoch();
     clusterUpdateState();
     return REDIS_OK;
 
@@ -230,6 +251,7 @@ void clusterInit(void) {
 
     server.cluster = zmalloc(sizeof(clusterState));
     server.cluster->myself = NULL;
+    server.cluster->currentEpoch = 0;
     server.cluster->state = REDIS_CLUSTER_FAIL;
     server.cluster->size = 1;
     server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
@@ -360,6 +382,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     else
         getRandomHexChars(node->name, REDIS_CLUSTER_NAMELEN);
     node->ctime = time(NULL);
+    node->configEpoch = 0;
     node->flags = flags;
     memset(node->slots,0,sizeof(node->slots));
     node->numslots = 0;
@@ -2071,9 +2094,10 @@ sds clusterGenNodesDescription(int filter) {
             ci = sdscatprintf(ci,"- ");
 
         /* Latency from the POV of this node, link status */
-        ci = sdscatprintf(ci,"%ld %ld %s",
+        ci = sdscatprintf(ci,"%ld %ld %llu %s",
             (long) node->ping_sent,
             (long) node->pong_received,
+            (unsigned long long) node->configEpoch,
             (node->link || node->flags & REDIS_NODE_MYSELF) ?
                         "connected" : "disconnected");
 