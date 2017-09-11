@@ -1014,11 +1014,24 @@ int clusterNodeGetSlotBit(clusterNode *n, int slot) {
  * If the slot is already assigned to another instance this is considered
  * an error and REDIS_ERR is returned. */
 int clusterAddSlot(clusterNode *n, int slot) {
-    redisAssert(clusterNodeSetSlotBit(n,slot) == 0);
+    if (clusterNodeSetSlotBit(n,slot) != 0)
+        return REDIS_ERR;
     server.cluster.slots[slot] = n;
     return REDIS_OK;
 }
 
+/* Delete the specified slot marking it as unassigned.
+ * Returns REDIS_OK if the slot was assigned, otherwise if the slot was
+ * already unassigned REDIS_ERR is returned. */
+int clusterDelSlot(int slot) {
+    clusterNode *n = server.cluster.slots[slot];
+
+    if (!n) return REDIS_ERR;
+    redisAssert(clusterNodeClearSlotBit(n,slot) == 1);
+    server.cluster.slots[slot] = NULL;
+    return REDIS_OK;
+}
+
 /* -----------------------------------------------------------------------------
  * Cluster state evaluation function
  * -------------------------------------------------------------------------- */
@@ -1165,10 +1178,12 @@ void clusterCommand(redisClient *c) {
         o = createObject(REDIS_STRING,ci);
         addReplyBulk(c,o);
         decrRefCount(o);
-    } else if (!strcasecmp(c->argv[1]->ptr,"addslots") && c->argc >= 3) {
+    } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
+               !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3) {
         int j;
         long long slot;
         unsigned char *slots = zmalloc(REDIS_CLUSTER_SLOTS);
+        int del = !strcasecmp(c->argv[1]->ptr,"delslots");
 
         memset(slots,0,REDIS_CLUSTER_SLOTS);
         /* Check that all the arguments are parsable and that all the
@@ -1181,7 +1196,11 @@ void clusterCommand(redisClient *c) {
                 zfree(slots);
                 return;
             }
-            if (server.cluster.slots[slot]) {
+            if (del && server.cluster.slots[slot] == NULL) {
+                addReplyErrorFormat(c,"Slot %lld is already unassigned", slot);
+                zfree(slots);
+                return;
+            } else if (!del && server.cluster.slots[slot]) {
                 addReplyErrorFormat(c,"Slot %lld is already busy", slot);
                 zfree(slots);
                 return;
@@ -1195,7 +1214,8 @@ void clusterCommand(redisClient *c) {
         }
         for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
             if (slots[j]) {
-                int retval = clusterAddSlot(server.cluster.myself,j);
+                int retval = del ?  clusterDelSlot(j) :
+                                    clusterAddSlot(server.cluster.myself,j);
                 
                 redisAssert(retval == REDIS_OK);
             }