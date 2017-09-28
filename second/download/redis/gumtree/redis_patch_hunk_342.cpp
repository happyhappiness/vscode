         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
     addReplyLongLong(c,deleted);
 }
 
-void zremrangebyscoreCommand(redisClient *c) {
+/* Implements ZREMRANGEBYRANK, ZREMRANGEBYSCORE, ZREMRANGEBYLEX commands. */
+#define ZRANGE_RANK 0
+#define ZRANGE_SCORE 1
+#define ZRANGE_LEX 2
+void zremrangeGenericCommand(redisClient *c, int rangetype) {
     robj *key = c->argv[1];
     robj *zobj;
-    zrangespec range;
     int keyremoved = 0;
     unsigned long deleted;
+    zrangespec range;
+    zlexrangespec lexrange;
+    long start, end, llen;
 
-    /* Parse the range arguments. */
-    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
-        addReplyError(c,"min or max is not a float");
-        return;
+    /* Step 1: Parse the range. */
+    if (rangetype == ZRANGE_RANK) {
+        if ((getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK) ||
+            (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK))
+            return;
+    } else if (rangetype == ZRANGE_SCORE) {
+        if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+            addReplyError(c,"min or max is not a float");
+            return;
+        }
+    } else if (rangetype == ZRANGE_LEX) {
+        if (zslParseLexRange(c->argv[2],c->argv[3],&lexrange) != REDIS_OK) {
+            addReplyError(c,"min or max not valid string range item");
+            return;
+        }
     }
 
+    /* Step 2: Lookup & range sanity checks if needed. */
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET)) return;
+        checkType(c,zobj,REDIS_ZSET)) goto cleanup;
+
+    if (rangetype == ZRANGE_RANK) {
+        /* Sanitize indexes. */
+        llen = zsetLength(zobj);
+        if (start < 0) start = llen+start;
+        if (end < 0) end = llen+end;
+        if (start < 0) start = 0;
+
+        /* Invariant: start >= 0, so this test will be true when end < 0.
+         * The range is empty when start > end or start >= length. */
+        if (start > end || start >= llen) {
+            addReply(c,shared.czero);
+            goto cleanup;
+        }
+        if (end >= llen) end = llen-1;
+    }
 
+    /* Step 3: Perform the range deletion operation. */
     if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
-        zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,range,&deleted);
+        switch(rangetype) {
+        case ZRANGE_RANK:
+            zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
+            break;
+        case ZRANGE_SCORE:
+            zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,&range,&deleted);
+            break;
+        case ZRANGE_LEX:
+            zobj->ptr = zzlDeleteRangeByLex(zobj->ptr,&lexrange,&deleted);
+            break;
+        }
         if (zzlLength(zobj->ptr) == 0) {
             dbDelete(c->db,key);
             keyremoved = 1;
         }
     } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
-        deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
+        switch(rangetype) {
+        case ZRANGE_RANK:
+            deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
+            break;
+        case ZRANGE_SCORE:
+            deleted = zslDeleteRangeByScore(zs->zsl,&range,zs->dict);
+            break;
+        case ZRANGE_LEX:
+            deleted = zslDeleteRangeByLex(zs->zsl,&lexrange,zs->dict);
+            break;
+        }
         if (htNeedsResize(zs->dict)) dictResize(zs->dict);
         if (dictSize(zs->dict) == 0) {
             dbDelete(c->db,key);
             keyremoved = 1;
         }
     } else {
         redisPanic("Unknown sorted set encoding");
     }
 
+    /* Step 4: Notifications and reply. */
     if (deleted) {
+        char *event[3] = {"zremrangebyrank","zremrangebyscore","zremrangebylex"};
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyscore",key,c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,event[rangetype],key,c->db->id);
         if (keyremoved)
             notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
     }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
+
+cleanup:
+    if (rangetype == ZRANGE_LEX) zslFreeLexRange(&lexrange);
 }
 
 void zremrangebyrankCommand(redisClient *c) {
-    robj *key = c->argv[1];
-    robj *zobj;
-    long start;
-    long end;
-    int llen;
-    unsigned long deleted;
-    int keyremoved = 0;
-
-    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
-        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
-
-    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET)) return;
-
-    /* Sanitize indexes. */
-    llen = zsetLength(zobj);
-    if (start < 0) start = llen+start;
-    if (end < 0) end = llen+end;
-    if (start < 0) start = 0;
-
-    /* Invariant: start >= 0, so this test will be true when end < 0.
-     * The range is empty when start > end or start >= length. */
-    if (start > end || start >= llen) {
-        addReply(c,shared.czero);
-        return;
-    }
-    if (end >= llen) end = llen-1;
-
-    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
-        /* Correct for 1-based rank. */
-        zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
-        if (zzlLength(zobj->ptr) == 0) {
-            dbDelete(c->db,key);
-            keyremoved = 1;
-        }
-    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
-        zset *zs = zobj->ptr;
+    zremrangeGenericCommand(c,ZRANGE_RANK);
+}
 
-        /* Correct for 1-based rank. */
-        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
-        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-        if (dictSize(zs->dict) == 0) {
-            dbDelete(c->db,key);
-            keyremoved = 1;
-        }
-    } else {
-        redisPanic("Unknown sorted set encoding");
-    }
+void zremrangebyscoreCommand(redisClient *c) {
+    zremrangeGenericCommand(c,ZRANGE_SCORE);
+}
 
-    if (deleted) {
-        signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,"zrembyrank",key,c->db->id);
-        if (keyremoved)
-            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",key,c->db->id);
-    }
-    server.dirty += deleted;
-    addReplyLongLong(c,deleted);
+void zremrangebylexCommand(redisClient *c) {
+    zremrangeGenericCommand(c,ZRANGE_LEX);
 }
 
 typedef struct {
     robj *subject;
     int type; /* Set, sorted set */
     int encoding;
