     }
     if (end >= llen) end = llen-1;
 
     if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
         /* Correct for 1-based rank. */
         zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
-        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
+        if (zzlLength(zobj->ptr) == 0) {
+            dbDelete(c->db,key);
+            keyremoved = 1;
+        }
     } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
 
         /* Correct for 1-based rank. */
         deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
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
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyrank",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+    }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
 
 typedef struct {
     robj *subject;
