@@ -2359,6 +2359,79 @@ void zcountCommand(redisClient *c) {
     addReplyLongLong(c, count);
 }
 
+void zlexcountCommand(redisClient *c) {
+    robj *key = c->argv[1];
+    robj *zobj;
+    zlexrangespec range;
+    int count = 0;
+
+    /* Parse the range arguments */
+    if (zslParseLexRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max not valid string range item");
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
+
+        /* Use the first element in range as the starting point */
+        eptr = zzlFirstInLexRange(zl,range);
+
+        /* No "first" element */
+        if (eptr == NULL) {
+            addReply(c, shared.czero);
+            return;
+        }
+
+        /* First element is in range */
+        sptr = ziplistNext(zl,eptr);
+        redisAssertWithInfo(c,zobj,zzlLexValueLteMax(eptr,&range));
+
+        /* Iterate over elements in range */
+        while (eptr) {
+            /* Abort when the node is no longer in range. */
+            if (!zzlLexValueLteMax(eptr,&range)) {
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
+        zn = zslFirstInLexRange(zsl, range);
+
+        /* Use rank of first element, if any, to determine preliminary count */
+        if (zn != NULL) {
+            rank = zslGetRank(zsl, zn->score, zn->obj);
+            count = (zsl->length - (rank - 1));
+
+            /* Find last element in range */
+            zn = zslLastInLexRange(zsl, range);
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
+}
+
 /* This command implements ZRANGEBYLEX, ZREVRANGEBYLEX. */
 void genericZrangebylexCommand(redisClient *c, int reverse) {
     zlexrangespec range;