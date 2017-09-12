@@ -296,6 +296,44 @@ zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
     return NULL;
 }
 
+typedef struct {
+    double min, max;
+    int minex, maxex; /* are min or max exclusive? */
+} zrangespec;
+
+/* Populate the rangespec according to the objects min and max. */
+int zslParseRange(robj *min, robj *max, zrangespec *spec) {
+    spec->minex = spec->maxex = 0;
+
+    /* Parse the min-max interval. If one of the values is prefixed
+     * by the "(" character, it's considered "open". For instance
+     * ZRANGEBYSCORE zset (1.5 (2.5 will match min < x < max
+     * ZRANGEBYSCORE zset 1.5 2.5 will instead match min <= x <= max */
+    if (min->encoding == REDIS_ENCODING_INT) {
+        spec->min = (long)min->ptr;
+    } else {
+        if (((char*)min->ptr)[0] == '(') {
+            spec->min = strtod((char*)min->ptr+1,NULL);
+            spec->minex = 1;
+        } else {
+            spec->min = strtod((char*)min->ptr,NULL);
+        }
+    }
+    if (max->encoding == REDIS_ENCODING_INT) {
+        spec->max = (long)max->ptr;
+    } else {
+        if (((char*)max->ptr)[0] == '(') {
+            spec->max = strtod((char*)max->ptr+1,NULL);
+            spec->maxex = 1;
+        } else {
+            spec->max = strtod((char*)max->ptr,NULL);
+        }
+    }
+
+    return REDIS_OK;
+}
+
+
 /*-----------------------------------------------------------------------------
  * Sorted set commands 
  *----------------------------------------------------------------------------*/
@@ -781,125 +819,153 @@ void zrevrangeCommand(redisClient *c) {
     zrangeGenericCommand(c,1);
 }
 
-/* This command implements both ZRANGEBYSCORE and ZCOUNT.
- * If justcount is non-zero, just the count is returned. */
-void genericZrangebyscoreCommand(redisClient *c, int justcount) {
-    robj *o;
-    double min, max;
-    int minex = 0, maxex = 0; /* are min or max exclusive? */
+/* This command implements ZRANGEBYSCORE, ZREVRANGEBYSCORE and ZCOUNT.
+ * If "justcount", only the number of elements in the range is returned. */
+void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
+    zrangespec range;
+    robj *o, *emptyreply;
+    zset *zsetobj;
+    zskiplist *zsl;
+    zskiplistNode *ln;
     int offset = 0, limit = -1;
     int withscores = 0;
-    int badsyntax = 0;
+    unsigned long rangelen = 0;
+    void *replylen = NULL;
 
-    /* Parse the min-max interval. If one of the values is prefixed
-     * by the "(" character, it's considered "open". For instance
-     * ZRANGEBYSCORE zset (1.5 (2.5 will match min < x < max
-     * ZRANGEBYSCORE zset 1.5 2.5 will instead match min <= x <= max */
-    if (((char*)c->argv[2]->ptr)[0] == '(') {
-        min = strtod((char*)c->argv[2]->ptr+1,NULL);
-        minex = 1;
-    } else {
-        min = strtod(c->argv[2]->ptr,NULL);
+    /* Parse the range arguments. */
+    zslParseRange(c->argv[2],c->argv[3],&range);
+
+    /* Parse optional extra arguments. Note that ZCOUNT will exactly have
+     * 4 arguments, so we'll never enter the following code path. */
+    if (c->argc > 4) {
+        int remaining = c->argc - 4;
+        int pos = 4;
+
+        while (remaining) {
+            if (remaining >= 1 && !strcasecmp(c->argv[pos]->ptr,"withscores")) {
+                pos++; remaining--;
+                withscores = 1;
+            } else if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
+                offset = atoi(c->argv[pos+1]->ptr);
+                limit = atoi(c->argv[pos+2]->ptr);
+                pos += 3; remaining -= 3;
+            } else {
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        }
     }
-    if (((char*)c->argv[3]->ptr)[0] == '(') {
-        max = strtod((char*)c->argv[3]->ptr+1,NULL);
-        maxex = 1;
+
+    /* Ok, lookup the key and get the range */
+    emptyreply = justcount ? shared.czero : shared.emptymultibulk;
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],emptyreply)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
+    zsetobj = o->ptr;
+    zsl = zsetobj->zsl;
+
+    /* If reversed, assume the elements are sorted from high to low score. */
+    ln = zslFirstWithScore(zsl,range.min);
+    if (reverse) {
+        /* If range.min is out of range, ln will be NULL and we need to use
+         * the tail of the skiplist as first node of the range. */
+        if (ln == NULL) ln = zsl->tail;
+
+        /* zslFirstWithScore returns the first element with where with
+         * score >= range.min, so backtrack to make sure the element we use
+         * here has score <= range.min. */
+        while (ln && ln->score > range.min) ln = ln->backward;
+
+        /* Move to the right element according to the range spec. */
+        if (range.minex) {
+            /* Find last element with score < range.min */
+            while (ln && ln->score == range.min) ln = ln->backward;
+        } else {
+            /* Find last element with score <= range.min */
+            while (ln && ln->level[0].forward &&
+                         ln->level[0].forward->score == range.min)
+                ln = ln->level[0].forward;
+        }
     } else {
-        max = strtod(c->argv[3]->ptr,NULL);
+        if (range.minex) {
+            /* Find first element with score > range.min */
+            while (ln && ln->score == range.min) ln = ln->level[0].forward;
+        }
     }
 
-    /* Parse "WITHSCORES": note that if the command was called with
-     * the name ZCOUNT then we are sure that c->argc == 4, so we'll never
-     * enter the following paths to parse WITHSCORES and LIMIT. */
-    if (c->argc == 5 || c->argc == 8) {
-        if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0)
-            withscores = 1;
-        else
-            badsyntax = 1;
-    }
-    if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
-        badsyntax = 1;
-    if (badsyntax) {
-        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
+    /* No "first" element in the specified interval. */
+    if (ln == NULL) {
+        addReply(c,emptyreply);
         return;
     }
 
-    /* Parse "LIMIT" */
-    if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
-        addReply(c,shared.syntaxerr);
-        return;
-    } else if (c->argc == (7 + withscores)) {
-        offset = atoi(c->argv[5]->ptr);
-        limit = atoi(c->argv[6]->ptr);
-        if (offset < 0) offset = 0;
+    /* We don't know in advance how many matching elements there
+     * are in the list, so we push this object that will represent
+     * the multi-bulk length in the output buffer, and will "fix"
+     * it later */
+    if (!justcount)
+        replylen = addDeferredMultiBulkLength(c);
+
+    /* If there is an offset, just traverse the number of elements without
+     * checking the score because that is done in the next loop. */
+    while(ln && offset--) {
+        if (reverse)
+            ln = ln->backward;
+        else
+            ln = ln->level[0].forward;
     }
 
-    /* Ok, lookup the key and get the range */
-    o = lookupKeyRead(c->db,c->argv[1]);
-    if (o == NULL) {
-        addReply(c,justcount ? shared.czero : shared.emptymultibulk);
-    } else {
-        if (o->type != REDIS_ZSET) {
-            addReply(c,shared.wrongtypeerr);
-        } else {
-            zset *zsetobj = o->ptr;
-            zskiplist *zsl = zsetobj->zsl;
-            zskiplistNode *ln;
-            robj *ele;
-            void *replylen = NULL;
-            unsigned long rangelen = 0;
-
-            /* Get the first node with the score >= min, or with
-             * score > min if 'minex' is true. */
-            ln = zslFirstWithScore(zsl,min);
-            while (minex && ln && ln->score == min) ln = ln->level[0].forward;
-
-            if (ln == NULL) {
-                /* No element matching the speciifed interval */
-                addReply(c,justcount ? shared.czero : shared.emptymultibulk);
-                return;
-            }
-
-            /* We don't know in advance how many matching elements there
-             * are in the list, so we push this object that will represent
-             * the multi-bulk length in the output buffer, and will "fix"
-             * it later */
-            if (!justcount)
-                replylen = addDeferredMultiBulkLength(c);
-
-            while(ln && (maxex ? (ln->score < max) : (ln->score <= max))) {
-                if (offset) {
-                    offset--;
-                    ln = ln->level[0].forward;
-                    continue;
-                }
-                if (limit == 0) break;
-                if (!justcount) {
-                    ele = ln->obj;
-                    addReplyBulk(c,ele);
-                    if (withscores)
-                        addReplyDouble(c,ln->score);
-                }
-                ln = ln->level[0].forward;
-                rangelen++;
-                if (limit > 0) limit--;
+    while (ln && limit--) {
+        /* Check if this this element is in range. */
+        if (reverse) {
+            if (range.maxex) {
+                /* Element should have score > range.max */
+                if (ln->score <= range.max) break;
+            } else {
+                /* Element should have score >= range.max */
+                if (ln->score < range.max) break;
             }
-            if (justcount) {
-                addReplyLongLong(c,(long)rangelen);
+        } else {
+            if (range.maxex) {
+                /* Element should have score < range.max */
+                if (ln->score >= range.max) break;
             } else {
-                setDeferredMultiBulkLength(c,replylen,
-                     withscores ? (rangelen*2) : rangelen);
+                /* Element should have score <= range.max */
+                if (ln->score > range.max) break;
             }
         }
+
+        /* Do our magic */
+        rangelen++;
+        if (!justcount) {
+            addReplyBulk(c,ln->obj);
+            if (withscores)
+                addReplyDouble(c,ln->score);
+        }
+
+        if (reverse)
+            ln = ln->backward;
+        else
+            ln = ln->level[0].forward;
+    }
+
+    if (justcount) {
+        addReplyLongLong(c,(long)rangelen);
+    } else {
+        setDeferredMultiBulkLength(c,replylen,
+             withscores ? (rangelen*2) : rangelen);
     }
 }
 
 void zrangebyscoreCommand(redisClient *c) {
-    genericZrangebyscoreCommand(c,0);
+    genericZrangebyscoreCommand(c,0,0);
+}
+
+void zrevrangebyscoreCommand(redisClient *c) {
+    genericZrangebyscoreCommand(c,1,0);
 }
 
 void zcountCommand(redisClient *c) {
-    genericZrangebyscoreCommand(c,1);
+    genericZrangebyscoreCommand(c,0,1);
 }
 
 void zcardCommand(redisClient *c) {