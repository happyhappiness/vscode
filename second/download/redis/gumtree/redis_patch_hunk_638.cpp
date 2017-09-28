                     dbDelete(c->db,key);
                     keyremoved = 1;
                     break;
                 }
             }
         }
-    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+    } else if (zobj->encoding == OBJ_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
         dictEntry *de;
         double score;
 
         for (j = 2; j < c->argc; j++) {
             de = dictFind(zs->dict,c->argv[j]);
             if (de != NULL) {
                 deleted++;
 
                 /* Delete from the skiplist */
                 score = *(double*)dictGetVal(de);
-                redisAssertWithInfo(c,c->argv[j],zslDelete(zs->zsl,score,c->argv[j]));
+                serverAssertWithInfo(c,c->argv[j],zslDelete(zs->zsl,score,c->argv[j]));
 
                 /* Delete from the hash table */
                 dictDelete(zs->dict,c->argv[j]);
                 if (htNeedsResize(zs->dict)) dictResize(zs->dict);
                 if (dictSize(zs->dict) == 0) {
                     dbDelete(c->db,key);
                     keyremoved = 1;
                     break;
                 }
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     if (deleted) {
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrem",key,c->db->id);
+        notifyKeyspaceEvent(NOTIFY_ZSET,"zrem",key,c->db->id);
         if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
+            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",key,c->db->id);
         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
 }
 
 /* Implements ZREMRANGEBYRANK, ZREMRANGEBYSCORE, ZREMRANGEBYLEX commands. */
 #define ZRANGE_RANK 0
 #define ZRANGE_SCORE 1
 #define ZRANGE_LEX 2
-void zremrangeGenericCommand(redisClient *c, int rangetype) {
+void zremrangeGenericCommand(client *c, int rangetype) {
     robj *key = c->argv[1];
     robj *zobj;
     int keyremoved = 0;
-    unsigned long deleted;
+    unsigned long deleted = 0;
     zrangespec range;
     zlexrangespec lexrange;
     long start, end, llen;
 
     /* Step 1: Parse the range. */
     if (rangetype == ZRANGE_RANK) {
-        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK) ||
-            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK))
+        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK) ||
+            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK))
             return;
     } else if (rangetype == ZRANGE_SCORE) {
-        if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        if (zslParseRange(c->argv[2],c->argv[3],&range) != C_OK) {
             addReplyError(c,"min or max is not a float");
             return;
         }
     } else if (rangetype == ZRANGE_LEX) {
-        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != REDIS_OK) {
+        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != C_OK) {
             addReplyError(c,"min or max not valid string range item");
             return;
         }
     }
 
     /* Step 2: Lookup & range sanity checks if needed. */
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET)) goto cleanup;
+        checkType(c,zobj,OBJ_ZSET)) goto cleanup;
 
     if (rangetype == ZRANGE_RANK) {
         /* Sanitize indexes. */
         llen = zsetLength(zobj);
         if (start < 0) start = llen+start;
         if (end < 0) end = llen+end;
