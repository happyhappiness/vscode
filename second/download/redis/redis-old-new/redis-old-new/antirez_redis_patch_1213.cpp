@@ -706,7 +706,7 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
     if (dstkey) {
         /* Store the resulting set into the target, if the intersection
          * is not an empty set. */
-        dbDelete(c->db,dstkey);
+        int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
@@ -715,6 +715,9 @@ void sinterGenericCommand(redisClient *c, robj **setkeys, unsigned long setnum,
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
+            if (deleted)
+                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                    dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
         server.dirty++;
@@ -873,7 +876,7 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
     } else {
         /* If we have a target key where to store the resulting set
          * create this key with the result set inside */
-        dbDelete(c->db,dstkey);
+        int deleted = dbDelete(c->db,dstkey);
         if (setTypeSize(dstset) > 0) {
             dbAdd(c->db,dstkey,dstset);
             addReplyLongLong(c,setTypeSize(dstset));
@@ -883,6 +886,9 @@ void sunionDiffGenericCommand(redisClient *c, robj **setkeys, int setnum, robj *
         } else {
             decrRefCount(dstset);
             addReply(c,shared.czero);
+            if (deleted)
+                notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
+                    dstkey,c->db->id);
         }
         signalModifiedKey(c->db,dstkey);
         server.dirty++;