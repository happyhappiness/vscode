@@ -180,6 +180,78 @@ typedef struct {
     int minex, maxex; /* are min or max exclusive? */
 } zrangespec;
 
+static inline int zslValueInMinRange(double value, zrangespec *spec) {
+    return spec->minex ? (value > spec->min) : (value >= spec->min);
+}
+
+static inline int zslValueInMaxRange(double value, zrangespec *spec) {
+    return spec->maxex ? (value < spec->max) : (value <= spec->max);
+}
+
+static inline int zslValueInRange(double value, zrangespec *spec) {
+    return zslValueInMinRange(value,spec) && zslValueInMaxRange(value,spec);
+}
+
+/* Returns if there is a part of the zset is in range. */
+int zslIsInRange(zskiplist *zsl, zrangespec *range) {
+    zskiplistNode *x;
+
+    x = zsl->tail;
+    if (x == NULL || !zslValueInMinRange(x->score,range))
+        return 0;
+    x = zsl->header->level[0].forward;
+    if (x == NULL || !zslValueInMaxRange(x->score,range))
+        return 0;
+    return 1;
+}
+
+/* Find the first node that is contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslFirstInRange(zskiplist *zsl, zrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *OUT* of range. */
+        while (x->level[i].forward &&
+            !zslValueInMinRange(x->level[i].forward->score,&range))
+                x = x->level[i].forward;
+    }
+
+    /* The tail is in range, so the previous block should always return a
+     * node that is non-NULL and the last one to be out of range. */
+    x = x->level[0].forward;
+    redisAssert(x != NULL && zslValueInRange(x->score,&range));
+    return x;
+}
+
+/* Find the last node that is contained in the specified range.
+ * Returns NULL when no element is contained in the range. */
+zskiplistNode *zslLastInRange(zskiplist *zsl, zrangespec range) {
+    zskiplistNode *x;
+    int i;
+
+    /* If everything is out of range, return early. */
+    if (!zslIsInRange(zsl,&range)) return NULL;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        /* Go forward while *IN* range. */
+        while (x->level[i].forward &&
+            zslValueInMaxRange(x->level[i].forward->score,&range))
+                x = x->level[i].forward;
+    }
+
+    /* The header is in range, so the previous block should always return a
+     * node that is non-NULL and in range. */
+    redisAssert(x != NULL && zslValueInRange(x->score,&range));
+    return x;
+}
+
 /* Delete all the elements with score between min and max from the skiplist.
  * Min and mx are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
@@ -243,22 +315,6 @@ unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned
     return removed;
 }
 
-/* Find the first node having a score equal or greater than the specified one.
- * Returns NULL if there is no match. */
-zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
-    zskiplistNode *x;
-    int i;
-
-    x = zsl->header;
-    for (i = zsl->level-1; i >= 0; i--) {
-        while (x->level[i].forward && x->level[i].forward->score < score)
-            x = x->level[i].forward;
-    }
-    /* We may have multiple elements with the same score, what we need
-     * is to find the element with both the right score and object. */
-    return x->level[0].forward;
-}
-
 /* Find the rank for an element by both score and key.
  * Returns 0 when the element cannot be found, rank otherwise.
  * Note that the rank is 1-based due to the span of zsl->header to the
@@ -847,9 +903,18 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
     int withscores = 0;
     unsigned long rangelen = 0;
     void *replylen = NULL;
+    int minidx, maxidx;
 
     /* Parse the range arguments. */
-    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+    if (reverse) {
+        /* Range is given as [max,min] */
+        maxidx = 2; minidx = 3;
+    } else {
+        /* Range is given as [min,max] */
+        minidx = 2; maxidx = 3;
+    }
+
+    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
         addReplyError(c,"min or max is not a double");
         return;
     }
@@ -882,33 +947,11 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
     zsetobj = o->ptr;
     zsl = zsetobj->zsl;
 
-    /* If reversed, assume the elements are sorted from high to low score. */
-    ln = zslFirstWithScore(zsl,range.min);
+    /* If reversed, get the last node in range as starting point. */
     if (reverse) {
-        /* If range.min is out of range, ln will be NULL and we need to use
-         * the tail of the skiplist as first node of the range. */
-        if (ln == NULL) ln = zsl->tail;
-
-        /* zslFirstWithScore returns the first element with where with
-         * score >= range.min, so backtrack to make sure the element we use
-         * here has score <= range.min. */
-        while (ln && ln->score > range.min) ln = ln->backward;
-
-        /* Move to the right element according to the range spec. */
-        if (range.minex) {
-            /* Find last element with score < range.min */
-            while (ln && ln->score == range.min) ln = ln->backward;
-        } else {
-            /* Find last element with score <= range.min */
-            while (ln && ln->level[0].forward &&
-                         ln->level[0].forward->score == range.min)
-                ln = ln->level[0].forward;
-        }
+        ln = zslLastInRange(zsl,range);
     } else {
-        if (range.minex) {
-            /* Find first element with score > range.min */
-            while (ln && ln->score == range.min) ln = ln->level[0].forward;
-        }
+        ln = zslFirstInRange(zsl,range);
     }
 
     /* No "first" element in the specified interval. */
@@ -917,40 +960,24 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
         return;
     }
 
-    /* We don't know in advance how many matching elements there
-     * are in the list, so we push this object that will represent
-     * the multi-bulk length in the output buffer, and will "fix"
-     * it later */
+    /* We don't know in advance how many matching elements there are in the
+     * list, so we push this object that will represent the multi-bulk length
+     * in the output buffer, and will "fix" it later */
     if (!justcount)
         replylen = addDeferredMultiBulkLength(c);
 
     /* If there is an offset, just traverse the number of elements without
      * checking the score because that is done in the next loop. */
     while(ln && offset--) {
-        if (reverse)
-            ln = ln->backward;
-        else
-            ln = ln->level[0].forward;
+        ln = reverse ? ln->backward : ln->level[0].forward;
     }
 
     while (ln && limit--) {
-        /* Check if this this element is in range. */
+        /* Abort when the node is no longer in range. */
         if (reverse) {
-            if (range.maxex) {
-                /* Element should have score > range.max */
-                if (ln->score <= range.max) break;
-            } else {
-                /* Element should have score >= range.max */
-                if (ln->score < range.max) break;
-            }
+            if (!zslValueInMinRange(ln->score,&range)) break;
         } else {
-            if (range.maxex) {
-                /* Element should have score < range.max */
-                if (ln->score >= range.max) break;
-            } else {
-                /* Element should have score <= range.max */
-                if (ln->score > range.max) break;
-            }
+            if (!zslValueInMaxRange(ln->score,&range)) break;
         }
 
         /* Do our magic */
@@ -961,10 +988,8 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
                 addReplyDouble(c,ln->score);
         }
 
-        if (reverse)
-            ln = ln->backward;
-        else
-            ln = ln->level[0].forward;
+        /* Move to next node */
+        ln = reverse ? ln->backward : ln->level[0].forward;
     }
 
     if (justcount) {