@@ -453,6 +453,7 @@ static void zrevrangeCommand(redisClient *c);
 static void zcardCommand(redisClient *c);
 static void zremCommand(redisClient *c);
 static void zscoreCommand(redisClient *c);
+static void zremrangebyscoreCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -493,6 +494,7 @@ static struct redisCommand cmdTable[] = {
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
+    {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
     {"zrangebyscore",zrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
@@ -3939,6 +3941,49 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     return 0; /* not found */
 }
 
+/* Delete all the elements with score between min and max from the skiplist.
+ * Min and mx are inclusive, so a score >= min || score <= max is deleted.
+ * Note that this function takes the reference to the hash table view of the
+ * sorted set, in order to remove the elements from the hash table too. */
+static unsigned long zslDeleteRange(zskiplist *zsl, double min, double max, dict *dict) {
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    unsigned long removed = 0;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && x->forward[i]->score < min)
+            x = x->forward[i];
+        update[i] = x;
+    }
+    /* We may have multiple elements with the same score, what we need
+     * is to find the element with both the right score and object. */
+    x = x->forward[0];
+    while (x && x->score <= max) {
+        zskiplistNode *next;
+
+        for (i = 0; i < zsl->level; i++) {
+            if (update[i]->forward[i] != x) break;
+            update[i]->forward[i] = x->forward[i];
+        }
+        if (x->forward[0]) {
+            x->forward[0]->backward = (x->backward == zsl->header) ?
+                                        NULL : x->backward;
+        } else {
+            zsl->tail = x->backward;
+        }
+        next = x->forward[0];
+        dictDelete(dict,x->obj);
+        zslFreeNode(x);
+        while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
+            zsl->level--;
+        zsl->length--;
+        removed++;
+        x = next;
+    }
+    return removed; /* not found */
+}
+
 /* Find the first node having a score equal or greater than the specified one.
  * Returns NULL if there is no match. */
 static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
@@ -4042,6 +4087,30 @@ static void zremCommand(redisClient *c) {
     }
 }
 
+static void zremrangebyscoreCommand(redisClient *c) {
+    double min = strtod(c->argv[2]->ptr,NULL);
+    double max = strtod(c->argv[3]->ptr,NULL);
+    robj *zsetobj;
+    zset *zs;
+
+    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
+    if (zsetobj == NULL) {
+        addReply(c,shared.czero);
+    } else {
+        long deleted;
+
+        if (zsetobj->type != REDIS_ZSET) {
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+        zs = zsetobj->ptr;
+        deleted = zslDeleteRange(zs->zsl,min,max,zs->dict);
+        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
+        server.dirty += deleted;
+        addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",deleted));
+    }
+}
+
 static void zrangeGenericCommand(redisClient *c, int reverse) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);