@@ -24,13 +24,7 @@
  * from tail to head, useful for ZREVRANGE. */
 
 zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
-    zskiplistNode *zn = zmalloc(sizeof(*zn));
-
-    zn->forward = zmalloc(sizeof(zskiplistNode*) * level);
-    if (level > 1)
-        zn->span = zmalloc(sizeof(unsigned int) * (level - 1));
-    else
-        zn->span = NULL;
+    zskiplistNode *zn = zmalloc(sizeof(*zn)+level*sizeof(struct zskiplistLevel));
     zn->score = score;
     zn->obj = obj;
     return zn;
@@ -45,11 +39,8 @@ zskiplist *zslCreate(void) {
     zsl->length = 0;
     zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
     for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++) {
-        zsl->header->forward[j] = NULL;
-
-        /* span has space for ZSKIPLIST_MAXLEVEL-1 elements */
-        if (j < ZSKIPLIST_MAXLEVEL-1)
-            zsl->header->span[j] = 0;
+        zsl->header->level[j].forward = NULL;
+        zsl->header->level[j].span = 0;
     }
     zsl->header->backward = NULL;
     zsl->tail = NULL;
@@ -58,19 +49,15 @@ zskiplist *zslCreate(void) {
 
 void zslFreeNode(zskiplistNode *node) {
     decrRefCount(node->obj);
-    zfree(node->forward);
-    zfree(node->span);
     zfree(node);
 }
 
 void zslFree(zskiplist *zsl) {
-    zskiplistNode *node = zsl->header->forward[0], *next;
+    zskiplistNode *node = zsl->header->level[0].forward, *next;
 
-    zfree(zsl->header->forward);
-    zfree(zsl->header->span);
     zfree(zsl->header);
     while(node) {
-        next = node->forward[0];
+        next = node->level[0].forward;
         zslFreeNode(node);
         node = next;
     }
@@ -84,7 +71,7 @@ int zslRandomLevel(void) {
     return (level<ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL;
 }
 
-void zslInsert(zskiplist *zsl, double score, robj *obj) {
+zskiplistNode *zslInsert(zskiplist *zsl, double score, robj *obj) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     unsigned int rank[ZSKIPLIST_MAXLEVEL];
     int i, level;
@@ -93,13 +80,12 @@ void zslInsert(zskiplist *zsl, double score, robj *obj) {
     for (i = zsl->level-1; i >= 0; i--) {
         /* store rank that is crossed to reach the insert position */
         rank[i] = i == (zsl->level-1) ? 0 : rank[i+1];
-
-        while (x->forward[i] &&
-            (x->forward[i]->score < score ||
-                (x->forward[i]->score == score &&
-                compareStringObjects(x->forward[i]->obj,obj) < 0))) {
-            rank[i] += i > 0 ? x->span[i-1] : 1;
-            x = x->forward[i];
+        while (x->level[i].forward &&
+            (x->level[i].forward->score < score ||
+                (x->level[i].forward->score == score &&
+                compareStringObjects(x->level[i].forward->obj,obj) < 0))) {
+            rank[i] += x->level[i].span;
+            x = x->level[i].forward;
         }
         update[i] = x;
     }
@@ -112,56 +98,51 @@ void zslInsert(zskiplist *zsl, double score, robj *obj) {
         for (i = zsl->level; i < level; i++) {
             rank[i] = 0;
             update[i] = zsl->header;
-            update[i]->span[i-1] = zsl->length;
+            update[i]->level[i].span = zsl->length;
         }
         zsl->level = level;
     }
     x = zslCreateNode(level,score,obj);
     for (i = 0; i < level; i++) {
-        x->forward[i] = update[i]->forward[i];
-        update[i]->forward[i] = x;
+        x->level[i].forward = update[i]->level[i].forward;
+        update[i]->level[i].forward = x;
 
         /* update span covered by update[i] as x is inserted here */
-        if (i > 0) {
-            x->span[i-1] = update[i]->span[i-1] - (rank[0] - rank[i]);
-            update[i]->span[i-1] = (rank[0] - rank[i]) + 1;
-        }
+        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
+        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
     }
 
     /* increment span for untouched levels */
     for (i = level; i < zsl->level; i++) {
-        update[i]->span[i-1]++;
+        update[i]->level[i].span++;
     }
 
     x->backward = (update[0] == zsl->header) ? NULL : update[0];
-    if (x->forward[0])
-        x->forward[0]->backward = x;
+    if (x->level[0].forward)
+        x->level[0].forward->backward = x;
     else
         zsl->tail = x;
     zsl->length++;
+    return x;
 }
 
 /* Internal function used by zslDelete, zslDeleteByScore and zslDeleteByRank */
 void zslDeleteNode(zskiplist *zsl, zskiplistNode *x, zskiplistNode **update) {
     int i;
     for (i = 0; i < zsl->level; i++) {
-        if (update[i]->forward[i] == x) {
-            if (i > 0) {
-                update[i]->span[i-1] += x->span[i-1] - 1;
-            }
-            update[i]->forward[i] = x->forward[i];
+        if (update[i]->level[i].forward == x) {
+            update[i]->level[i].span += x->level[i].span - 1;
+            update[i]->level[i].forward = x->level[i].forward;
         } else {
-            /* invariant: i > 0, because update[0]->forward[0]
-             * is always equal to x */
-            update[i]->span[i-1] -= 1;
+            update[i]->level[i].span -= 1;
         }
     }
-    if (x->forward[0]) {
-        x->forward[0]->backward = x->backward;
+    if (x->level[0].forward) {
+        x->level[0].forward->backward = x->backward;
     } else {
         zsl->tail = x->backward;
     }
-    while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
+    while(zsl->level > 1 && zsl->header->level[zsl->level-1].forward == NULL)
         zsl->level--;
     zsl->length--;
 }
@@ -173,16 +154,16 @@ int zslDelete(zskiplist *zsl, double score, robj *obj) {
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] &&
-            (x->forward[i]->score < score ||
-                (x->forward[i]->score == score &&
-                compareStringObjects(x->forward[i]->obj,obj) < 0)))
-            x = x->forward[i];
+        while (x->level[i].forward &&
+            (x->level[i].forward->score < score ||
+                (x->level[i].forward->score == score &&
+                compareStringObjects(x->level[i].forward->obj,obj) < 0)))
+            x = x->level[i].forward;
         update[i] = x;
     }
     /* We may have multiple elements with the same score, what we need
      * is to find the element with both the right score and object. */
-    x = x->forward[0];
+    x = x->level[0].forward;
     if (x && score == x->score && equalStringObjects(x->obj,obj)) {
         zslDeleteNode(zsl, x, update);
         zslFreeNode(x);
@@ -204,16 +185,16 @@ unsigned long zslDeleteRangeByScore(zskiplist *zsl, double min, double max, dict
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] && x->forward[i]->score < min)
-            x = x->forward[i];
+        while (x->level[i].forward && x->level[i].forward->score < min)
+            x = x->level[i].forward;
         update[i] = x;
     }
     /* We may have multiple elements with the same score, what we need
      * is to find the element with both the right score and object. */
-    x = x->forward[0];
+    x = x->level[0].forward;
     while (x && x->score <= max) {
-        zskiplistNode *next = x->forward[0];
-        zslDeleteNode(zsl, x, update);
+        zskiplistNode *next = x->level[0].forward;
+        zslDeleteNode(zsl,x,update);
         dictDelete(dict,x->obj);
         zslFreeNode(x);
         removed++;
@@ -231,18 +212,18 @@ unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] && (traversed + (i > 0 ? x->span[i-1] : 1)) < start) {
-            traversed += i > 0 ? x->span[i-1] : 1;
-            x = x->forward[i];
+        while (x->level[i].forward && (traversed + x->level[i].span) < start) {
+            traversed += x->level[i].span;
+            x = x->level[i].forward;
         }
         update[i] = x;
     }
 
     traversed++;
-    x = x->forward[0];
+    x = x->level[0].forward;
     while (x && traversed <= end) {
-        zskiplistNode *next = x->forward[0];
-        zslDeleteNode(zsl, x, update);
+        zskiplistNode *next = x->level[0].forward;
+        zslDeleteNode(zsl,x,update);
         dictDelete(dict,x->obj);
         zslFreeNode(x);
         removed++;
@@ -260,12 +241,12 @@ zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] && x->forward[i]->score < score)
-            x = x->forward[i];
+        while (x->level[i].forward && x->level[i].forward->score < score)
+            x = x->level[i].forward;
     }
     /* We may have multiple elements with the same score, what we need
      * is to find the element with both the right score and object. */
-    return x->forward[0];
+    return x->level[0].forward;
 }
 
 /* Find the rank for an element by both score and key.
@@ -279,12 +260,12 @@ unsigned long zslistTypeGetRank(zskiplist *zsl, double score, robj *o) {
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] &&
-            (x->forward[i]->score < score ||
-                (x->forward[i]->score == score &&
-                compareStringObjects(x->forward[i]->obj,o) <= 0))) {
-            rank += i > 0 ? x->span[i-1] : 1;
-            x = x->forward[i];
+        while (x->level[i].forward &&
+            (x->level[i].forward->score < score ||
+                (x->level[i].forward->score == score &&
+                compareStringObjects(x->level[i].forward->obj,o) <= 0))) {
+            rank += x->level[i].span;
+            x = x->level[i].forward;
         }
 
         /* x might be equal to zsl->header, so test if obj is non-NULL */
@@ -303,10 +284,10 @@ zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] && (traversed + (i>0 ? x->span[i-1] : 1)) <= rank)
+        while (x->level[i].forward && (traversed + x->level[i].span) <= rank)
         {
-            traversed += i > 0 ? x->span[i-1] : 1;
-            x = x->forward[i];
+            traversed += x->level[i].span;
+            x = x->level[i].forward;
         }
         if (traversed == rank) {
             return x;
@@ -319,13 +300,11 @@ zskiplistNode* zslistTypeGetElementByRank(zskiplist *zsl, unsigned long rank) {
  * Sorted set commands 
  *----------------------------------------------------------------------------*/
 
-/* This generic command implements both ZADD and ZINCRBY.
- * scoreval is the score if the operation is a ZADD (doincrement == 0) or
- * the increment if the operation is a ZINCRBY (doincrement == 1). */
-void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, int doincrement) {
+/* This generic command implements both ZADD and ZINCRBY. */
+void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int incr) {
     robj *zsetobj;
     zset *zs;
-    double *score;
+    zskiplistNode *znode;
 
     zsetobj = lookupKeyWrite(c->db,key);
     if (zsetobj == NULL) {
@@ -339,72 +318,72 @@ void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, i
     }
     zs = zsetobj->ptr;
 
-    /* Ok now since we implement both ZADD and ZINCRBY here the code
-     * needs to handle the two different conditions. It's all about setting
-     * '*score', that is, the new score to set, to the right value. */
-    score = zmalloc(sizeof(double));
-    if (doincrement) {
-        dictEntry *de;
-
+    /* Since both ZADD and ZINCRBY are implemented here, we need to increment
+     * the score first by the current score if ZINCRBY is called. */
+    if (incr) {
         /* Read the old score. If the element was not present starts from 0 */
-        de = dictFind(zs->dict,ele);
-        if (de) {
-            double *oldscore = dictGetEntryVal(de);
-            *score = *oldscore + scoreval;
-        } else {
-            *score = scoreval;
-        }
-        if (isnan(*score)) {
-            addReplySds(c,
-                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
-            zfree(score);
+        dictEntry *de = dictFind(zs->dict,ele);
+        if (de != NULL)
+            score += *(double*)dictGetEntryVal(de);
+
+        if (isnan(score)) {
+            addReplyError(c,"resulting score is not a number (NaN)");
             /* Note that we don't need to check if the zset may be empty and
              * should be removed here, as we can only obtain Nan as score if
              * there was already an element in the sorted set. */
             return;
         }
-    } else {
-        *score = scoreval;
     }
 
-    /* What follows is a simple remove and re-insert operation that is common
-     * to both ZADD and ZINCRBY... */
-    if (dictAdd(zs->dict,ele,score) == DICT_OK) {
-        /* case 1: New element */
+    /* We need to remove and re-insert the element when it was already present
+     * in the dictionary, to update the skiplist. Note that we delay adding a
+     * pointer to the score because we want to reference the score in the
+     * skiplist node. */
+    if (dictAdd(zs->dict,ele,NULL) == DICT_OK) {
+        dictEntry *de;
+
+        /* New element */
         incrRefCount(ele); /* added to hash */
-        zslInsert(zs->zsl,*score,ele);
+        znode = zslInsert(zs->zsl,score,ele);
         incrRefCount(ele); /* added to skiplist */
+
+        /* Update the score in the dict entry */
+        de = dictFind(zs->dict,ele);
+        redisAssert(de != NULL);
+        dictGetEntryVal(de) = &znode->score;
         touchWatchedKey(c->db,c->argv[1]);
         server.dirty++;
-        if (doincrement)
-            addReplyDouble(c,*score);
+        if (incr)
+            addReplyDouble(c,score);
         else
             addReply(c,shared.cone);
     } else {
         dictEntry *de;
-        double *oldscore;
+        robj *curobj;
+        double *curscore;
+        int deleted;
 
-        /* case 2: Score update operation */
+        /* Update score */
         de = dictFind(zs->dict,ele);
         redisAssert(de != NULL);
-        oldscore = dictGetEntryVal(de);
-        if (*score != *oldscore) {
-            int deleted;
+        curobj = dictGetEntryKey(de);
+        curscore = dictGetEntryVal(de);
 
-            /* Remove and insert the element in the skip list with new score */
-            deleted = zslDelete(zs->zsl,*oldscore,ele);
+        /* When the score is updated, reuse the existing string object to
+         * prevent extra alloc/dealloc of strings on ZINCRBY. */
+        if (score != *curscore) {
+            deleted = zslDelete(zs->zsl,*curscore,curobj);
             redisAssert(deleted != 0);
-            zslInsert(zs->zsl,*score,ele);
-            incrRefCount(ele);
-            /* Update the score in the hash table */
-            dictReplace(zs->dict,ele,score);
+            znode = zslInsert(zs->zsl,score,curobj);
+            incrRefCount(curobj);
+
+            /* Update the score in the current dict entry */
+            dictGetEntryVal(de) = &znode->score;
             touchWatchedKey(c->db,c->argv[1]);
             server.dirty++;
-        } else {
-            zfree(score);
         }
-        if (doincrement)
-            addReplyDouble(c,*score);
+        if (incr)
+            addReplyDouble(c,score);
         else
             addReply(c,shared.czero);
     }
@@ -426,7 +405,7 @@ void zremCommand(redisClient *c) {
     robj *zsetobj;
     zset *zs;
     dictEntry *de;
-    double *oldscore;
+    double curscore;
     int deleted;
 
     if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
@@ -439,8 +418,8 @@ void zremCommand(redisClient *c) {
         return;
     }
     /* Delete from the skiplist */
-    oldscore = dictGetEntryVal(de);
-    deleted = zslDelete(zs->zsl,*oldscore,c->argv[2]);
+    curscore = *(double*)dictGetEntryVal(de);
+    deleted = zslDelete(zs->zsl,curscore,c->argv[2]);
     redisAssert(deleted != 0);
 
     /* Delete from the hash table */
@@ -554,14 +533,16 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     zsetopsrc *src;
     robj *dstobj;
     zset *dstzset;
+    zskiplistNode *znode;
     dictIterator *di;
     dictEntry *de;
     int touched = 0;
 
     /* expect setnum input keys to be given */
     setnum = atoi(c->argv[2]->ptr);
     if (setnum < 1) {
-        addReplySds(c,sdsnew("-ERR at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE\r\n"));
+        addReplyError(c,
+            "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
         return;
     }
 
@@ -644,28 +625,26 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
              * from small to large, all src[i > 0].dict are non-empty too */
             di = dictGetIterator(src[0].dict);
             while((de = dictNext(di)) != NULL) {
-                double *score = zmalloc(sizeof(double)), value;
-                *score = src[0].weight * zunionInterDictValue(de);
+                double score, value;
 
+                score = src[0].weight * zunionInterDictValue(de);
                 for (j = 1; j < setnum; j++) {
                     dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
                     if (other) {
                         value = src[j].weight * zunionInterDictValue(other);
-                        zunionInterAggregate(score, value, aggregate);
+                        zunionInterAggregate(&score, value, aggregate);
                     } else {
                         break;
                     }
                 }
 
-                /* skip entry when not present in every source dict */
-                if (j != setnum) {
-                    zfree(score);
-                } else {
+                /* accept entry only when present in every source dict */
+                if (j == setnum) {
                     robj *o = dictGetEntryKey(de);
-                    dictAdd(dstzset->dict,o,score);
-                    incrRefCount(o); /* added to dictionary */
-                    zslInsert(dstzset->zsl,*score,o);
+                    znode = zslInsert(dstzset->zsl,score,o);
                     incrRefCount(o); /* added to skiplist */
+                    dictAdd(dstzset->dict,o,&znode->score);
+                    incrRefCount(o); /* added to dictionary */
                 }
             }
             dictReleaseIterator(di);
@@ -676,27 +655,28 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
 
             di = dictGetIterator(src[i].dict);
             while((de = dictNext(di)) != NULL) {
-                /* skip key when already processed */
-                if (dictFind(dstzset->dict,dictGetEntryKey(de)) != NULL) continue;
+                double score, value;
 
-                double *score = zmalloc(sizeof(double)), value;
-                *score = src[i].weight * zunionInterDictValue(de);
+                /* skip key when already processed */
+                if (dictFind(dstzset->dict,dictGetEntryKey(de)) != NULL)
+                    continue;
+                score = src[i].weight * zunionInterDictValue(de);
 
                 /* because the zsets are sorted by size, its only possible
                  * for sets at larger indices to hold this entry */
                 for (j = (i+1); j < setnum; j++) {
                     dictEntry *other = dictFind(src[j].dict,dictGetEntryKey(de));
                     if (other) {
                         value = src[j].weight * zunionInterDictValue(other);
-                        zunionInterAggregate(score, value, aggregate);
+                        zunionInterAggregate(&score, value, aggregate);
                     }
                 }
 
                 robj *o = dictGetEntryKey(de);
-                dictAdd(dstzset->dict,o,score);
-                incrRefCount(o); /* added to dictionary */
-                zslInsert(dstzset->zsl,*score,o);
+                znode = zslInsert(dstzset->zsl,score,o);
                 incrRefCount(o); /* added to skiplist */
+                dictAdd(dstzset->dict,o,&znode->score);
+                incrRefCount(o); /* added to dictionary */
             }
             dictReleaseIterator(di);
         }
@@ -778,18 +758,17 @@ void zrangeGenericCommand(redisClient *c, int reverse) {
         ln = start == 0 ? zsl->tail : zslistTypeGetElementByRank(zsl, llen-start);
     } else {
         ln = start == 0 ?
-            zsl->header->forward[0] : zslistTypeGetElementByRank(zsl, start+1);
+            zsl->header->level[0].forward : zslistTypeGetElementByRank(zsl, start+1);
     }
 
     /* Return the result in form of a multi-bulk reply */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
-        withscores ? (rangelen*2) : rangelen));
+    addReplyMultiBulkLen(c,withscores ? (rangelen*2) : rangelen);
     for (j = 0; j < rangelen; j++) {
         ele = ln->obj;
         addReplyBulk(c,ele);
         if (withscores)
             addReplyDouble(c,ln->score);
-        ln = reverse ? ln->backward : ln->forward[0];
+        ln = reverse ? ln->backward : ln->level[0].forward;
     }
 }
 
@@ -840,8 +819,7 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
     if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
         badsyntax = 1;
     if (badsyntax) {
-        addReplySds(c,
-            sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
+        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
         return;
     }
 
@@ -866,13 +844,14 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
             zset *zsetobj = o->ptr;
             zskiplist *zsl = zsetobj->zsl;
             zskiplistNode *ln;
-            robj *ele, *lenobj = NULL;
+            robj *ele;
+            void *replylen = NULL;
             unsigned long rangelen = 0;
 
             /* Get the first node with the score >= min, or with
              * score > min if 'minex' is true. */
             ln = zslFirstWithScore(zsl,min);
-            while (minex && ln && ln->score == min) ln = ln->forward[0];
+            while (minex && ln && ln->score == min) ln = ln->level[0].forward;
 
             if (ln == NULL) {
                 /* No element matching the speciifed interval */
@@ -884,16 +863,13 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
              * are in the list, so we push this object that will represent
              * the multi-bulk length in the output buffer, and will "fix"
              * it later */
-            if (!justcount) {
-                lenobj = createObject(REDIS_STRING,NULL);
-                addReply(c,lenobj);
-                decrRefCount(lenobj);
-            }
+            if (!justcount)
+                replylen = addDeferredMultiBulkLength(c);
 
             while(ln && (maxex ? (ln->score < max) : (ln->score <= max))) {
                 if (offset) {
                     offset--;
-                    ln = ln->forward[0];
+                    ln = ln->level[0].forward;
                     continue;
                 }
                 if (limit == 0) break;
@@ -903,14 +879,14 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
                     if (withscores)
                         addReplyDouble(c,ln->score);
                 }
-                ln = ln->forward[0];
+                ln = ln->level[0].forward;
                 rangelen++;
                 if (limit > 0) limit--;
             }
             if (justcount) {
                 addReplyLongLong(c,(long)rangelen);
             } else {
-                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
+                setDeferredMultiBulkLength(c,replylen,
                      withscores ? (rangelen*2) : rangelen);
             }
         }
@@ -933,7 +909,7 @@ void zcardCommand(redisClient *c) {
         checkType(c,o,REDIS_ZSET)) return;
 
     zs = o->ptr;
-    addReplyUlong(c,zs->zsl->length);
+    addReplyLongLong(c,zs->zsl->length);
 }
 
 void zscoreCommand(redisClient *c) {