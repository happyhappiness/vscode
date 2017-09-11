@@ -128,8 +128,8 @@ int clusterLoadConfig(char *filename) {
                 if (strcasecmp(argv[j],"currentEpoch") == 0) {
                     server.cluster->currentEpoch =
                             strtoull(argv[j+1],NULL,10);
-                } else if (strcasecmp(argv[j],"last_vote_epoch") == 0) {
-                    server.cluster->last_vote_epoch =
+                } else if (strcasecmp(argv[j],"lastVoteEpoch") == 0) {
+                    server.cluster->lastVoteEpoch =
                             strtoull(argv[j+1],NULL,10);
                 } else {
                     redisLog(REDIS_WARNING,
@@ -281,11 +281,11 @@ int clusterSaveConfig(int do_fsync) {
     int fd;
 
     /* Get the nodes description and concatenate our "vars" directive to
-     * save currentEpoch and last_vote_epoch. */
+     * save currentEpoch and lastVoteEpoch. */
     ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
-    ci = sdscatprintf(ci,"vars currentEpoch %llu last_vote_epoch %llu\n",
+    ci = sdscatprintf(ci,"vars currentEpoch %llu lastVoteEpoch %llu\n",
         (unsigned long long) server.cluster->currentEpoch,
-        (unsigned long long) server.cluster->last_vote_epoch);
+        (unsigned long long) server.cluster->lastVoteEpoch);
     content_size = sdslen(ci);
     
     if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT,0644))
@@ -339,7 +339,7 @@ void clusterInit(void) {
     server.cluster->failover_auth_count = 0;
     server.cluster->failover_auth_rank = 0;
     server.cluster->failover_auth_epoch = 0;
-    server.cluster->last_vote_epoch = 0;
+    server.cluster->lastVoteEpoch = 0;
     server.cluster->stats_bus_messages_sent = 0;
     server.cluster->stats_bus_messages_received = 0;
     memset(server.cluster->slots,0, sizeof(server.cluster->slots));
@@ -2134,7 +2134,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     if (requestCurrentEpoch < server.cluster->currentEpoch) return;
 
     /* I already voted for this epoch? Return ASAP. */
-    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;
+    if (server.cluster->lastVoteEpoch == server.cluster->currentEpoch) return;
 
     /* Node must be a slave and its master down.
      * The master can be non failing if the request is flagged
@@ -2166,7 +2166,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
 
     /* We can vote for this slave. */
     clusterSendFailoverAuth(node);
-    server.cluster->last_vote_epoch = server.cluster->currentEpoch;
+    server.cluster->lastVoteEpoch = server.cluster->currentEpoch;
     node->slaveof->voted_time = mstime();
 }
 