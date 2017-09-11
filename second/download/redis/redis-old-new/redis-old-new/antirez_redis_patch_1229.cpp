@@ -504,9 +504,11 @@ void sortCommand(redisClient *c) {
         }
         if (outputlen) {
             setKey(c->db,storekey,sobj);
+            notifyKeyspaceEvent("sortstore",storekey,c->db->id);
             server.dirty += outputlen;
         } else if (dbDelete(c->db,storekey)) {
             signalModifiedKey(c->db,storekey);
+            notifyKeyspaceEvent("del",storekey,c->db->id);
             server.dirty++;
         }
         decrRefCount(sobj);
@@ -525,5 +527,3 @@ void sortCommand(redisClient *c) {
     }
     zfree(vector);
 }
-
-