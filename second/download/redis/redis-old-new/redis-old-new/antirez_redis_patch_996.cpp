@@ -1873,34 +1873,21 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     if (server.cluster->myself->numslots == 0) return;
 
     /* Request epoch must be >= our currentEpoch. */
-    if (requestCurrentEpoch < server.cluster->currentEpoch) {
-        printf("REFUSED BECAUSE OF EPOCH\n");
-        return;
-    }
+    if (requestCurrentEpoch < server.cluster->currentEpoch) return;
 
     /* I already voted for this epoch? Return ASAP. */
-    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) {
-        printf("REFUSED BECAUSE ALREADY VOTED FOR EPOCH\n");
-        return;
-    }
+    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;
 
     /* Node must be a slave and its master down. */
     if (!(node->flags & REDIS_NODE_SLAVE) ||
         master == NULL ||
-        !(master->flags & REDIS_NODE_FAIL))
-    {
-        printf("REFUSED BECAUSE NOT A SLAVE OR MASTER NOT FAIL.\n");
-        return;
-    }
+        !(master->flags & REDIS_NODE_FAIL)) return;
 
     /* We did not voted for a slave about this master for two
      * times the node timeout. This is not strictly needed for correctness
      * of the algorithm but makes the base case more linear. */
     if (mstime() - node->slaveof->voted_time < server.cluster_node_timeout * 2)
-    {
-        printf("REFUSED BECAUSE ALREADY VOTED WITHIN NODE_TIMEOUT*2.\n");
         return;
-    }
 
     /* The slave requesting the vote must have a configEpoch for the claimed
      * slots that is >= the one of the masters currently serving the same
@@ -1912,12 +1899,10 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
         /* If we reached this point we found a slot that in our current slots
          * is served by a master with a greater configEpoch than the one claimed
          * by the slave requesting our vote. Refuse to vote for this slave. */
-        printf("REFUSED BECAUSE SLAVE CONFIG EPOCH FOR SLOTS IS STALE.\n");
         return;
     }
 
     /* We can vote for this slave. */
-    printf("I VOTED.\n");
     clusterSendFailoverAuth(node);
     server.cluster->last_vote_epoch = server.cluster->currentEpoch;
     node->slaveof->voted_time = mstime();