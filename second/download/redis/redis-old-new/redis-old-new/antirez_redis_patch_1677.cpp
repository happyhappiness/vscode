@@ -994,7 +994,6 @@ int clusterNodeGetSlotBit(clusterNode *n, int slot) {
 int clusterAddSlot(clusterNode *n, int slot) {
     redisAssert(clusterNodeSetSlotBit(n,slot) == 0);
     server.cluster.slots[slot] = n;
-    printf("SLOT %d added to %.40s\n", slot, n->name);
     return REDIS_OK;
 }
 