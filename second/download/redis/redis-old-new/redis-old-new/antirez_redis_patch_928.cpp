@@ -86,6 +86,7 @@ uint64_t clusterGetMaxEpoch(void) {
         if (node->configEpoch > max) max = node->configEpoch;
     }
     dictReleaseIterator(di);
+    if (max < server.cluster->currentEpoch) max = server.cluster->currentEpoch;
     return max;
 }
 
@@ -1171,6 +1172,68 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
     }
 }
 
+/* This function is called when this node is a master, and we receive from
+ * another master a configuration epoch that is equal to our configuration
+ * epoch.
+ *
+ * BACKGROUND
+ *
+ * It is not possible that different slaves get the same config
+ * epoch during a failover election, because the slaves need to get voted
+ * by a majority. However when we perform a manual resharding of the cluster
+ * the node will assign a configuration epoch to itself without to ask
+ * for agreement. Usually resharding happens when the cluster is working well
+ * and is supervised by the sysadmin, however it is possible for a failover
+ * to happen exactly while the node we are resharding a slot to assigns itself
+ * a new configuration epoch, but before it is able to propagate it.
+ *
+ * So technically it is possible in this condition that two nodes end with
+ * the same configuration epoch.
+ *
+ * Another possibility is that there are bugs in the implementation causing
+ * this to happen.
+ *
+ * Moreover when a new cluster is created, all the nodes start with the same
+ * configEpoch. This collision resolution code allows nodes to automatically
+ * end with a different configEpoch at startup automatically.
+ *
+ * In all the cases, we want a mechanism that resolves this issue automatically
+ * as a safeguard. The same configuration epoch for masters serving different
+ * set of slots is not harmful, but it is if the nodes end serving the same
+ * slots for some reason (manual errors or software bugs) without a proper
+ * failover procedure.
+ *
+ * In general we want a system that eventually always ends with different
+ * masters having different configuration epochs whatever happened, since
+ * nothign is worse than a split-brain condition in a distributed system.
+ *
+ * BEHAVIOR
+ *
+ * When this function gets called, what happens is that if this node
+ * has the lexicographically smaller Node ID compared to the other node
+ * with the conflicting epoch (the 'sender' node), it will assign itself
+ * the greatest configuration epoch currently detected among nodes plus 1.
+ *
+ * This means that even if there are multiple nodes colliding, the node
+ * with the greatest Node ID never moves forward, so eventually all the nodes
+ * end with a different configuration epoch.
+ */
+void clusterHandleConfigEpochCollision(clusterNode *sender) {
+    /* Prerequisites: nodes have the same configEpoch and are both masters. */
+    if (sender->configEpoch != myself->configEpoch ||
+        !nodeIsMaster(sender) || !nodeIsMaster(myself)) return;
+    /* Don't act if the colliding node has a smaller Node ID. */
+    if (memcmp(sender->name,myself->name,REDIS_CLUSTER_NAMELEN) <= 0) return;
+    /* Get the next ID available at the best of this node knowledge. */
+    myself->configEpoch = clusterGetMaxEpoch()+1;
+    clusterSaveConfigOrDie(1);
+    redisLog(REDIS_VERBOSE,
+        "WARNING: configEpoch collision with node %.40s."
+        "Updating my configEpoch to %llu",
+        sender->name,
+        (unsigned long long) myself->configEpoch);
+}
+
 /* When this function is called, there is a packet to process starting
  * at node->rcvbuf. Releasing the buffer is up to the caller, so this
  * function should just handle the higher level stuff of processing the
@@ -1476,6 +1539,15 @@ int clusterProcessPacket(clusterLink *link) {
             }
         }
 
+        /* If our config epoch collides with the sender's try to fix
+         * the problem. */
+        if (sender &&
+            nodeIsMaster(myself) && nodeIsMaster(sender) &&
+            senderConfigEpoch == myself->configEpoch)
+        {
+            clusterHandleConfigEpochCollision(sender);
+        }
+
         /* Get info from the gossip section */
         clusterProcessGossipSection(hdr,link);
     } else if (type == CLUSTERMSG_TYPE_FAIL) {