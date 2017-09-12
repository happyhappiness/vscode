@@ -454,6 +454,87 @@ unsigned int zzlLength(robj *zobj) {
     return ziplistLen(zl)/2;
 }
 
+/* Returns if there is a part of the zset is in range. Should only be used
+ * internally by zzlFirstInRange and zzlLastInRange. */
+int zzlIsInRange(unsigned char *zl, zrangespec *range) {
+    unsigned char *p;
+    double score;
+
+    /* Test for ranges that will always be empty. */
+    if (range->min > range->max ||
+            (range->min == range->max && (range->minex || range->maxex)))
+        return 0;
+
+    p = ziplistIndex(zl,-1); /* Last score. */
+    redisAssert(p != NULL);
+    score = zzlGetScore(p);
+    if (!zslValueGteMin(score,range))
+        return 0;
+
+    p = ziplistIndex(zl,1); /* First score. */
+    redisAssert(p != NULL);
+    score = zzlGetScore(p);
+    if (!zslValueLteMax(score,range))
+        return 0;
+
+    return 1;
+}
+
+/* Find pointer to the first element contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlFirstInRange(robj *zobj, zrangespec range) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *eptr = ziplistIndex(zl,0), *sptr;
+    double score;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        score = zzlGetScore(sptr);
+        if (zslValueGteMin(score,&range))
+            return eptr;
+
+        /* Move to next element. */
+        eptr = ziplistNext(zl,sptr);
+    }
+
+    return NULL;
+}
+
+/* Find pointer to the last element contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+unsigned char *zzlLastInRange(robj *zobj, zrangespec range) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *eptr = ziplistIndex(zl,-2), *sptr;
+    double score;
+
+    /* If everything is out of range, return early. */
+    if (!zzlIsInRange(zl,&range)) return NULL;
+
+    while (eptr != NULL) {
+        sptr = ziplistNext(zl,eptr);
+        redisAssert(sptr != NULL);
+
+        score = zzlGetScore(sptr);
+        if (zslValueLteMax(score,&range))
+            return eptr;
+
+        /* Move to previous element by moving to the score of previous element.
+         * When this returns NULL, we know there also is no element. */
+        sptr = ziplistPrev(zl,eptr);
+        if (sptr != NULL)
+            redisAssert((eptr = ziplistPrev(zl,sptr)) != NULL);
+        else
+            eptr = NULL;
+    }
+
+    return NULL;
+}
+
 unsigned char *zzlFind(robj *zobj, robj *ele, double *score) {
     unsigned char *zl = zobj->ptr;
     unsigned char *eptr = ziplistIndex(zl,0), *sptr;
@@ -557,6 +638,34 @@ int zzlInsert(robj *zobj, robj *ele, double score) {
     return REDIS_OK;
 }
 
+unsigned long zzlDeleteRangeByScore(robj *zobj, zrangespec range) {
+    unsigned char *zl = zobj->ptr;
+    unsigned char *eptr, *sptr;
+    double score;
+    unsigned long deleted = 0;
+
+    eptr = zzlFirstInRange(zobj,range);
+    if (eptr == NULL) return deleted;
+
+
+    /* When the tail of the ziplist is deleted, eptr will point to the sentinel
+     * byte and ziplistNext will return NULL. */
+    while ((sptr = ziplistNext(zl,eptr)) != NULL) {
+        score = zzlGetScore(sptr);
+        if (zslValueLteMax(score,&range)) {
+            /* Delete both the element and the score. */
+            zl = ziplistDelete(zl,&eptr);
+            zl = ziplistDelete(zl,&eptr);
+            deleted++;
+        } else {
+            /* No longer in range. */
+            break;
+        }
+    }
+
+    return deleted;
+}
+
 /*-----------------------------------------------------------------------------
  * Sorted set commands 
  *----------------------------------------------------------------------------*/
@@ -736,25 +845,32 @@ void zremCommand(redisClient *c) {
 }
 
 void zremrangebyscoreCommand(redisClient *c) {
+    robj *key = c->argv[1];
+    robj *zobj;
     zrangespec range;
-    long deleted;
-    robj *o;
-    zset *zs;
+    unsigned long deleted;
 
     /* Parse the range arguments. */
     if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
         addReplyError(c,"min or max is not a double");
         return;
     }
 
-    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,o,REDIS_ZSET)) return;
+    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
+        checkType(c,zobj,REDIS_ZSET)) return;
 
-    zs = o->ptr;
-    deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
-    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
-    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
-    if (deleted) signalModifiedKey(c->db,c->argv[1]);
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        deleted = zzlDeleteRangeByScore(zobj,range);
+    } else if (zobj->encoding == REDIS_ENCODING_RAW) {
+        zset *zs = zobj->ptr;
+        deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
+        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
+    } else {
+        redisPanic("Unknown sorted set encoding");
+    }
+
+    if (deleted) signalModifiedKey(c->db,key);
     server.dirty += deleted;
     addReplyLongLong(c,deleted);
 }