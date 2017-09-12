@@ -677,6 +677,7 @@ static void zrankCommand(redisClient *c);
 static void zrevrankCommand(redisClient *c);
 static void hsetCommand(redisClient *c);
 static void hgetCommand(redisClient *c);
+static void zremrangebyrankCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -724,6 +725,7 @@ static struct redisCommand cmdTable[] = {
     {"zincrby",zincrbyCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM,1,1,1},
     {"zrem",zremCommand,3,REDIS_CMD_BULK,1,1,1},
     {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE,1,1,1},
+    {"zremrangebyrank",zremrangebyrankCommand,4,REDIS_CMD_INLINE,1,1,1},
     {"zrange",zrangeCommand,-4,REDIS_CMD_INLINE,1,1,1},
     {"zrangebyscore",zrangebyscoreCommand,-4,REDIS_CMD_INLINE,1,1,1},
     {"zcount",zcountCommand,4,REDIS_CMD_INLINE,1,1,1},
@@ -5078,6 +5080,31 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
     zsl->length++;
 }
 
+/* Internal function used by zslDelete, zslDeleteByScore and zslDeleteByRank */
+void zslDeleteNode(zskiplist *zsl, zskiplistNode *x, zskiplistNode **update) {
+    int i;
+    for (i = 0; i < zsl->level; i++) {
+        if (update[i]->forward[i] == x) {
+            if (i > 0) {
+                update[i]->span[i-1] += x->span[i-1] - 1;
+            }
+            update[i]->forward[i] = x->forward[i];
+        } else {
+            /* invariant: i > 0, because update[0]->forward[0]
+             * is always equal to x */
+            update[i]->span[i-1] -= 1;
+        }
+    }
+    if (x->forward[0]) {
+        x->forward[0]->backward = x->backward;
+    } else {
+        zsl->tail = x->backward;
+    }
+    while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
+        zsl->level--;
+    zsl->length--;
+}
+
 /* Delete an element with matching score/object from the skiplist. */
 static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
@@ -5096,27 +5123,8 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
      * is to find the element with both the right score and object. */
     x = x->forward[0];
     if (x && score == x->score && compareStringObjects(x->obj,obj) == 0) {
-        for (i = 0; i < zsl->level; i++) {
-            if (update[i]->forward[i] == x) {
-                if (i > 0) {
-                    update[i]->span[i-1] += x->span[i-1] - 1;
-                }
-                update[i]->forward[i] = x->forward[i];
-            } else {
-                /* invariant: i > 0, because update[0]->forward[0]
-                 * is always equal to x */
-                update[i]->span[i-1] -= 1;
-            }
-        }
-        if (x->forward[0]) {
-            x->forward[0]->backward = x->backward;
-        } else {
-            zsl->tail = x->backward;
-        }
+        zslDeleteNode(zsl, x, update);
         zslFreeNode(x);
-        while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
-            zsl->level--;
-        zsl->length--;
         return 1;
     } else {
         return 0; /* not found */
@@ -5128,7 +5136,7 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
  * Min and mx are inclusive, so a score >= min || score <= max is deleted.
  * Note that this function takes the reference to the hash table view of the
  * sorted set, in order to remove the elements from the hash table too. */
-static unsigned long zslDeleteRange(zskiplist *zsl, double min, double max, dict *dict) {
+static unsigned long zslDeleteRangeByScore(zskiplist *zsl, double min, double max, dict *dict) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     unsigned long removed = 0;
     int i;
@@ -5143,35 +5151,44 @@ static unsigned long zslDeleteRange(zskiplist *zsl, double min, double max, dict
      * is to find the element with both the right score and object. */
     x = x->forward[0];
     while (x && x->score <= max) {
-        zskiplistNode *next;
+        zskiplistNode *next = x->forward[0];
+        zslDeleteNode(zsl, x, update);
+        dictDelete(dict,x->obj);
+        zslFreeNode(x);
+        removed++;
+        x = next;
+    }
+    return removed; /* not found */
+}
 
-        for (i = 0; i < zsl->level; i++) {
-            if (update[i]->forward[i] == x) {
-                if (i > 0) {
-                    update[i]->span[i-1] += x->span[i-1] - 1;
-                }
-                update[i]->forward[i] = x->forward[i];
-            } else {
-                /* invariant: i > 0, because update[0]->forward[0]
-                 * is always equal to x */
-                update[i]->span[i-1] -= 1;
-            }
-        }
-        if (x->forward[0]) {
-            x->forward[0]->backward = x->backward;
-        } else {
-            zsl->tail = x->backward;
+/* Delete all the elements with rank between start and end from the skiplist.
+ * Start and end are inclusive. Note that start and end need to be 1-based */
+static unsigned long zslDeleteRangeByRank(zskiplist *zsl, unsigned int start, unsigned int end, dict *dict) {
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    unsigned long traversed = 0, removed = 0;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && (traversed + (i > 0 ? x->span[i-1] : 1)) < start) {
+            traversed += i > 0 ? x->span[i-1] : 1;
+            x = x->forward[i];
         }
-        next = x->forward[0];
+        update[i] = x;
+    }
+
+    traversed++;
+    x = x->forward[0];
+    while (x && traversed <= end) {
+        zskiplistNode *next = x->forward[0];
+        zslDeleteNode(zsl, x, update);
         dictDelete(dict,x->obj);
         zslFreeNode(x);
-        while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
-            zsl->level--;
-        zsl->length--;
         removed++;
+        traversed++;
         x = next;
     }
-    return removed; /* not found */
+    return removed;
 }
 
 /* Find the first node having a score equal or greater than the specified one.
@@ -5386,13 +5403,54 @@ static void zremrangebyscoreCommand(redisClient *c) {
             return;
         }
         zs = zsetobj->ptr;
-        deleted = zslDeleteRange(zs->zsl,min,max,zs->dict);
+        deleted = zslDeleteRangeByScore(zs->zsl,min,max,zs->dict);
         if (htNeedsResize(zs->dict)) dictResize(zs->dict);
         server.dirty += deleted;
         addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
     }
 }
 
+static void zremrangebyrankCommand(redisClient *c) {
+    int start = atoi(c->argv[2]->ptr);
+    int end = atoi(c->argv[3]->ptr);
+    robj *zsetobj;
+    zset *zs;
+
+    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
+    if (zsetobj == NULL) {
+        addReply(c,shared.czero);
+    } else {
+        if (zsetobj->type != REDIS_ZSET) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+
+        zs = zsetobj->ptr;
+        int llen = zs->zsl->length;
+        long deleted;
+
+        /* convert negative indexes */
+        if (start < 0) start = llen+start;
+        if (end < 0) end = llen+end;
+        if (start < 0) start = 0;
+        if (end < 0) end = 0;
+
+        /* indexes sanity checks */
+        if (start > end || start >= llen) {
+            addReply(c,shared.czero);
+            return;
+        }
+        if (end >= llen) end = llen-1;
+
+        /* increment start and end because zsl*Rank functions
+         * use 1-based rank */
+        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
+        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+        server.dirty += deleted;
+        addReplyLong(c, deleted);
+    }
+}
+
 static void zrangeGenericCommand(redisClient *c, int reverse) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);
@@ -5439,9 +5497,9 @@ static void zrangeGenericCommand(redisClient *c, int reverse) {
             /* check if starting point is trivial, before searching
              * the element in log(N) time */
             if (reverse) {
-                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen - start);
+                ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
             } else {
-                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start + 1);
+                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
             }
 
             /* Return the result in form of a multi-bulk reply */