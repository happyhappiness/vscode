         addReply(c,shared.czero);
         return;
     }
 
     /* If the source key has the wrong type, or the destination key
      * is set and has the wrong type, return with an error. */
-    if (checkType(c,srcset,REDIS_SET) ||
-        (dstset && checkType(c,dstset,REDIS_SET))) return;
+    if (checkType(c,srcset,OBJ_SET) ||
+        (dstset && checkType(c,dstset,OBJ_SET))) return;
 
     /* If srcset and dstset are equal, SMOVE is a no-op */
     if (srcset == dstset) {
         addReply(c,setTypeIsMember(srcset,ele) ? shared.cone : shared.czero);
         return;
     }
 
     /* If the element cannot be removed from the src set, return 0. */
     if (!setTypeRemove(srcset,ele)) {
         addReply(c,shared.czero);
         return;
     }
-    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"srem",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_SET,"srem",c->argv[1],c->db->id);
 
     /* Remove the src set from the database when empty */
     if (setTypeSize(srcset) == 0) {
         dbDelete(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
     }
     signalModifiedKey(c->db,c->argv[1]);
     signalModifiedKey(c->db,c->argv[2]);
     server.dirty++;
 
     /* Create the destination set when it doesn't exist */
