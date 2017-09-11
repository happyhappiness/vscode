@@ -3631,6 +3631,7 @@ void clusterCommand(redisClient *c) {
             sdsfree(ni);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"failover") && c->argc == 2) {
+        /* CLUSTER FAILOVER */
         if (nodeIsMaster(myself)) {
             addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
             return;
@@ -3646,6 +3647,36 @@ void clusterCommand(redisClient *c) {
         clusterSendMFStart(myself->slaveof);
         redisLog(REDIS_WARNING,"Manual failover user request accepted.");
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"set-config-epoch") && c->argc == 3)
+    {
+        /* CLUSTER SET-CONFIG-EPOCH <epoch>
+         *
+         * The user is allowed to set the config epoch only when a node is
+         * totally fresh: no config epoch, no other known node, and so forth.
+         * This happens at cluster creation time to start with a cluster where
+         * every node has a different node ID, without to rely on the conflicts
+         * resolution system which is too slow when a big cluster is created. */
+        long long epoch;
+
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != REDIS_OK)
+            return;
+
+        if (epoch < 0) {
+            addReplyErrorFormat(c,"Invalid config epoch specified: %lld",epoch);
+        } else if (dictSize(server.cluster->nodes) > 1) {
+            addReplyError(c,"The user can assign a config epoch only when the "
+                            "node does not know any other node.");
+        } else if (myself->configEpoch != 0) {
+            addReplyError(c,"Node config epoch is already non-zero");
+        } else {
+            myself->configEpoch = epoch;
+            /* No need to fsync the config here since in the unlucky event
+             * of a failure to persist the config, the conflict resolution code
+             * will assign an unique config to this node. */
+            clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|
+                                 CLUSTER_TODO_SAVE_CONFIG);
+            addReply(c,shared.ok);
+        }
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
     }