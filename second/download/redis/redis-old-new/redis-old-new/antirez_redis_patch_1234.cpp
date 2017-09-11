@@ -844,9 +844,9 @@ void zaddGenericCommand(redisClient *c, int incr) {
     robj *ele;
     robj *zobj;
     robj *curobj;
-    double score = 0, *scores, curscore = 0.0;
+    double score = 0, *scores = NULL, curscore = 0.0;
     int j, elements = (c->argc-2)/2;
-    int added = 0;
+    int added = 0, updated = 0;
 
     if (c->argc % 2) {
         addReply(c,shared.syntaxerr);
@@ -859,11 +859,7 @@ void zaddGenericCommand(redisClient *c, int incr) {
     scores = zmalloc(sizeof(double)*elements);
     for (j = 0; j < elements; j++) {
         if (getDoubleFromObjectOrReply(c,c->argv[2+j*2],&scores[j],NULL)
-            != REDIS_OK)
-        {
-            zfree(scores);
-            return;
-        }
+            != REDIS_OK) goto cleanup;
     }
 
     /* Lookup the key and create the sorted set if does not exist. */
@@ -880,8 +876,7 @@ void zaddGenericCommand(redisClient *c, int incr) {
     } else {
         if (zobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
-            zfree(scores);
-            return;
+            goto cleanup;
         }
     }
 
@@ -898,20 +893,16 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     score += curscore;
                     if (isnan(score)) {
                         addReplyError(c,nanerr);
-                        /* Don't need to check if the sorted set is empty
-                         * because we know it has at least one element. */
-                        zfree(scores);
-                        return;
+                        goto cleanup;
                     }
                 }
 
                 /* Remove and re-insert when score changed. */
                 if (score != curscore) {
                     zobj->ptr = zzlDelete(zobj->ptr,eptr);
                     zobj->ptr = zzlInsert(zobj->ptr,ele,score);
-
-                    signalModifiedKey(c->db,key);
                     server.dirty++;
+                    updated++;
                 }
             } else {
                 /* Optimize: check if the element is too large or the list
@@ -921,10 +912,8 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
                 if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
                     zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
-
-                signalModifiedKey(c->db,key);
                 server.dirty++;
-                if (!incr) added++;
+                added++;
             }
         } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
             zset *zs = zobj->ptr;
@@ -943,8 +932,7 @@ void zaddGenericCommand(redisClient *c, int incr) {
                         addReplyError(c,nanerr);
                         /* Don't need to check if the sorted set is empty
                          * because we know it has at least one element. */
-                        zfree(scores);
-                        return;
+                        goto cleanup;
                     }
                 }
 
@@ -956,29 +944,32 @@ void zaddGenericCommand(redisClient *c, int incr) {
                     znode = zslInsert(zs->zsl,score,curobj);
                     incrRefCount(curobj); /* Re-inserted in skiplist. */
                     dictGetVal(de) = &znode->score; /* Update score ptr. */
-
-                    signalModifiedKey(c->db,key);
                     server.dirty++;
+                    updated++;
                 }
             } else {
                 znode = zslInsert(zs->zsl,score,ele);
                 incrRefCount(ele); /* Inserted in skiplist. */
                 redisAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                 incrRefCount(ele); /* Added to dictionary. */
-
-                signalModifiedKey(c->db,key);
                 server.dirty++;
-                if (!incr) added++;
+                added++;
             }
         } else {
             redisPanic("Unknown sorted set encoding");
         }
     }
-    zfree(scores);
     if (incr) /* ZINCRBY */
         addReplyDouble(c,score);
     else /* ZADD */
         addReplyLongLong(c,added);
+
+cleanup:
+    zfree(scores);
+    if (added || updated) {
+        signalModifiedKey(c->db,key);
+        notifyKeyspaceEvent(incr ? "zincr" : "zadd", key, c->db->id);
+    }
 }
 
 void zaddCommand(redisClient *c) {
@@ -992,7 +983,7 @@ void zincrbyCommand(redisClient *c) {
 void zremCommand(redisClient *c) {
     robj *key = c->argv[1];
     robj *zobj;
-    int deleted = 0, j;
+    int deleted = 0, keyremoved = 0, j;
 
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
         checkType(c,zobj,REDIS_ZSET)) return;
@@ -1038,6 +1029,8 @@ void zremCommand(redisClient *c) {
     }
 
     if (deleted) {
+        notifyKeyspaceEvent("zrem",key,c->db->id);
+        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
         signalModifiedKey(c->db,key);
         server.dirty += deleted;
     }
@@ -1048,6 +1041,7 @@ void zremrangebyscoreCommand(redisClient *c) {
     robj *key = c->argv[1];
     robj *zobj;
     zrangespec range;
+    int keyremoved = 0;
     unsigned long deleted;
 
     /* Parse the range arguments. */
@@ -1061,17 +1055,27 @@ void zremrangebyscoreCommand(redisClient *c) {
 
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
+        notifyKeyspaceEvent("zrembyscore",key,c->db->id);
+        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
+    }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
@@ -1083,6 +1087,7 @@ void zremrangebyrankCommand(redisClient *c) {
     long end;
     int llen;
     unsigned long deleted;
+    int keyremoved = 0;
 
     if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
         (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;
@@ -1107,19 +1112,29 @@ void zremrangebyrankCommand(redisClient *c) {
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
+        notifyKeyspaceEvent("zrembyrank",key,c->db->id);
+        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
+    }
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }
@@ -1661,6 +1676,7 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
 
     if (dbDelete(c->db,dstkey)) {
         signalModifiedKey(c->db,dstkey);
+        notifyKeyspaceEvent("del",dstkey,c->db->id);
         touched = 1;
         server.dirty++;
     }
@@ -1673,6 +1689,9 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
         dbAdd(c->db,dstkey,dstobj);
         addReplyLongLong(c,zsetLength(dstobj));
         if (!touched) signalModifiedKey(c->db,dstkey);
+        notifyKeyspaceEvent(
+            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
+            dstkey,c->db->id);
         server.dirty++;
     } else {
         decrRefCount(dstobj);