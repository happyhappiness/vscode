@@ -671,6 +671,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     node->port = 0;
     node->fail_reports = listCreate();
     node->voted_time = 0;
+    node->orphaned_time = 0;
     node->repl_offset_time = 0;
     node->repl_offset = 0;
     listSetFreeMethod(node->fail_reports,zfree);
@@ -2910,30 +2911,44 @@ void clusterHandleSlaveMigration(int max_slaves) {
 
     /* Step 3: Idenitfy a candidate for migration, and check if among the
      * masters with the greatest number of ok slaves, I'm the one with the
-     * smaller node ID.
+     * smallest node ID (the "candidate slave").
      *
-     * Note that this means that eventually a replica migration will occurr
+     * Note: this means that eventually a replica migration will occurr
      * since slaves that are reachable again always have their FAIL flag
-     * cleared. At the same time this does not mean that there are no
-     * race conditions possible (two slaves migrating at the same time), but
-     * this is extremely unlikely to happen, and harmless. */
+     * cleared, so eventually there must be a candidate. At the same time
+     * this does not mean that there are no race conditions possible (two
+     * slaves migrating at the same time), but this is unlikely to
+     * happen, and harmless when happens. */
     candidate = myself;
     di = dictGetSafeIterator(server.cluster->nodes);
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
-        int okslaves;
+        int okslaves = 0, is_orphaned = 1;
 
-        /* Only iterate over working masters. */
-        if (nodeIsSlave(node) || nodeFailed(node)) continue;
-        /* We want to migrate only if this master used to have slaves or
-         * if failed over a master that had slaves. This way we only migrate
-         * to instances that were supposed to have replicas. */
-        if (!(node->flags & CLUSTER_NODE_MIGRATE_TO)) continue;
-        okslaves = clusterCountNonFailingSlaves(node);
+        /* We want to migrate only if this master is working, orphaned, and
+         * used to have slaves or if failed over a master that had slaves
+         * (MIGRATE_TO flag). This way we only migrate to instances that were
+         * supposed to have replicas. */
+        if (nodeIsSlave(node) || nodeFailed(node)) is_orphaned = 0;
+        if (!(node->flags & CLUSTER_NODE_MIGRATE_TO)) is_orphaned = 0;
 
-        if (okslaves == 0 && target == NULL && node->numslots > 0)
-            target = node;
+        /* Check number of working slaves. */
+        if (nodeIsMaster(node)) okslaves = clusterCountNonFailingSlaves(node);
+        if (okslaves > 0) is_orphaned = 0;
 
+        if (is_orphaned) {
+            if (!target && node->numslots > 0) target = node;
+
+            /* Track the starting time of the orphaned condition for this
+             * master. */
+            if (!node->orphaned_time) node->orphaned_time = mstime();
+        } else {
+            node->orphaned_time = 0;
+        }
+
+        /* Check if I'm the slave candidate for the migration: attached
+         * to a master with the maximum number of slaves and with the smallest
+         * node ID. */
         if (okslaves == max_slaves) {
             for (j = 0; j < node->numslaves; j++) {
                 if (memcmp(node->slaves[j]->name,
@@ -2948,8 +2963,13 @@ void clusterHandleSlaveMigration(int max_slaves) {
     dictReleaseIterator(di);
 
     /* Step 4: perform the migration if there is a target, and if I'm the
-     * candidate. */
-    if (target && candidate == myself) {
+     * candidate, but only if the master is continuously orphaned for a
+     * couple of seconds, so that during failovers, we give some time to
+     * the natural slaves of this instance to advertise their switch from
+     * the old master to the new one. */
+    if (target && candidate == myself &&
+        (mstime()-target->orphaned_time) > CLUSTER_SLAVE_MIGRATION_DELAY)
+    {
         serverLog(LL_WARNING,"Migrating to orphaned master %.40s",
             target->name);
         clusterSetMaster(target);