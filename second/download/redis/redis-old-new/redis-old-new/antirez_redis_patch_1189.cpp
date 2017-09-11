@@ -1534,7 +1534,7 @@ void clusterCommand(redisClient *c) {
             if (server.cluster->slots[slot] == server.cluster->myself &&
                 n != server.cluster->myself)
             {
-                if (CountKeysInSlot(slot) != 0) {
+                if (countKeysInSlot(slot) != 0) {
                     addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                     return;
                 }
@@ -1619,7 +1619,7 @@ void clusterCommand(redisClient *c) {
         }
 
         keys = zmalloc(sizeof(robj*)*maxkeys);
-        numkeys = GetKeysInSlot(slot, keys, maxkeys);
+        numkeys = getKeysInSlot(slot, keys, maxkeys);
         addReplyMultiBulkLen(c,numkeys);
         for (j = 0; j < numkeys; j++) addReplyBulk(c,keys[j]);
         zfree(keys);