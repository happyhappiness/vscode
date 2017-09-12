@@ -34,11 +34,32 @@ void clusterGetRandomName(char *p) {
 
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
+    char *line;
+    int maxline;
    
-    return REDIS_ERR;
     if (fp == NULL) return REDIS_ERR;
+
+    /* Parse the file. Note that single liens of the cluster config file can
+     * be really long as they include all the hash slots of the node.
+     * This means in the worst possible case REDIS_CLUSTER_SLOTS/2 integers.
+     * To simplify we allocate 1024+REDIS_CLUSTER_SLOTS*16 bytes per line. */
+    maxline = 1024+REDIS_CLUSTER_SLOTS*16;
+    line = zmalloc(maxline);
+    while(fgets(line,maxline,fp) != NULL) {
+        int argc;
+        sds *argv = sdssplitargs(line,&argc);
+
+        printf("Node: %s\n", argv[0]);
+
+        sdssplitargs_free(argv,argc);
+    }
+    zfree(line);
     fclose(fp);
 
+    /* Config sanity check */
+    /* TODO: check that myself is set. */
+    return REDIS_ERR;
+
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
         server.cluster.myself->name);
     return REDIS_OK;
@@ -57,8 +78,8 @@ int clusterSaveConfig(void) {
     sds ci = clusterGenNodesDescription();
     int fd;
     
-    if ((fd = open(server.cluster.configfile,O_WRONLY|O_CREAT,0644)) == -1)
-        goto err;
+    if ((fd = open(server.cluster.configfile,O_WRONLY|O_CREAT|O_TRUNC,0644))
+        == -1) goto err;
     if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
     close(fd);
     sdsfree(ci);
@@ -337,6 +358,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
                 /* Broadcast the failing node name to everybody */
                 clusterSendFail(node->name);
                 clusterUpdateState();
+                clusterSaveConfigOrDie();
             }
         } else {
             /* If it's not in NOADDR state and we don't have it, we
@@ -522,7 +544,10 @@ int clusterProcessPacket(clusterLink *link) {
         clusterProcessGossipSection(hdr,link);
 
         /* Update the cluster state if needed */
-        if (update) clusterUpdateState();
+        if (update) {
+            clusterUpdateState();
+            clusterSaveConfigOrDie();
+        }
     } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
         clusterNode *failing;
 
@@ -534,6 +559,7 @@ int clusterProcessPacket(clusterLink *link) {
             failing->flags |= REDIS_NODE_FAIL;
             failing->flags &= ~REDIS_NODE_PFAIL;
             clusterUpdateState();
+            clusterSaveConfigOrDie();
         }
     } else {
         redisLog(REDIS_NOTICE,"Received unknown packet type: %d", type);
@@ -1047,6 +1073,7 @@ void clusterCommand(redisClient *c) {
         }
         zfree(slots);
         clusterUpdateState();
+        clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         char *statestr[] = {"ok","fail","needhelp"};