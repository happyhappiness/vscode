@@ -1276,7 +1276,7 @@ void clusterCommand(redisClient *c) {
             /* CLUSTER SETSLOT <SLOT> STABLE */
             server.cluster.importing_slots_from[slot] = NULL;
             server.cluster.migrating_slots_to[slot] = NULL;
-        } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 4) {
+        } else if (!strcasecmp(c->argv[3]->ptr,"node") && c->argc == 5) {
             /* CLUSTER SETSLOT <SLOT> NODE <NODE ID> */
             clusterNode *n = clusterLookupNode(c->argv[4]->ptr);
 
@@ -1293,7 +1293,7 @@ void clusterCommand(redisClient *c) {
                 keys = zmalloc(sizeof(robj*)*1);
                 numkeys = GetKeysInSlot(slot, keys, 1);
                 zfree(keys);
-                if (numkeys == 0) {
+                if (numkeys != 0) {
                     addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                     return;
                 }