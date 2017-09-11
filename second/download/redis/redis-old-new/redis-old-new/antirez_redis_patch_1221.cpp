@@ -504,11 +504,12 @@ void sortCommand(redisClient *c) {
         }
         if (outputlen) {
             setKey(c->db,storekey,sobj);
-            notifyKeyspaceEvent("sortstore",storekey,c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"sortstore",storekey,
+                                c->db->id);
             server.dirty += outputlen;
         } else if (dbDelete(c->db,storekey)) {
             signalModifiedKey(c->db,storekey);
-            notifyKeyspaceEvent("del",storekey,c->db->id);
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",storekey,c->db->id);
             server.dirty++;
         }
         decrRefCount(sobj);