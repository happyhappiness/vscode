@@ -1141,6 +1141,18 @@ sds clusterGenNodesDescription(void) {
     return ci;
 }
 
+int getSlotOrReply(redisClient *c, robj *o) {
+    long long slot;
+
+    if (getLongLongFromObject(o,&slot) != REDIS_OK ||
+        slot < 0 || slot > REDIS_CLUSTER_SLOTS)
+    {
+        addReplyError(c,"Invalid or out of range slot");
+        return -1;
+    }
+    return (int) slot;
+}
+
 void clusterCommand(redisClient *c) {
     if (server.cluster_enabled == 0) {
         addReplyError(c,"This instance has cluster support disabled");
@@ -1180,28 +1192,24 @@ void clusterCommand(redisClient *c) {
         decrRefCount(o);
     } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
                !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3) {
-        int j;
-        long long slot;
+        int j, slot;
         unsigned char *slots = zmalloc(REDIS_CLUSTER_SLOTS);
         int del = !strcasecmp(c->argv[1]->ptr,"delslots");
 
         memset(slots,0,REDIS_CLUSTER_SLOTS);
         /* Check that all the arguments are parsable and that all the
          * slots are not already busy. */
         for (j = 2; j < c->argc; j++) {
-            if (getLongLongFromObject(c->argv[j],&slot) != REDIS_OK ||
-                slot < 0 || slot > REDIS_CLUSTER_SLOTS)
-            {
-                addReplyError(c,"Invalid or out of range slot index");
+            if ((slot = getSlotOrReply(c,c->argv[j])) == -1) {
                 zfree(slots);
                 return;
             }
             if (del && server.cluster.slots[slot] == NULL) {
-                addReplyErrorFormat(c,"Slot %lld is already unassigned", slot);
+                addReplyErrorFormat(c,"Slot %d is already unassigned", slot);
                 zfree(slots);
                 return;
             } else if (!del && server.cluster.slots[slot]) {
-                addReplyErrorFormat(c,"Slot %lld is already busy", slot);
+                addReplyErrorFormat(c,"Slot %d is already busy", slot);
                 zfree(slots);
                 return;
             }
@@ -1228,17 +1236,11 @@ void clusterCommand(redisClient *c) {
         /* SETSLOT 10 MIGRATING <instance ID> */
         /* SETSLOT 10 IMPORTING <instance ID> */
         /* SETSLOT 10 STABLE */
-        long long aux;
-        unsigned int slot;
+        int slot;
         clusterNode *n;
 
-        if (getLongLongFromObjectOrReply(c,c->argv[2],&aux,NULL) != REDIS_OK)
-            return;
-        if (aux < 0 || aux >= REDIS_CLUSTER_SLOTS) {
-            addReplyError(c,"Slot out of range");
-            return;
-        }
-        slot = (unsigned int) aux;
+        if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;
+
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
             if (server.cluster.slots[slot] != server.cluster.myself) {
                 addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
@@ -1263,8 +1265,33 @@ void clusterCommand(redisClient *c) {
             }
             server.cluster.importing_slots_from[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
+            /* CLUSTER SETSLOT <SLOT> STABLE */
             server.cluster.importing_slots_from[slot] = NULL;
             server.cluster.migrating_slots_to[slot] = NULL;
+        } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 4) {
+            /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
+            clusterNode *n = clusterLookupNode(c->argv[4]->ptr);
+
+            if (!n) addReplyErrorFormat(c,"Unknown node %s",
+                (char*)c->argv[4]->ptr);
+            /* If this hash slot was served by 'myself' before to switch
+             * make sure there are no longer local keys for this hash slot. */
+            if (server.cluster.slots[slot] == server.cluster.myself &&
+                n != server.cluster.myself)
+            {
+                int numkeys;
+                robj **keys;
+
+                keys = zmalloc(sizeof(robj*)*1);
+                numkeys = GetKeysInSlot(slot, keys, 1);
+                zfree(keys);
+                if (numkeys == 0) {
+                    addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
+                    return;
+                }
+            }
+            clusterDelSlot(slot);
+            clusterAddSlot(n,slot);
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;