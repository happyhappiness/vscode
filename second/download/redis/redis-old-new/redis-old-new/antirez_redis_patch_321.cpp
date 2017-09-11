@@ -783,6 +783,8 @@ int clusterNodeRemoveSlave(clusterNode *master, clusterNode *slave) {
                         (sizeof(*master->slaves) * remaining_slaves));
             }
             master->numslaves--;
+            if (master->numslaves == 0)
+                master->flags &= ~CLUSTER_NODE_MIGRATE_TO;
             return C_OK;
         }
     }
@@ -799,6 +801,7 @@ int clusterNodeAddSlave(clusterNode *master, clusterNode *slave) {
         sizeof(clusterNode*)*(master->numslaves+1));
     master->slaves[master->numslaves] = slave;
     master->numslaves++;
+    master->flags |= CLUSTER_NODE_MIGRATE_TO;
     return C_OK;
 }
 
@@ -1413,7 +1416,10 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
 void clusterSetNodeAsMaster(clusterNode *n) {
     if (nodeIsMaster(n)) return;
 
-    if (n->slaveof) clusterNodeRemoveSlave(n->slaveof,n);
+    if (n->slaveof) {
+        clusterNodeRemoveSlave(n->slaveof,n);
+        if (n != myself) n->flags |= CLUSTER_NODE_MIGRATE_TO;
+    }
     n->flags &= ~CLUSTER_NODE_SLAVE;
     n->flags |= CLUSTER_NODE_MASTER;
     n->slaveof = NULL;
@@ -1432,8 +1438,8 @@ void clusterSetNodeAsMaster(clusterNode *n) {
  * node (see the function comments for more info).
  *
  * The 'sender' is the node for which we received a configuration update.
- * Sometimes it is not actually the "Sender" of the information, like in the case
- * we receive the info via an UPDATE packet. */
+ * Sometimes it is not actually the "Sender" of the information, like in the
+ * case we receive the info via an UPDATE packet. */
 void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoch, unsigned char *slots) {
     int j;
     clusterNode *curmaster, *newmaster = NULL;
@@ -1764,7 +1770,8 @@ int clusterProcessPacket(clusterLink *link) {
                 if (nodeIsMaster(sender)) {
                     /* Master turned into a slave! Reconfigure the node. */
                     clusterDelNodeSlots(sender);
-                    sender->flags &= ~CLUSTER_NODE_MASTER;
+                    sender->flags &= ~(CLUSTER_NODE_MASTER|
+                                       CLUSTER_NODE_MIGRATE_TO);
                     sender->flags |= CLUSTER_NODE_SLAVE;
 
                     /* Remove the list of slaves from the node. */
@@ -2863,7 +2870,7 @@ void clusterHandleSlaveFailover(void) {
  * Slave migration is the process that allows a slave of a master that is
  * already covered by at least another slave, to "migrate" to a master that
  * is orpaned, that is, left with no working slaves.
- * -------------------------------------------------------------------------- */
+ * ------------------------------------------------------------------------- */
 
 /* This function is responsible to decide if this replica should be migrated
  * to a different (orphaned) master. It is called by the clusterCron() function
@@ -2918,10 +2925,10 @@ void clusterHandleSlaveMigration(int max_slaves) {
 
         /* Only iterate over working masters. */
         if (nodeIsSlave(node) || nodeFailed(node)) continue;
-        /* If this master never had slaves so far, don't migrate. We want
-         * to migrate to a master that remained orphaned, not masters that
-         * were never configured to have slaves. */
-        if (node->numslaves == 0) continue;
+        /* We want to migrate only if this master used to have slaves or
+         * if failed over a master that had slaves. This way we only migrate
+         * to instances that were supposed to have replicas. */
+        if (!(node->flags & CLUSTER_NODE_MIGRATE_TO)) continue;
         okslaves = clusterCountNonFailingSlaves(node);
 
         if (okslaves == 0 && target == NULL && node->numslots > 0)
@@ -3169,9 +3176,12 @@ void clusterCron(void) {
 
             /* A master is orphaned if it is serving a non-zero number of
              * slots, have no working slaves, but used to have at least one
-             * slave. */
-            if (okslaves == 0 && node->numslots > 0 && node->numslaves)
+             * slave, or failed over a master that used to have slaves. */
+            if (okslaves == 0 && node->numslots > 0 &&
+                node->flags & CLUSTER_NODE_MIGRATE_TO)
+            {
                 orphaned_masters++;
+            }
             if (okslaves > max_slaves) max_slaves = okslaves;
             if (nodeIsSlave(myself) && myself->slaveof == node)
                 this_slaves = okslaves;
@@ -3258,6 +3268,7 @@ void clusterCron(void) {
          * the orphaned masters. Note that it does not make sense to try
          * a migration if there is no master with at least *two* working
          * slaves. */
+        if (orphaned_masters) serverLog(LL_WARNING,"0");
         if (orphaned_masters && max_slaves >= 2 && this_slaves == max_slaves)
             clusterHandleSlaveMigration(max_slaves);
     }
@@ -3573,7 +3584,7 @@ void clusterSetMaster(clusterNode *n) {
     serverAssert(myself->numslots == 0);
 
     if (nodeIsMaster(myself)) {
-        myself->flags &= ~CLUSTER_NODE_MASTER;
+        myself->flags &= ~(CLUSTER_NODE_MASTER|CLUSTER_NODE_MIGRATE_TO);
         myself->flags |= CLUSTER_NODE_SLAVE;
         clusterCloseAllSlots();
     } else {
@@ -3596,13 +3607,13 @@ struct redisNodeFlags {
 };
 
 static struct redisNodeFlags redisNodeFlagsTable[] = {
-    {CLUSTER_NODE_MYSELF,    "myself,"},
-    {CLUSTER_NODE_MASTER,    "master,"},
-    {CLUSTER_NODE_SLAVE,     "slave,"},
-    {CLUSTER_NODE_PFAIL,     "fail?,"},
-    {CLUSTER_NODE_FAIL,      "fail,"},
-    {CLUSTER_NODE_HANDSHAKE, "handshake,"},
-    {CLUSTER_NODE_NOADDR,    "noaddr,"}
+    {CLUSTER_NODE_MYSELF,       "myself,"},
+    {CLUSTER_NODE_MASTER,       "master,"},
+    {CLUSTER_NODE_SLAVE,        "slave,"},
+    {CLUSTER_NODE_PFAIL,        "fail?,"},
+    {CLUSTER_NODE_FAIL,         "fail,"},
+    {CLUSTER_NODE_HANDSHAKE,    "handshake,"},
+    {CLUSTER_NODE_NOADDR,       "noaddr,"}
 };
 
 /* Concatenate the comma separated list of node flags to the given SDS