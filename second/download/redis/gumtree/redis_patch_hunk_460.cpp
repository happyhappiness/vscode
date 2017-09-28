          * slot 'j' populated even if we are not importing it, nor we are
          * assigned to this slot. Fix this condition. */
 
         update_config++;
         /* Case A: slot is unassigned. Take responsibility for it. */
         if (server.cluster->slots[j] == NULL) {
-            redisLog(REDIS_WARNING, "I have keys for unassigned slot %d. "
+            serverLog(LL_WARNING, "I have keys for unassigned slot %d. "
                                     "Taking responsibility for it.",j);
             clusterAddSlot(myself,j);
         } else {
-            redisLog(REDIS_WARNING, "I have keys for slot %d, but the slot is "
+            serverLog(LL_WARNING, "I have keys for slot %d, but the slot is "
                                     "assigned to another node. "
                                     "Setting it to importing state.",j);
             server.cluster->importing_slots_from[j] = server.cluster->slots[j];
         }
     }
     if (update_config) clusterSaveConfigOrDie(1);
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* -----------------------------------------------------------------------------
  * SLAVE nodes handling
  * -------------------------------------------------------------------------- */
 
 /* Set the specified node 'n' as master for this node.
  * If this node is currently a master, it is turned into a slave. */
 void clusterSetMaster(clusterNode *n) {
-    redisAssert(n != myself);
-    redisAssert(myself->numslots == 0);
+    serverAssert(n != myself);
+    serverAssert(myself->numslots == 0);
 
     if (nodeIsMaster(myself)) {
-        myself->flags &= ~(REDIS_NODE_MASTER|REDIS_NODE_MIGRATE_TO);
-        myself->flags |= REDIS_NODE_SLAVE;
+        myself->flags &= ~(CLUSTER_NODE_MASTER|CLUSTER_NODE_MIGRATE_TO);
+        myself->flags |= CLUSTER_NODE_SLAVE;
         clusterCloseAllSlots();
     } else {
         if (myself->slaveof)
             clusterNodeRemoveSlave(myself->slaveof,myself);
     }
     myself->slaveof = n;
