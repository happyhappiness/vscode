@@ -174,33 +174,43 @@ int zslDelete(zskiplist *zsl, double score, robj *obj) {
     return 0; /* not found */
 }
 
+/* Struct to hold a inclusive/exclusive range spec. */
+typedef struct {
+    double min, max;
+    int minex, maxex; /* are min or max exclusive? */
+} zrangespec;
+
 /* Delete all the elements with score between min and max from the skiplist.
  * Min and mx are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
  * sorted set, in order to remove the elements from the hash table too. */
-unsigned long zslDeleteRangeByScore(zskiplist *zsl, double min, double max, dict *dict) {
+unsigned long zslDeleteRangeByScore(zskiplist *zsl, zrangespec range, dict *dict) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     unsigned long removed = 0;
     int i;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->level[i].forward && x->level[i].forward->score < min)
-            x = x->level[i].forward;
+        while (x->level[i].forward && (range.minex ?
+            x->level[i].forward->score <= range.min :
+            x->level[i].forward->score < range.min))
+                x = x->level[i].forward;
         update[i] = x;
     }
-    /* We may have multiple elements with the same score, what we need
-     * is to find the element with both the right score and object. */
+
+    /* Current node is the last with score < or <= min. */
     x = x->level[0].forward;
-    while (x && x->score <= max) {
+
+    /* Delete nodes while in range. */
+    while (x && (range.maxex ? x->score < range.max : x->score <= range.max)) {
         zskiplistNode *next = x->level[0].forward;
         zslDeleteNode(zsl,x,update);
         dictDelete(dict,x->obj);
         zslFreeNode(x);
         removed++;
         x = next;
     }
-    return removed; /* not found */
+    return removed;
 }
 
 /* Delete all the elements with rank between start and end from the skiplist.
@@ -296,6 +306,44 @@ zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
     return NULL;
 }
 
+/* Populate the rangespec according to the objects min and max. */
+static int zslParseRange(robj *min, robj *max, zrangespec *spec) {
+    char *eptr;
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
+            spec->min = strtod((char*)min->ptr+1,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
+            spec->minex = 1;
+        } else {
+            spec->min = strtod((char*)min->ptr,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->min)) return REDIS_ERR;
+        }
+    }
+    if (max->encoding == REDIS_ENCODING_INT) {
+        spec->max = (long)max->ptr;
+    } else {
+        if (((char*)max->ptr)[0] == '(') {
+            spec->max = strtod((char*)max->ptr+1,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
+            spec->maxex = 1;
+        } else {
+            spec->max = strtod((char*)max->ptr,&eptr);
+            if (eptr[0] != '\0' || isnan(spec->max)) return REDIS_ERR;
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
@@ -432,20 +480,22 @@ void zremCommand(redisClient *c) {
 }
 
 void zremrangebyscoreCommand(redisClient *c) {
-    double min;
-    double max;
+    zrangespec range;
     long deleted;
-    robj *zsetobj;
+    robj *o;
     zset *zs;
 
-    if ((getDoubleFromObjectOrReply(c, c->argv[2], &min, NULL) != REDIS_OK) ||
-        (getDoubleFromObjectOrReply(c, c->argv[3], &max, NULL) != REDIS_OK)) return;
+    /* Parse the range arguments. */
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max is not a double");
+        return;
+    }
 
-    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
-        checkType(c,zsetobj,REDIS_ZSET)) return;
+    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_ZSET)) return;
 
-    zs = zsetobj->ptr;
-    deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
+    zs = o->ptr;
+    deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
     if (htNeedsResize(zs->dict)) dictResize(zs->dict);
     if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
     if (deleted) touchWatchedKey(c->db,c->argv[1]);
@@ -632,13 +682,13 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
                     dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
                     if (other) {
                         value = src[j].weight * zunionInterDictValue(other);
-                        zunionInterAggregate(&score, value, aggregate);
+                        zunionInterAggregate(&score,value,aggregate);
                     } else {
                         break;
                     }
                 }
 
-                /* accept entry only when present in every source dict */
+                /* Only continue when present in every source dict. */
                 if (j == setnum) {
                     robj *o = dictGetEntryKey(de);
                     znode = zslInsert(dstzset->zsl,score,o);
@@ -660,6 +710,8 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
                 /* skip key when already processed */
                 if (dictFind(dstzset->dict,dictGetEntryKey(de)) != NULL)
                     continue;
+
+                /* initialize score */
                 score = src[i].weight * zunionInterDictValue(de);
 
                 /* because the zsets are sorted by size, its only possible
@@ -668,7 +720,7 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
                     dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
                     if (other) {
                         value = src[j].weight * zunionInterDictValue(other);
-                        zunionInterAggregate(&score, value, aggregate);
+                        zunionInterAggregate(&score,value,aggregate);
                     }
                 }
 
@@ -780,125 +832,156 @@ void zrevrangeCommand(redisClient *c) {
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
-    }
-    if (((char*)c->argv[3]->ptr)[0] == '(') {
-        max = strtod((char*)c->argv[3]->ptr+1,NULL);
-        maxex = 1;
-    } else {
-        max = strtod(c->argv[3]->ptr,NULL);
+    /* Parse the range arguments. */
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+        addReplyError(c,"min or max is not a double");
+        return;
     }
 
-    /* Parse "WITHSCORES": note that if the command was called with
-     * the name ZCOUNT then we are sure that c->argc == 4, so we'll never
-     * enter the following paths to parse WITHSCORES and LIMIT. */
-    if (c->argc == 5 || c->argc == 8) {
-        if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0)
-            withscores = 1;
-        else
-            badsyntax = 1;
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
-    if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
-        badsyntax = 1;
-    if (badsyntax) {
-        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
-        return;
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
+    } else {
+        if (range.minex) {
+            /* Find first element with score > range.min */
+            while (ln && ln->score == range.min) ln = ln->level[0].forward;
+        }
     }
 
-    /* Parse "LIMIT" */
-    if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
-        addReply(c,shared.syntaxerr);
+    /* No "first" element in the specified interval. */
+    if (ln == NULL) {
+        addReply(c,emptyreply);
         return;
-    } else if (c->argc == (7 + withscores)) {
-        offset = atoi(c->argv[5]->ptr);
-        limit = atoi(c->argv[6]->ptr);
-        if (offset < 0) offset = 0;
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
+    }
 
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