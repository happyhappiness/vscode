@@ -968,7 +968,8 @@ void zaddGenericCommand(redisClient *c, int incr) {
     zfree(scores);
     if (added || updated) {
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(incr ? "zincr" : "zadd", key, c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
+            incr ? "zincr" : "zadd", key, c->db->id);
     }
 }
 
@@ -1029,8 +1030,9 @@ void zremCommand(redisClient *c) {
     }
 
     if (deleted) {
-        notifyKeyspaceEvent("zrem",key,c->db->id);
-        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrem",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
@@ -1073,8 +1075,9 @@ void zremrangebyscoreCommand(redisClient *c) {
 
     if (deleted) {
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent("zrembyscore",key,c->db->id);
-        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyscore",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
     }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
@@ -1132,8 +1135,9 @@ void zremrangebyrankCommand(redisClient *c) {
 
     if (deleted) {
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent("zrembyrank",key,c->db->id);
-        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyrank",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
     }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
@@ -1676,7 +1680,7 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
 
     if (dbDelete(c->db,dstkey)) {
         signalModifiedKey(c->db,dstkey);
-        notifyKeyspaceEvent("del",dstkey,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
         touched = 1;
         server.dirty++;
     }
@@ -1689,7 +1693,7 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
         dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c,zsetLength(dstobj));
         if (!touched) signalModifiedKey(c->db,dstkey);
-        notifyKeyspaceEvent(
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
             (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
             dstkey,c->db->id);
         server.dirty++;