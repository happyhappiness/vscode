@@ -102,7 +102,7 @@ int clusterLoadConfig(char *filename) {
     struct stat sb;
     char *line;
     int maxline, j;
-   
+
     if (fp == NULL) {
         if (errno == ENOENT) {
             return REDIS_ERR;
@@ -311,7 +311,7 @@ int clusterSaveConfig(int do_fsync) {
         (unsigned long long) server.cluster->currentEpoch,
         (unsigned long long) server.cluster->lastVoteEpoch);
     content_size = sdslen(ci);
-    
+
     if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT,0644))
         == -1) goto err;
 
@@ -751,7 +751,7 @@ void freeClusterNode(clusterNode *n) {
 /* Add a node to the nodes hash table */
 int clusterAddNode(clusterNode *node) {
     int retval;
-    
+
     retval = dictAdd(server.cluster->nodes,
             sdsnewlen(node->name,REDIS_CLUSTER_NAMELEN), node);
     return (retval == DICT_OK) ? REDIS_OK : REDIS_ERR;
@@ -814,7 +814,7 @@ clusterNode *clusterLookupNode(char *name) {
 void clusterRenameNode(clusterNode *node, char *newname) {
     int retval;
     sds s = sdsnewlen(node->name, REDIS_CLUSTER_NAMELEN);
-   
+
     redisLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
         node->name, newname);
     retval = dictDelete(server.cluster->nodes, s);
@@ -1783,7 +1783,7 @@ int clusterProcessPacket(clusterLink *link) {
 /* This function is called when we detect the link with this node is lost.
    We set the node as no longer connected. The Cluster Cron will detect
    this connection and will try to get it connected again.
-   
+
    Instead if the node is a temporary node used to accept a query, we
    completely free the node on error. */
 void handleLinkIOError(clusterLink *link) {
@@ -1893,7 +1893,7 @@ void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
 
 /* Send a message to all the nodes that are part of the cluster having
  * a connected link.
- * 
+ *
  * It is guaranteed that this function will never have as a side effect
  * some node->link to be invalidated, so it is safe to call this function
  * from event handlers that will do stuff with node links later. */
@@ -1987,7 +1987,7 @@ void clusterSendPing(clusterLink *link, int type) {
     if (link->node && type == CLUSTERMSG_TYPE_PING)
         link->node->ping_sent = mstime();
     clusterBuildMessageHdr(hdr,type);
-        
+
     /* Populate the gossip fields */
     while(freshnodes > 0 && gossipcount < 3) {
         dictEntry *de = dictGetRandomKey(server.cluster->nodes);
@@ -3052,7 +3052,7 @@ void clusterUpdateState(void) {
      * of the netsplit because of lack of majority. */
     {
         int needed_quorum = (server.cluster->size / 2) + 1;
-        
+
         if (unreachable_masters >= needed_quorum) {
             new_state = REDIS_CLUSTER_FAIL;
             among_minority_time = mstime();
@@ -4028,7 +4028,7 @@ void migrateCommand(redisClient *c) {
         addReplySds(c,sdsnew("+NOKEY\r\n"));
         return;
     }
-    
+
     /* Connect */
     fd = migrateGetSocket(c,c->argv[1],c->argv[2],timeout);
     if (fd == -1) return; /* error sent to the client by migrateGetSocket() */