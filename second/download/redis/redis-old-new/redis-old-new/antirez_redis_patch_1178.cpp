@@ -1513,7 +1513,7 @@ void clusterSetMaster(clusterNode *n) {
         myself->flags |= REDIS_NODE_SLAVE;
     }
     myself->slaveof = n;
-    /* TODO: actually handle replication to point to the new slave. */
+    replicationSetMaster(n->ip, n->port);
 }
 
 /* -----------------------------------------------------------------------------
@@ -1900,6 +1900,8 @@ void clusterCommand(redisClient *c) {
 
         /* Set the master. */
         clusterSetMaster(n);
+        clusterUpdateState();
+        clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");