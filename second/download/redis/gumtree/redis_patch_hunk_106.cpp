 
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
         checkType(c,zobj,REDIS_ZSET)) return;
 
     if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
         zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,range,&deleted);
-        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
+        if (zzlLength(zobj->ptr) == 0) {
+            dbDelete(c->db,key);
+            keyremoved = 1;
+        }
     } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
         deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
         if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
+        if (dictSize(zs->dict) == 0) {
+            dbDelete(c->db,key);
+            keyremoved = 1;
+        }
     } else {
         redisPanic("Unknown sorted set encoding");
     }
 
-    if (deleted) signalModifiedKey(c->db,key);
+    if (deleted) {
+        signalModifiedKey(c->db,key);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyscore",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+    }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
 
 void zremrangebyrankCommand(redisClient *c) {
     robj *key = c->argv[1];
     robj *zobj;
     long start;
     long end;
     int llen;
     unsigned long deleted;
+    int keyremoved = 0;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
         (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
 
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
         checkType(c,zobj,REDIS_ZSET)) return;
