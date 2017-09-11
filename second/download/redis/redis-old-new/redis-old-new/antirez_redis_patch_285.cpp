@@ -168,13 +168,17 @@ int clusterLoadConfig(char *filename) {
         if ((p = strrchr(argv[1],':')) == NULL) goto fmterr;
         *p = '\0';
         memcpy(n->ip,argv[1],strlen(argv[1])+1);
-        // this_is_broken();
-        char *busp = strchr(p+1,':');
-        if (busp) *busp = '\0';
-        n->port = atoi(p+1);
-        /* In older versions of nodes.conf the bus port is missing. In this case
-         * we set it to the default offset of 10000 from the base port. */
-        n->cport = busp ? atoi(busp+1) : n->port + CLUSTER_PORT_INCR;
+        char *port = p+1;
+        char *busp = strchr(port,'@');
+        if (busp) {
+            *busp = '\0';
+            busp++;
+        }
+        n->port = atoi(port);
+        /* In older versions of nodes.conf the "@busport" part is missing.
+         * In this case we set it to the default offset of 10000 from the
+         * base port. */
+        n->cport = busp ? atoi(busp) : n->port + CLUSTER_PORT_INCR;
 
         /* Parse flags */
         p = s = argv[2];
@@ -1316,7 +1320,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         sds ci;
 
         ci = representClusterNodeFlags(sdsempty(), flags);
-        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d:%d %s",
+        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d@%d %s",
             g->nodename,
             g->ip,
             ntohs(g->port),
@@ -3742,7 +3746,7 @@ sds clusterGenNodeDescription(clusterNode *node) {
     sds ci;
 
     /* Node coordinates */
-    ci = sdscatprintf(sdsempty(),"%.40s %s:%d:%d ",
+    ci = sdscatprintf(sdsempty(),"%.40s %s:%d@%d ",
         node->name,
         node->ip,
         node->port,