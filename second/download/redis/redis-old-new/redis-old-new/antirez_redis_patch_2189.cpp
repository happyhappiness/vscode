@@ -4844,7 +4844,8 @@ static zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
     zskiplistNode *zn = zmalloc(sizeof(*zn));
 
     zn->forward = zmalloc(sizeof(zskiplistNode*) * level);
-    zn->span = zmalloc(sizeof(unsigned int) * level);
+    if (level > 0)
+        zn->span = zmalloc(sizeof(unsigned int) * (level - 1));
     zn->score = score;
     zn->obj = obj;
     return zn;
@@ -4897,19 +4898,19 @@ static int zslRandomLevel(void) {
 
 static void zslInsert(zskiplist *zsl, double score, robj *obj) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
-    unsigned int span[ZSKIPLIST_MAXLEVEL];
+    unsigned int rank[ZSKIPLIST_MAXLEVEL];
     int i, level;
 
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
-        /* store span that is crossed to reach the insert position */
-        span[i] = i == (zsl->level-1) ? 0 : span[i+1];
+        /* store rank that is crossed to reach the insert position */
+        rank[i] = i == (zsl->level-1) ? 0 : rank[i+1];
 
         while (x->forward[i] &&
             (x->forward[i]->score < score ||
                 (x->forward[i]->score == score &&
                 compareStringObjects(x->forward[i]->obj,obj) < 0))) {
-            span[i] += x->span[i];
+            rank[i] += i > 0 ? x->span[i-1] : 1;
             x = x->forward[i];
         }
         update[i] = x;
@@ -4921,9 +4922,9 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
     level = zslRandomLevel();
     if (level > zsl->level) {
         for (i = zsl->level; i < level; i++) {
-            span[i] = 0;
+            rank[i] = 0;
             update[i] = zsl->header;
-            update[i]->span[i] = zsl->length;
+            update[i]->span[i-1] = zsl->length;
         }
         zsl->level = level;
     }
@@ -4933,13 +4934,15 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
         update[i]->forward[i] = x;
 
         /* update span covered by update[i] as x is inserted here */
-        x->span[i] = update[i]->span[i] - (span[0] - span[i]);
-        update[i]->span[i] = (span[0] - span[i]) + 1;
+        if (i > 0) {
+            x->span[i-1] = update[i]->span[i-1] - (rank[0] - rank[i]);
+            update[i]->span[i-1] = (rank[0] - rank[i]) + 1;
+        }
     }
 
     /* increment span for untouched levels */
     for (i = level; i < zsl->level; i++) {
-        update[i]->span[i]++;
+        update[i]->span[i-1]++;
     }
 
     x->backward = (update[0] == zsl->header) ? NULL : update[0];
@@ -4970,10 +4973,14 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     if (x && score == x->score && compareStringObjects(x->obj,obj) == 0) {
         for (i = 0; i < zsl->level; i++) {
             if (update[i]->forward[i] == x) {
-                update[i]->span[i] += x->span[i] - 1;
+                if (i > 0) {
+                    update[i]->span[i-1] += x->span[i-1] - 1;
+                }
                 update[i]->forward[i] = x->forward[i];
             } else {
-                update[i]->span[i] -= 1;
+                /* invariant: i > 0, because update[0]->forward[0]
+                 * is always equal to x */
+                update[i]->span[i-1] -= 1;
             }
         }
         if (x->forward[0]) {
@@ -5015,10 +5022,14 @@ static unsigned long zslDeleteRange(zskiplist *zsl, double min, double max, dict
 
         for (i = 0; i < zsl->level; i++) {
             if (update[i]->forward[i] == x) {
-                update[i]->span[i] += x->span[i] - 1;
+                if (i > 0) {
+                    update[i]->span[i-1] += x->span[i-1] - 1;
+                }
                 update[i]->forward[i] = x->forward[i];
             } else {
-                update[i]->span[i] -= 1;
+                /* invariant: i > 0, because update[0]->forward[0]
+                 * is always equal to x */
+                update[i]->span[i-1] -= 1;
             }
         }
         if (x->forward[0]) {
@@ -5054,6 +5065,53 @@ static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
     return x->forward[0];
 }
 
+/* Find the rank for an element by both score and key.
+ * Returns 0 when the element cannot be found, rank otherwise.
+ * Note that the rank is 1-based due to the span of zsl->header to the
+ * first element. */
+static unsigned long zslGetRank(zskiplist *zsl, double score, robj *o) {
+    zskiplistNode *x;
+    unsigned long rank = 0;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] &&
+            (x->forward[i]->score < score ||
+                (x->forward[i]->score == score &&
+                compareStringObjects(x->forward[i]->obj,o) <= 0))) {
+            rank += i > 0 ? x->span[i-1] : 1;
+            x = x->forward[i];
+        }
+
+        /* x might be equal to zsl->header, so test if obj is non-NULL */
+        if (x->obj && compareStringObjects(x->obj,o) == 0) {
+            return rank;
+        }
+    }
+    return 0;
+}
+
+/* Finds an element by its rank. The rank argument needs to be 1-based. */
+zskiplistNode* zslGetElementByRank(zskiplist *zsl, unsigned long rank) {
+    zskiplistNode *x;
+    unsigned long traversed = 0;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && (traversed + (i > 0 ? x->span[i-1] : 1)) <= rank) {
+            traversed += i > 0 ? x->span[i-1] : 1;
+            x = x->forward[i];
+        }
+
+        if (traversed == rank) {
+            return x;
+        }
+    }
+    return NULL;
+}
+
 /* The actual Z-commands implementations */
 
 /* This generic command implements both ZADD and ZINCRBY.
@@ -5253,17 +5311,15 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
             if (end >= llen) end = llen-1;
             rangelen = (end-start)+1;
 
-            /* Return the result in form of a multi-bulk reply */
+            /* check if starting point is trivial, before searching
+             * the element in log(N) time */
             if (reverse) {
-                ln = zsl->tail;
-                while (start--)
-                    ln = ln->backward;
+                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen - start);
             } else {
-                ln = zsl->header->forward[0];
-                while (start--)
-                    ln = ln->forward[0];
+                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start + 1);
             }
 
+            /* Return the result in form of a multi-bulk reply */
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                 withscores ? (rangelen*2) : rangelen));
             for (j = 0; j < rangelen; j++) {
@@ -5467,42 +5523,26 @@ static void zrankCommand(redisClient *c) {
     }
     if (o->type != REDIS_ZSET) {
         addReply(c,shared.wrongtypeerr);
-        return;
-    }
-
-    zset *zs = o->ptr;
-    zskiplist *zsl = zs->zsl;
-    dictEntry *de = dictFind(zs->dict,c->argv[2]);
-    if (!de) {
-        addReply(c,shared.nullbulk);
-        return;
-    }
-
-    double *score = dictGetEntryVal(de);
-    zskiplistNode *x;
-    unsigned int rank = 0;
-    int i;
+    } else {
+        zset *zs = o->ptr;
+        zskiplist *zsl = zs->zsl;
+        dictEntry *de;
+        unsigned long rank;
 
-    x = zsl->header;
-    for (i = zsl->level-1; i >= 0; i--) {
-        while (x->forward[i] &&
-            (x->forward[i]->score < *score ||
-                (x->forward[i]->score == *score &&
-                compareStringObjects(x->forward[i]->obj,c->argv[2]) <= 0))) {
-            rank += x->span[i];
-            x = x->forward[i];
+        de = dictFind(zs->dict,c->argv[2]);
+        if (!de) {
+            addReply(c,shared.nullbulk);
+            return;
         }
 
-        /* x might be equal to zsl->header, so test if obj is non-NULL */
-        if (x->obj && compareStringObjects(x->obj,c->argv[2]) == 0) {
-            /* the pointer from zsl->header to the first element also spans one,
-             * which makes the rank 1-based */
+        double *score = dictGetEntryVal(de);
+        rank = zslGetRank(zsl, *score, c->argv[2]);
+        if (rank) {
             addReplyLong(c, rank-1);
-            return;
+        } else {
+            addReply(c,shared.nullbulk);
         }
     }
-
-    addReply(c,shared.nullbulk);
 }
 
 /* ========================= Non type-specific commands  ==================== */