@@ -52,6 +52,9 @@
 #include "redis.h"
 #include <math.h>
 
+static int zslLexValueGteMin(robj *value, zlexrangespec *spec);
+static int zslLexValueLteMax(robj *value, zlexrangespec *spec);
+
 zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
     zskiplistNode *zn = zmalloc(sizeof(*zn)+level*sizeof(struct zskiplistLevel));
     zn->score = score;
@@ -235,18 +238,18 @@ int zslIsInRange(zskiplist *zsl, zrangespec *range) {
 
 /* Find the first node that is contained in the specified range.
  * Returns NULL when no element is contained in the range. */
-zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec range) {
+zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec *range) {
     zskiplistNode *x;
     int i;
 
     /* If everything is out of range, return early. */
-    if (!zslIsInRange(zsl,&range)) return NULL;
+    if (!zslIsInRange(zsl,range)) return NULL;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
         /* Go forward while *OUT* of range. */
         while (x->level[i].forward &&
-            !zslValueGteMin(x->level[i].forward->score,&range))
+            !zslValueGteMin(x->level[i].forward->score,range))
                 x = x->level[i].forward;
     }
 
@@ -255,49 +258,49 @@ zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec range) {
     redisAssert(x != NULL);
 
     /* Check if score <= max. */
-    if (!zslValueLteMax(x->score,&range)) return NULL;
+    if (!zslValueLteMax(x->score,range)) return NULL;
     return x;
 }
 
 /* Find the last node that is contained in the specified range.
  * Returns NULL when no element is contained in the range. */
-zskiplistNode *zslLastInRange(zskiplist *zsl, zrangespec range) {
+zskiplistNode *zslLastInRange(zskiplist *zsl, zrangespec *range) {
     zskiplistNode *x;
     int i;
 
     /* If everything is out of range, return early. */
-    if (!zslIsInRange(zsl,&range)) return NULL;
+    if (!zslIsInRange(zsl,range)) return NULL;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
         /* Go forward while *IN* range. */
         while (x->level[i].forward &&
-            zslValueLteMax(x->level[i].forward->score,&range))
+            zslValueLteMax(x->level[i].forward->score,range))
                 x = x->level[i].forward;
     }
 
     /* This is an inner range, so this node cannot be NULL. */
     redisAssert(x != NULL);
 
     /* Check if score >= min. */
-    if (!zslValueGteMin(x->score,&range)) return NULL;
+    if (!zslValueGteMin(x->score,range)) return NULL;
     return x;
 }
 
 /* Delete all the elements with score between min and max from the skiplist.
  * Min and max are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
  * sorted set, in order to remove the elements from the hash table too. */
-unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec range, dict *dict) {
+unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec *range, dict *dict) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     unsigned long removed = 0;
     int i;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->level[i].forward && (range.minex ?
-            x->level[i].forward->score <= range.min :
-            x->level[i].forward->score < range.min))
+        while (x->level[i].forward && (range->minex ?
+            x->level[i].forward->score <= range->min :
+            x->level[i].forward->score < range->min))
                 x = x->level[i].forward;
         update[i] = x;
     }
@@ -306,7 +309,38 @@ unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec range, dict *dict
     x = x->level[0].forward;
 
     /* Delete nodes while in range. */
-    while (x && (range.maxex ? x->score < range.max : x->score <= range.max)) {
+    while (x &&
+           (range->maxex ? x->score < range->max : x->score <= range->max))
+    {
+        zskiplistNode *next = x->level[0].forward;
+        zslDeleteNode(zsl,x,update);
+        dictDelete(dict,x->obj);
+        zslFreeNode(x);
+        removed++;
+        x = next;
+    }
+    return removed;
+}
+
+unsigned long zslDeleteRangeByLex(zskiplist *zsl, zlexrangespec *range, dict *dict) {
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    unsigned long removed = 0;
+    int i;
+
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->level[i].forward &&
+            !zslLexValueGteMin(x->level[i].forward->obj,range))
+                x = x->level[i].forward;
+        update[i] = x;
+    }
+
+    /* Current node is the last with score < or <= min. */
+    x = x->level[0].forward;
+
+    /* Delete nodes while in range. */
+    while (x && zslLexValueLteMax(x->obj,range)) {
         zskiplistNode *next = x->level[0].forward;
         zslDeleteNode(zsl,x,update);
         dictDelete(dict,x->obj);
@@ -444,7 +478,7 @@ static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
   * respectively if the item is exclusive or inclusive. REDIS_OK will be
   * returned.
   *
-  * If the stirng is not a valid range REDIS_ERR is returned, and the value
+  * If the string is not a valid range REDIS_ERR is returned, and the value
   * of *dest and *ex is undefined. */
 int zslParseLexRangeItem(robj *item, robj **dest, int *ex) {
     char *c = item->ptr;
@@ -475,8 +509,14 @@ int zslParseLexRangeItem(robj *item, robj **dest, int *ex) {
     }
 }
 
-/* Populate the rangespec according to the objects min and max. */
+/* Populate the rangespec according to the objects min and max.
+ *
+ * Return REDIS_OK on success. On error REDIS_ERR is returned.
+ * When OK is returned the structure must be freed with zslFreeLexRange(),
+ * otherwise no release is needed. */
 static int zslParseLexRange(robj *min, robj *max, zlexrangespec *spec) {
+    /* The range can't be valid if objects are integer encoded.
+     * Every item must start with ( or [. */
     if (min->encoding == REDIS_ENCODING_INT ||
         max->encoding == REDIS_ENCODING_INT) return REDIS_ERR;
 
@@ -491,6 +531,13 @@ static int zslParseLexRange(robj *min, robj *max, zlexrangespec *spec) {
     }
 }
 
+/* Free a lex range structure, must be called only after zelParseLexRange()
+ * populated the structure with success (REDIS_OK returned). */
+void zslFreeLexRange(zlexrangespec *spec) {
+    decrRefCount(spec->min);
+    decrRefCount(spec->max);
+}
+
 /* This is just a wrapper to compareStringObjects() that is able to
  * handle shared.minstring and shared.maxstring as the equivalent of
  * -inf and +inf for strings */
@@ -534,18 +581,18 @@ int zslIsInLexRange(zskiplist *zsl, zlexrangespec *range) {
 
 /* Find the first node that is contained in the specified lex range.
  * Returns NULL when no element is contained in the range. */
-zskiplistNode *zslFirstInLexRange(zskiplist *zsl, zlexrangespec range) {
+zskiplistNode *zslFirstInLexRange(zskiplist *zsl, zlexrangespec *range) {
     zskiplistNode *x;
     int i;
 
     /* If everything is out of range, return early. */
-    if (!zslIsInLexRange(zsl,&range)) return NULL;
+    if (!zslIsInLexRange(zsl,range)) return NULL;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
         /* Go forward while *OUT* of range. */
         while (x->level[i].forward &&
-            !zslLexValueGteMin(x->level[i].forward->obj,&range))
+            !zslLexValueGteMin(x->level[i].forward->obj,range))
                 x = x->level[i].forward;
     }
 
@@ -554,32 +601,32 @@ zskiplistNode *zslFirstInLexRange(zskiplist *zsl, zlexrangespec range) {
     redisAssert(x != NULL);
 
     /* Check if score <= max. */
-    if (!zslLexValueLteMax(x->obj,&range)) return NULL;
+    if (!zslLexValueLteMax(x->obj,range)) return NULL;
     return x;
 }
 
 /* Find the last node that is contained in the specified range.
  * Returns NULL when no element is contained in the range. */
-zskiplistNode *zslLastInLexRange(zskiplist *zsl, zlexrangespec range) {
+zskiplistNode *zslLastInLexRange(zskiplist *zsl, zlexrangespec *range) {
     zskiplistNode *x;
     int i;
 
     /* If everything is out of range, return early. */
-    if (!zslIsInLexRange(zsl,&range)) return NULL;
+    if (!zslIsInLexRange(zsl,range)) return NULL;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
         /* Go forward while *IN* range. */
         while (x->level[i].forward &&
-            zslLexValueLteMax(x->level[i].forward->obj,&range))
+            zslLexValueLteMax(x->level[i].forward->obj,range))
                 x = x->level[i].forward;
     }
 
     /* This is an inner range, so this node cannot be NULL. */
     redisAssert(x != NULL);
 
     /* Check if score >= min. */
-    if (!zslLexValueGteMin(x->obj,&range)) return NULL;
+    if (!zslLexValueGteMin(x->obj,range)) return NULL;
     return x;
 }
 
@@ -717,21 +764,21 @@ int zzlIsInRange(unsigned char *zl, zrangespec *range) {
 
 /* Find pointer to the first element contained in the specified range.
  * Returns NULL when no element is contained in the range. */
-unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec range) {
+unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec *range) {
     unsigned char *eptr = ziplistIndex(zl,0), *sptr;
     double score;
 
     /* If everything is out of range, return early. */
-    if (!zzlIsInRange(zl,&range)) return NULL;
+    if (!zzlIsInRange(zl,range)) return NULL;
 
     while (eptr != NULL) {
         sptr = ziplistNext(zl,eptr);
         redisAssert(sptr != NULL);
 
         score = zzlGetScore(sptr);
-        if (zslValueGteMin(score,&range)) {
+        if (zslValueGteMin(score,range)) {
             /* Check if score <= max. */
-            if (zslValueLteMax(score,&range))
+            if (zslValueLteMax(score,range))
                 return eptr;
             return NULL;
         }
@@ -745,21 +792,21 @@ unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec range) {
 
 /* Find pointer to the last element contained in the specified range.
  * Returns NULL when no element is contained in the range. */
-unsigned char *zzlLastInRange(unsigned char *zl, zrangespec range) {
+unsigned char *zzlLastInRange(unsigned char *zl, zrangespec *range) {
     unsigned char *eptr = ziplistIndex(zl,-2), *sptr;
     double score;
 
     /* If everything is out of range, return early. */
-    if (!zzlIsInRange(zl,&range)) return NULL;
+    if (!zzlIsInRange(zl,range)) return NULL;
 
     while (eptr != NULL) {
         sptr = ziplistNext(zl,eptr);
         redisAssert(sptr != NULL);
 
         score = zzlGetScore(sptr);
-        if (zslValueLteMax(score,&range)) {
+        if (zslValueLteMax(score,range)) {
             /* Check if score >= min. */
-            if (zslValueGteMin(score,&range))
+            if (zslValueGteMin(score,range))
                 return eptr;
             return NULL;
         }
@@ -816,16 +863,16 @@ int zzlIsInLexRange(unsigned char *zl, zlexrangespec *range) {
 
 /* Find pointer to the first element contained in the specified lex range.
  * Returns NULL when no element is contained in the range. */
-unsigned char *zzlFirstInLexRange(unsigned char *zl, zlexrangespec range) {
+unsigned char *zzlFirstInLexRange(unsigned char *zl, zlexrangespec *range) {
     unsigned char *eptr = ziplistIndex(zl,0), *sptr;
 
     /* If everything is out of range, return early. */
-    if (!zzlIsInLexRange(zl,&range)) return NULL;
+    if (!zzlIsInLexRange(zl,range)) return NULL;
 
     while (eptr != NULL) {
-        if (zzlLexValueGteMin(eptr,&range)) {
+        if (zzlLexValueGteMin(eptr,range)) {
             /* Check if score <= max. */
-            if (zzlLexValueLteMax(eptr,&range))
+            if (zzlLexValueLteMax(eptr,range))
                 return eptr;
             return NULL;
         }
@@ -841,16 +888,16 @@ unsigned char *zzlFirstInLexRange(unsigned char *zl, zlexrangespec range) {
 
 /* Find pointer to the last element contained in the specified lex range.
  * Returns NULL when no element is contained in the range. */
-unsigned char *zzlLastInLexRange(unsigned char *zl, zlexrangespec range) {
+unsigned char *zzlLastInLexRange(unsigned char *zl, zlexrangespec *range) {
     unsigned char *eptr = ziplistIndex(zl,-2), *sptr;
 
     /* If everything is out of range, return early. */
-    if (!zzlIsInLexRange(zl,&range)) return NULL;
+    if (!zzlIsInLexRange(zl,range)) return NULL;
 
     while (eptr != NULL) {
-        if (zzlLexValueLteMax(eptr,&range)) {
+        if (zzlLexValueLteMax(eptr,range)) {
             /* Check if score >= min. */
-            if (zzlLexValueGteMin(eptr,&range))
+            if (zzlLexValueGteMin(eptr,range))
                 return eptr;
             return NULL;
         }
@@ -964,7 +1011,7 @@ unsigned char *zzlInsert(unsigned char *zl, robj *ele, double score) {
     return zl;
 }
 
-unsigned char *zzlDeleteRangeByScore(unsigned char *zl, zrangespec range, unsigned long *deleted) {
+unsigned char *zzlDeleteRangeByScore(unsigned char *zl, zrangespec *range, unsigned long *deleted) {
     unsigned char *eptr, *sptr;
     double score;
     unsigned long num = 0;
@@ -978,7 +1025,34 @@ unsigned char *zzlDeleteRangeByScore(unsigned char *zl, zrangespec range, unsign
      * byte and ziplistNext will return NULL. */
     while ((sptr = ziplistNext(zl,eptr)) != NULL) {
         score = zzlGetScore(sptr);
-        if (zslValueLteMax(score,&range)) {
+        if (zslValueLteMax(score,range)) {
+            /* Delete both the element and the score. */
+            zl = ziplistDelete(zl,&eptr);
+            zl = ziplistDelete(zl,&eptr);
+            num++;
+        } else {
+            /* No longer in range. */
+            break;
+        }
+    }
+
+    if (deleted != NULL) *deleted = num;
+    return zl;
+}
+
+unsigned char *zzlDeleteRangeByLex(unsigned char *zl, zlexrangespec *range, unsigned long *deleted) {
+    unsigned char *eptr, *sptr;
+    unsigned long num = 0;
+
+    if (deleted != NULL) *deleted = 0;
+
+    eptr = zzlFirstInLexRange(zl,range);
+    if (eptr == NULL) return zl;
+
+    /* When the tail of the ziplist is deleted, eptr will point to the sentinel
+     * byte and ziplistNext will return NULL. */
+    while ((sptr = ziplistNext(zl,eptr)) != NULL) {
+        if (zzlLexValueLteMax(eptr,range)) {
             /* Delete both the element and the score. */
             zl = ziplistDelete(zl,&eptr);
             zl = ziplistDelete(zl,&eptr);
@@ -1300,31 +1374,86 @@ void zremCommand(redisClient *c) {
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
@@ -1334,74 +1463,31 @@ void zremrangebyscoreCommand(redisClient *c) {
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
@@ -2147,9 +2233,9 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse) {
 
         /* If reversed, get the last node in range as starting point. */
         if (reverse) {
-            eptr = zzlLastInRange(zl,range);
+            eptr = zzlLastInRange(zl,&range);
         } else {
-            eptr = zzlFirstInRange(zl,range);
+            eptr = zzlFirstInRange(zl,&range);
         }
 
         /* No "first" element in the specified interval. */
@@ -2215,9 +2301,9 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse) {
 
         /* If reversed, get the last node in range as starting point. */
         if (reverse) {
-            ln = zslLastInRange(zsl,range);
+            ln = zslLastInRange(zsl,&range);
         } else {
-            ln = zslFirstInRange(zsl,range);
+            ln = zslFirstInRange(zsl,&range);
         }
 
         /* No "first" element in the specified interval. */
@@ -2304,7 +2390,7 @@ void zcountCommand(redisClient *c) {
         double score;
 
         /* Use the first element in range as the starting point */
-        eptr = zzlFirstInRange(zl,range);
+        eptr = zzlFirstInRange(zl,&range);
 
         /* No "first" element */
         if (eptr == NULL) {
@@ -2336,15 +2422,93 @@ void zcountCommand(redisClient *c) {
         unsigned long rank;
 
         /* Find first element in range */
-        zn = zslFirstInRange(zsl, range);
+        zn = zslFirstInRange(zsl, &range);
+
+        /* Use rank of first element, if any, to determine preliminary count */
+        if (zn != NULL) {
+            rank = zslGetRank(zsl, zn->score, zn->obj);
+            count = (zsl->length - (rank - 1));
+
+            /* Find last element in range */
+            zn = zslLastInRange(zsl, &range);
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
+        checkType(c, zobj, REDIS_ZSET))
+    {
+        zslFreeLexRange(&range);
+        return;
+    }
+
+    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+        unsigned char *zl = zobj->ptr;
+        unsigned char *eptr, *sptr;
+
+        /* Use the first element in range as the starting point */
+        eptr = zzlFirstInLexRange(zl,&range);
+
+        /* No "first" element */
+        if (eptr == NULL) {
+            zslFreeLexRange(&range);
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
+        zn = zslFirstInLexRange(zsl, &range);
 
         /* Use rank of first element, if any, to determine preliminary count */
         if (zn != NULL) {
             rank = zslGetRank(zsl, zn->score, zn->obj);
             count = (zsl->length - (rank - 1));
 
             /* Find last element in range */
-            zn = zslLastInRange(zsl, range);
+            zn = zslLastInLexRange(zsl, &range);
 
             /* Use rank of last element, if any, to determine the actual count */
             if (zn != NULL) {
@@ -2356,6 +2520,7 @@ void zcountCommand(redisClient *c) {
         redisPanic("Unknown sorted set encoding");
     }
 
+    zslFreeLexRange(&range);
     addReplyLongLong(c, count);
 }
 
@@ -2395,6 +2560,7 @@ void genericZrangebylexCommand(redisClient *c, int reverse) {
                     (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
                 pos += 3; remaining -= 3;
             } else {
+                zslFreeLexRange(&range);
                 addReply(c,shared.syntaxerr);
                 return;
             }
@@ -2403,7 +2569,11 @@ void genericZrangebylexCommand(redisClient *c, int reverse) {
 
     /* Ok, lookup the key and get the range */
     if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET)) return;
+        checkType(c,zobj,REDIS_ZSET))
+    {
+        zslFreeLexRange(&range);
+        return;
+    }
 
     if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
         unsigned char *zl = zobj->ptr;
@@ -2414,14 +2584,15 @@ void genericZrangebylexCommand(redisClient *c, int reverse) {
 
         /* If reversed, get the last node in range as starting point. */
         if (reverse) {
-            eptr = zzlLastInLexRange(zl,range);
+            eptr = zzlLastInLexRange(zl,&range);
         } else {
-            eptr = zzlFirstInLexRange(zl,range);
+            eptr = zzlFirstInLexRange(zl,&range);
         }
 
         /* No "first" element in the specified interval. */
         if (eptr == NULL) {
             addReply(c, shared.emptymultibulk);
+            zslFreeLexRange(&range);
             return;
         }
 
@@ -2477,14 +2648,15 @@ void genericZrangebylexCommand(redisClient *c, int reverse) {
 
         /* If reversed, get the last node in range as starting point. */
         if (reverse) {
-            ln = zslLastInLexRange(zsl,range);
+            ln = zslLastInLexRange(zsl,&range);
         } else {
-            ln = zslFirstInLexRange(zsl,range);
+            ln = zslFirstInLexRange(zsl,&range);
         }
 
         /* No "first" element in the specified interval. */
         if (ln == NULL) {
             addReply(c, shared.emptymultibulk);
+            zslFreeLexRange(&range);
             return;
         }
 
@@ -2525,6 +2697,7 @@ void genericZrangebylexCommand(redisClient *c, int reverse) {
         redisPanic("Unknown sorted set encoding");
     }
 
+    zslFreeLexRange(&range);
     setDeferredMultiBulkLength(c, replylen, rangelen);
 }
 