@@ -491,6 +491,41 @@ int clusterAddNode(clusterNode *node) {
     return (retval == DICT_OK) ? REDIS_OK : REDIS_ERR;
 }
 
+/* Remove a node from the cluster:
+ * 1) Mark all the nodes handled by it as unassigned.
+ * 2) Remove all the failure reports sent by this node.
+ * 3) Free the node, that will in turn remove it from the hash table
+ *    and from the list of slaves of its master, if it is a slave node.
+ */
+void clusterDelNode(clusterNode *delnode) {
+    int j;
+    dictIterator *di;
+    dictEntry *de;
+
+    /* 1) Mark slots as unassigned. */
+    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        if (server.cluster->importing_slots_from[j] == delnode)
+            server.cluster->importing_slots_from[j] = NULL;
+        if (server.cluster->migrating_slots_to[j] == delnode)
+            server.cluster->migrating_slots_to[j] = NULL;
+        if (server.cluster->slots[j] == delnode)
+            clusterDelSlot(j);
+    }
+
+    /* 2) Remove failure reports. */
+    di = dictGetIterator(server.cluster->nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetVal(de);
+
+        if (node == delnode) continue;
+        clusterNodeDelFailureReport(node,delnode);
+    }
+    dictReleaseIterator(di);
+
+    /* 3) Free the node, unlinking it from the cluster. */
+    freeClusterNode(delnode);
+}
+
 /* Node lookup by name */
 clusterNode *clusterLookupNode(char *name) {
     sds s = sdsnewlen(name, REDIS_CLUSTER_NAMELEN);
@@ -1781,6 +1816,18 @@ void clusterCommand(redisClient *c) {
         addReplyMultiBulkLen(c,numkeys);
         for (j = 0; j < numkeys; j++) addReplyBulk(c,keys[j]);
         zfree(keys);
+    } else if (!strcasecmp(c->argv[1]->ptr,"forget") && c->argc == 3) {
+        /* CLUSTER FORGET <NODE ID> */
+        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);
+
+        if (!n) {
+            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
+            return;
+        }
+        clusterDelNode(n);
+        clusterUpdateState();
+        clusterSaveConfigOrDie();
+        addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
     }