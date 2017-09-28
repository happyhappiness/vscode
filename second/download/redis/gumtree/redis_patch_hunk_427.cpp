  */
 void clusterHandleConfigEpochCollision(clusterNode *sender) {
     /* Prerequisites: nodes have the same configEpoch and are both masters. */
     if (sender->configEpoch != myself->configEpoch ||
         !nodeIsMaster(sender) || !nodeIsMaster(myself)) return;
     /* Don't act if the colliding node has a smaller Node ID. */
-    if (memcmp(sender->name,myself->name,REDIS_CLUSTER_NAMELEN) <= 0) return;
+    if (memcmp(sender->name,myself->name,CLUSTER_NAMELEN) <= 0) return;
     /* Get the next ID available at the best of this node knowledge. */
     server.cluster->currentEpoch++;
     myself->configEpoch = server.cluster->currentEpoch;
     clusterSaveConfigOrDie(1);
-    redisLog(REDIS_VERBOSE,
+    serverLog(LL_VERBOSE,
         "WARNING: configEpoch collision with node %.40s."
         " configEpoch set to %llu",
         sender->name,
         (unsigned long long) myself->configEpoch);
 }
 
 /* -----------------------------------------------------------------------------
  * CLUSTER nodes blacklist
  *
  * The nodes blacklist is just a way to ensure that a given node with a given
  * Node ID is not readded before some time elapsed (this time is specified
- * in seconds in REDIS_CLUSTER_BLACKLIST_TTL).
+ * in seconds in CLUSTER_BLACKLIST_TTL).
  *
  * This is useful when we want to remove a node from the cluster completely:
  * when CLUSTER FORGET is called, it also puts the node into the blacklist so
  * that even if we receive gossip messages from other nodes that still remember
  * about the node we want to remove, we don't re-add it before some time.
  *
- * Currently the REDIS_CLUSTER_BLACKLIST_TTL is set to 1 minute, this means
+ * Currently the CLUSTER_BLACKLIST_TTL is set to 1 minute, this means
  * that redis-trib has 60 seconds to send CLUSTER FORGET messages to nodes
  * in the cluster without dealing with the problem of other nodes re-adding
  * back the node to nodes we already sent the FORGET command to.
  *
  * The data structure used is a hash table with an sds string representing
  * the node ID as key, and the time when it is ok to re-add the node as
  * value.
  * -------------------------------------------------------------------------- */
 
-#define REDIS_CLUSTER_BLACKLIST_TTL 60      /* 1 minute. */
+#define CLUSTER_BLACKLIST_TTL 60      /* 1 minute. */
 
 
 /* Before of the addNode() or Exists() operations we always remove expired
  * entries from the black list. This is an O(N) operation but it is not a
  * problem since add / exists operations are called very infrequently and
  * the hash table is supposed to contain very little elements at max.
