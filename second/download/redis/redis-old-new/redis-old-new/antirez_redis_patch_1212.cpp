@@ -1680,7 +1680,6 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
 
     if (dbDelete(c->db,dstkey)) {
         signalModifiedKey(c->db,dstkey);
-        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
         touched = 1;
         server.dirty++;
     }
@@ -1700,6 +1699,8 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     } else {
         decrRefCount(dstobj);
         addReply(c,shared.czero);
+        if (touched)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
     }
     zfree(src);
 }