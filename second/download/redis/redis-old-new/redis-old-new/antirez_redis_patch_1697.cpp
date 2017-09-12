@@ -44,7 +44,7 @@ int clusterLoadConfig(char *filename) {
     return REDIS_OK;
 
 fmterr:
-    redisLog(REDIS_WARNING,"Unrecovarable error: corrupted redis-cluster.conf file.");
+    redisLog(REDIS_WARNING,"Unrecovarable error: corrupted cluster config file.");
     fclose(fp);
     exit(1);
 }
@@ -53,11 +53,12 @@ int clusterLoadConfig(char *filename) {
  *
  * This function writes the node config and returns 0, on error -1
  * is returned. */
-int clusterSaveConfig(char *filename) {
+int clusterSaveConfig(void) {
     sds ci = clusterGenNodesDescription();
     int fd;
     
-    if ((fd = open(filename,O_WRONLY|O_CREAT,0644)) == -1) goto err;
+    if ((fd = open(server.cluster.configfile,O_WRONLY|O_CREAT,0644)) == -1)
+        goto err;
     if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
     close(fd);
     sdsfree(ci);
@@ -68,6 +69,13 @@ int clusterSaveConfig(char *filename) {
     return -1;
 }
 
+void clusterSaveConfigOrDie(void) {
+    if (clusterSaveConfig() == -1) {
+        redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
+        exit(1);
+    }
+}
+
 void clusterInit(void) {
     int saveconf = 0;
 
@@ -81,20 +89,15 @@ void clusterInit(void) {
         sizeof(server.cluster.importing_slots_from));
     memset(server.cluster.slots,0,
         sizeof(server.cluster.slots));
-    if (clusterLoadConfig("redis-cluster.conf") == REDIS_ERR) {
+    if (clusterLoadConfig(server.cluster.configfile) == REDIS_ERR) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */
         redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
             server.cluster.myself->name);
         saveconf = 1;
     }
     clusterAddNode(server.cluster.myself);
-    if (saveconf) {
-        if (clusterSaveConfig("redis-cluster.conf") == -1) {
-            redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
-            exit(1);
-        }
-    }
+    if (saveconf) clusterSaveConfigOrDie();
     /* We need a listening TCP port for our cluster messaging needs */
     server.cfd = anetTcpServer(server.neterr,
             server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
@@ -910,6 +913,7 @@ sds clusterGenNodesDescription(void) {
     sds ci = sdsempty();
     dictIterator *di;
     dictEntry *de;
+    int j, start;
 
     di = dictGetIterator(server.cluster.nodes);
     while((de = dictNext(di)) != NULL) {
@@ -939,11 +943,32 @@ sds clusterGenNodesDescription(void) {
             ci = sdscatprintf(ci,"- ");
 
         /* Latency from the POV of this node, link status */
-        ci = sdscatprintf(ci,"%ld %ld %s\n",
+        ci = sdscatprintf(ci,"%ld %ld %s",
             (long) node->ping_sent,
             (long) node->pong_received,
             node->link ? "connected" : "disconnected");
+
+        /* Slots served by this instance */
+        start = -1;
+        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+            int bit;
+
+            if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
+                if (start == -1) start = j;
+            }
+            if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
+                if (j == REDIS_CLUSTER_SLOTS-1) j++;
+
+                if (start == j-1) {
+                    ci = sdscatprintf(ci," %d",start);
+                } else {
+                    ci = sdscatprintf(ci," %d-%d",start,j-1);
+                }
+                start = -1;
+            }
+        }
     }
+    ci = sdscatlen(ci,"\n",1);
     dictReleaseIterator(di);
     return ci;
 }