@@ -1849,6 +1849,9 @@ void clusterSetMaster(clusterNode *n) {
         myself->flags &= ~REDIS_NODE_MASTER;
         myself->flags |= REDIS_NODE_SLAVE;
     }
+    /* Clear the promoted flag anyway if we are a slave, to ensure it will
+     * be set only when the node turns into a master because of fail over. */
+    myself->flags &= ~REDIS_NODE_PROMOTED;
     myself->slaveof = n;
     replicationSetMaster(n->ip, n->port);
 }
@@ -2247,7 +2250,6 @@ void clusterCommand(redisClient *c) {
         }
 
         /* Set the master. */
-        server.cluster->myself->flags &= ~REDIS_NODE_PROMOTED;
         clusterSetMaster(n);
         clusterUpdateState();
         clusterSaveConfigOrDie();