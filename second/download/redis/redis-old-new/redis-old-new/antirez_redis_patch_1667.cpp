@@ -1168,6 +1168,44 @@ void clusterCommand(redisClient *c) {
         clusterUpdateState();
         clusterSaveConfigOrDie();
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
+        /* SETSLOT 10 MIGRATING <instance ID> */
+        /* SETSLOT 10 IMPORTING <instance ID> */
+        /* SETSLOT 10 STABLE */
+        long long aux;
+        unsigned int slot;
+        clusterNode *n;
+
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&aux,NULL) != REDIS_OK)
+            return;
+        if (aux < 0 || aux >= REDIS_CLUSTER_SLOTS) {
+            addReplyError(c,"Slot out of range");
+            return;
+        }
+        slot = (unsigned int) aux;
+        if (server.cluster.slots[slot] != server.cluster.myself) {
+            addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
+            return;
+        }
+        if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
+            if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
+                addReplyErrorFormat(c,"I don't know about node %s",
+                    (char*)c->argv[4]->ptr);
+                return;
+            }
+            server.cluster.migrating_slots_to[slot] = n;
+        } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
+            if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
+                addReplyErrorFormat(c,"I don't know about node %s",
+                    (char*)c->argv[3]->ptr);
+                return;
+            }
+            server.cluster.importing_slots_from[slot] = n;
+        } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
+            server.cluster.importing_slots_from[slot] = NULL;
+        } else {
+            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         char *statestr[] = {"ok","fail","needhelp"};
         int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;
@@ -1211,8 +1249,7 @@ void clusterCommand(redisClient *c) {
         addReplyLongLong(c,keyHashSlot(key,sdslen(key)));
     } else if (!strcasecmp(c->argv[1]->ptr,"getkeysinslot") && c->argc == 4) {
         long long maxkeys, slot;
-        unsigned int numkeys;
-        int j;
+        unsigned int numkeys, j;
         robj **keys;
 
         if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)