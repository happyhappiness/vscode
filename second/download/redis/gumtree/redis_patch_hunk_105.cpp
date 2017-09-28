         }
     } else {
         redisPanic("Unknown sorted set encoding");
     }
 
     if (deleted) {
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrem",key,c->db->id);
+        if (keyremoved)
+            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
 }
 
 void zremrangebyscoreCommand(redisClient *c) {
     robj *key = c->argv[1];
     robj *zobj;
     zrangespec range;
+    int keyremoved = 0;
     unsigned long deleted;
 
     /* Parse the range arguments. */
     if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
         addReplyError(c,"min or max is not a float");
         return;
