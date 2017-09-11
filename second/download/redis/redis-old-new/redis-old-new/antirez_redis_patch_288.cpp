@@ -168,7 +168,12 @@ int clusterLoadConfig(char *filename) {
         if ((p = strrchr(argv[1],':')) == NULL) goto fmterr;
         *p = '\0';
         memcpy(n->ip,argv[1],strlen(argv[1])+1);
+        char *busp = strchr(p+1,':');
+        if (busp) *busp = '\0';
         n->port = atoi(p+1);
+        /* In older versions of nodes.conf the bus port is missing. In this case
+         * we set it to the default offset of 10000 from the base port. */
+        n->cport = busp ? atoi(busp+1) : n->port + CLUSTER_PORT_INCR;
 
         /* Parse flags */
         p = s = argv[2];
@@ -3731,10 +3736,11 @@ sds clusterGenNodeDescription(clusterNode *node) {
     sds ci;
 
     /* Node coordinates */
-    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
+    ci = sdscatprintf(sdsempty(),"%.40s %s:%d:%d ",
         node->name,
         node->ip,
-        node->port);
+        node->port,
+        node->cport);
 
     /* Flags */
     ci = representClusterNodeFlags(ci, node->flags);