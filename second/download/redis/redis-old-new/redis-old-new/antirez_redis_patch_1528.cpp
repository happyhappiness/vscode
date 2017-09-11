@@ -1756,12 +1756,11 @@ void zrevrangeCommand(redisClient *c) {
     zrangeGenericCommand(c,1);
 }
 
-/* This command implements ZRANGEBYSCORE, ZREVRANGEBYSCORE and ZCOUNT.
- * If "justcount", only the number of elements in the range is returned. */
-void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
+/* This command implements ZRANGEBYSCORE, ZREVRANGEBYSCORE. */
+void genericZrangebyscoreCommand(redisClient *c, int reverse) {
     zrangespec range;
     robj *key = c->argv[1];
-    robj *emptyreply, *zobj;
+    robj *zobj;
     int offset = 0, limit = -1;
     int withscores = 0;
     unsigned long rangelen = 0;
@@ -1804,8 +1803,7 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
     }
 
     /* Ok, lookup the key and get the range */
-    emptyreply = justcount ? shared.czero : shared.emptymultibulk;
-    if ((zobj = lookupKeyReadOrReply(c,key,emptyreply)) == NULL ||
+    if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL ||
         checkType(c,zobj,REDIS_ZSET)) return;
 
     if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
@@ -1817,14 +1815,15 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
         double score;
 
         /* If reversed, get the last node in range as starting point. */
-        if (reverse)
+        if (reverse) {
             eptr = zzlLastInRange(zl,range);
-        else
+        } else {
             eptr = zzlFirstInRange(zl,range);
+        }
 
         /* No "first" element in the specified interval. */
         if (eptr == NULL) {
-            addReply(c,emptyreply);
+            addReply(c, shared.emptymultibulk);
             return;
         }
 
@@ -1835,16 +1834,17 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
         /* We don't know in advance how many matching elements there are in the
          * list, so we push this object that will represent the multi-bulk
          * length in the output buffer, and will "fix" it later */
-        if (!justcount)
-            replylen = addDeferredMultiBulkLength(c);
+        replylen = addDeferredMultiBulkLength(c);
 
         /* If there is an offset, just traverse the number of elements without
          * checking the score because that is done in the next loop. */
-        while (eptr && offset--)
-            if (reverse)
+        while (eptr && offset--) {
+            if (reverse) {
                 zzlPrev(zl,&eptr,&sptr);
-            else
+            } else {
                 zzlNext(zl,&eptr,&sptr);
+            }
+        }
 
         while (eptr && limit--) {
             score = zzlGetScore(sptr);
@@ -1856,52 +1856,59 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
                 if (!zslValueLteMax(score,&range)) break;
             }
 
-            /* Do our magic */
+            /* We know the element exists, so ziplistGet should always succeed */
+            redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
+
             rangelen++;
-            if (!justcount) {
-                redisAssert(ziplistGet(eptr,&vstr,&vlen,&vlong));
-                if (vstr == NULL)
-                    addReplyBulkLongLong(c,vlong);
-                else
-                    addReplyBulkCBuffer(c,vstr,vlen);
-
-                if (withscores)
-                    addReplyDouble(c,score);
+            if (vstr == NULL) {
+                addReplyBulkLongLong(c,vlong);
+            } else {
+                addReplyBulkCBuffer(c,vstr,vlen);
+            }
+
+            if (withscores) {
+                addReplyDouble(c,score);
             }
 
             /* Move to next node */
-            if (reverse)
+            if (reverse) {
                 zzlPrev(zl,&eptr,&sptr);
-            else
+            } else {
                 zzlNext(zl,&eptr,&sptr);
+            }
         }
     } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
         zset *zs = zobj->ptr;
         zskiplist *zsl = zs->zsl;
         zskiplistNode *ln;
 
         /* If reversed, get the last node in range as starting point. */
-        if (reverse)
+        if (reverse) {
             ln = zslLastInRange(zsl,range);
-        else
+        } else {
             ln = zslFirstInRange(zsl,range);
+        }
 
         /* No "first" element in the specified interval. */
         if (ln == NULL) {
-            addReply(c,emptyreply);
+            addReply(c, shared.emptymultibulk);
             return;
         }
 
         /* We don't know in advance how many matching elements there are in the
          * list, so we push this object that will represent the multi-bulk
          * length in the output buffer, and will "fix" it later */
-        if (!justcount)
-            replylen = addDeferredMultiBulkLength(c);
+        replylen = addDeferredMultiBulkLength(c);
 
         /* If there is an offset, just traverse the number of elements without
          * checking the score because that is done in the next loop. */
-        while (ln && offset--)
-            ln = reverse ? ln->backward : ln->level[0].forward;
+        while (ln && offset--) {
+            if (reverse) {
+                ln = ln->backward;
+            } else {
+                ln = ln->level[0].forward;
+            }
+        }
 
         while (ln && limit--) {
             /* Abort when the node is no longer in range. */
@@ -1911,39 +1918,114 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
                 if (!zslValueLteMax(ln->score,&range)) break;
             }
 
-            /* Do our magic */
             rangelen++;
-            if (!justcount) {
-                addReplyBulk(c,ln->obj);
-                if (withscores)
-                    addReplyDouble(c,ln->score);
+            addReplyBulk(c,ln->obj);
+
+            if (withscores) {
+                addReplyDouble(c,ln->score);
             }
 
             /* Move to next node */
-            ln = reverse ? ln->backward : ln->level[0].forward;
+            if (reverse) {
+                ln = ln->backward;
+            } else {
+                ln = ln->level[0].forward;
+            }
         }
     } else {
         redisPanic("Unknown sorted set encoding");
     }
 
-    if (justcount) {
-        addReplyLongLong(c,(long)rangelen);
-    } else {
-        if (withscores) rangelen *= 2;
-        setDeferredMultiBulkLength(c,replylen,rangelen);
+    if (withscores) {
+        rangelen *= 2;
     }
+
+    setDeferredMultiBulkLength(c, replylen, rangelen);
 }
 
 void zrangebyscoreCommand(redisClient *c) {
-    genericZrangebyscoreCommand(c,0,0);
+    genericZrangebyscoreCommand(c,0);
 }
 
 void zrevrangebyscoreCommand(redisClient *c) {
-    genericZrangebyscoreCommand(c,1,0);
+    genericZrangebyscoreCommand(c,1);
 }
 
 void zcountCommand(redisClient *c) {
-    genericZrangebyscoreCommand(c,0,1);
+    robj *key = c->argv[1];
+    robj *zobj;
+    zrangespec range;
+    int count = 0;
+
+    /* Parse the range arguments */
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max is not a double");
+        return;
+    }
+
+    /* Lookup the sorted set */
+    if ((zobj = lookupKeyReadOrReply(c, key, shared.czero)) == NULL ||
+        checkType(c, zobj, REDIS_ZSET)) return;
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+        double score;
+
+        /* Use the first element in range as the starting point */
+        eptr = zzlFirstInRange(zl,range);
+
+        /* No "first" element */
+        if (eptr == NULL) {
+            addReply(c, shared.czero);
+            return;
+        }
+
+        /* First element is in range */
+        sptr = ziplistNext(zl,eptr);
+        score = zzlGetScore(sptr);
+        redisAssert(zslValueLteMax(score,&range));
+
+        /* Iterate over elements in range */
+        while (eptr) {
+            score = zzlGetScore(sptr);
+
+            /* Abort when the node is no longer in range. */
+            if (!zslValueLteMax(score,&range)) {
+                break;
+            } else {
+                count++;
+                zzlNext(zl,&eptr,&sptr);
+            }
+        }
+    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
+        zset *zs = zobj->ptr;
+        zskiplist *zsl = zs->zsl;
+        zskiplistNode *zn;
+        unsigned long rank;
+
+        /* Find first element in range */
+        zn = zslFirstInRange(zsl, range);
+
+        /* Use rank of first element, if any, to determine preliminary count */
+        if (zn != NULL) {
+            rank = zslGetRank(zsl, zn->score, zn->obj);
+            count = (zsl->length - (rank - 1));
+
+            /* Find last element in range */
+            zn = zslLastInRange(zsl, range);
+
+            /* Use rank of last element, if any, to determine the actual count */
+            if (zn != NULL) {
+                rank = zslGetRank(zsl, zn->score, zn->obj);
+                count -= (zsl->length - rank);
+            }
+        }
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+
+    addReplyLongLong(c, count);
 }
 
 void zcardCommand(redisClient *c) {