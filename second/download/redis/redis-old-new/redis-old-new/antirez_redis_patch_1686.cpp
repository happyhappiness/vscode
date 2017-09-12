@@ -11,6 +11,8 @@ void clusterSendFail(char *nodename);
 void clusterUpdateState(void);
 int clusterNodeGetSlotBit(clusterNode *n, int slot);
 sds clusterGenNodesDescription(void);
+clusterNode *clusterLookupNode(char *name);
+int clusterNodeAddSlave(clusterNode *master, clusterNode *slave);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -35,7 +37,7 @@ void clusterGetRandomName(char *p) {
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
     char *line;
-    int maxline;
+    int maxline, j;
    
     if (fp == NULL) return REDIS_ERR;
 
@@ -48,18 +50,81 @@ int clusterLoadConfig(char *filename) {
     while(fgets(line,maxline,fp) != NULL) {
         int argc;
         sds *argv = sdssplitargs(line,&argc);
+        clusterNode *n, *master;
+        char *p, *s;
+
+        /* Create this node if it does not exist */
+        n = clusterLookupNode(argv[0]);
+        if (!n) {
+            n = createClusterNode(argv[0],0);
+            clusterAddNode(n);
+        }
+        /* Address and port */
+        if ((p = strchr(argv[1],':')) == NULL) goto fmterr;
+        *p = '\0';
+        memcpy(n->ip,argv[1],strlen(argv[1])+1);
+        n->port = atoi(p+1);
+
+        /* Parse flags */
+        p = s = argv[2];
+        while(p) {
+            p = strchr(s,',');
+            if (p) *p = '\0';
+            if (!strcasecmp(s,"myself")) {
+                redisAssert(server.cluster.myself == NULL);
+                server.cluster.myself = n;
+                n->flags |= REDIS_NODE_MYSELF;
+            } else if (!strcasecmp(s,"master")) {
+                n->flags |= REDIS_NODE_MASTER;
+            } else if (!strcasecmp(s,"slave")) {
+                n->flags |= REDIS_NODE_SLAVE;
+            } else if (!strcasecmp(s,"fail?")) {
+                n->flags |= REDIS_NODE_PFAIL;
+            } else if (!strcasecmp(s,"fail")) {
+                n->flags |= REDIS_NODE_FAIL;
+            } else if (!strcasecmp(s,"handshake")) {
+                n->flags |= REDIS_NODE_HANDSHAKE;
+            } else if (!strcasecmp(s,"noaddr")) {
+                n->flags |= REDIS_NODE_NOADDR;
+            } else {
+                redisPanic("Unknown flag in redis cluster config file");
+            }
+            if (p) s = p+1;
+        }
+
+        /* Get master if any. Set the master and populate master's
+         * slave list. */
+        if (argv[3][0] != '-') {
+            master = clusterLookupNode(argv[3]);
+            if (!master) {
+                master = createClusterNode(argv[3],0);
+                clusterAddNode(master);
+            }
+            n->slaveof = master;
+            clusterNodeAddSlave(master,n);
+        }
 
-        printf("Node: %s\n", argv[0]);
+        /* Populate hash slots served by this instance. */
+        for (j = 7; j < argc; j++) {
+            int start, stop;
+
+            if ((p = strchr(argv[j],'-')) != NULL) {
+                *p = '\0';
+                start = atoi(argv[j]);
+                stop = atoi(p+1);
+            } else {
+                start = stop = atoi(argv[j]);
+            }
+            while(start <= stop) clusterAddSlot(n, start++);
+        }
 
         sdssplitargs_free(argv,argc);
     }
     zfree(line);
     fclose(fp);
 
     /* Config sanity check */
-    /* TODO: check that myself is set. */
-    return REDIS_ERR;
-
+    redisAssert(server.cluster.myself != NULL);
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
         server.cluster.myself->name);
     return REDIS_OK;
@@ -100,7 +165,7 @@ void clusterSaveConfigOrDie(void) {
 void clusterInit(void) {
     int saveconf = 0;
 
-    server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
+    server.cluster.myself = NULL;
     server.cluster.state = REDIS_CLUSTER_FAIL;
     server.cluster.nodes = dictCreate(&clusterNodesDictType,NULL);
     server.cluster.node_timeout = 15;
@@ -113,6 +178,7 @@ void clusterInit(void) {
     if (clusterLoadConfig(server.cluster.configfile) == REDIS_ERR) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */
+        server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
         redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
             server.cluster.myself->name);
         clusterAddNode(server.cluster.myself);