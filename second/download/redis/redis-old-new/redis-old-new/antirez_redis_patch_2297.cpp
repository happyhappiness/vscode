@@ -444,6 +444,7 @@ static void msetCommand(redisClient *c);
 static void msetnxCommand(redisClient *c);
 static void zaddCommand(redisClient *c);
 static void zrangeCommand(redisClient *c);
+static void zrangebyscoreCommand(redisClient *c);
 static void zrevrangeCommand(redisClient *c);
 static void zlenCommand(redisClient *c);
 static void zremCommand(redisClient *c);
@@ -488,6 +489,7 @@ static struct redisCommand cmdTable[] = {
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
+    {"zrangebyscore",zrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
     {"zlen",zlenCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
@@ -3885,6 +3887,7 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
     zsl->length++;
 }
 
+/* Delete an element with matching score/object from the skiplist. */
 static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
     int i;
@@ -3901,7 +3904,7 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     /* We may have multiple elements with the same score, what we need
      * is to find the element with both the right score and object. */
     x = x->forward[0];
-    if (compareStringObjects(x->obj,obj) == 0) {
+    if (x && score == x->score && compareStringObjects(x->obj,obj) == 0) {
         for (i = 0; i < zsl->level; i++) {
             if (update[i]->forward[i] != x) break;
             update[i]->forward[i] = x->forward[i];
@@ -3923,6 +3926,22 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
     return 0; /* not found */
 }
 
+/* Find the first node having a score equal or greater than the specified one.
+ * Returns NULL if there is no match. */
+static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
+    zskiplistNode *x;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && x->forward[i]->score < score)
+            x = x->forward[i];
+    }
+    /* We may have multiple elements with the same score, what we need
+     * is to find the element with both the right score and object. */
+    return x->forward[0];
+}
+
 /* The actual Z-commands implementations */
 
 static void zaddCommand(redisClient *c) {
@@ -4076,6 +4095,52 @@ static void zrevrangeCommand(redisClient *c) {
     zrangeGenericCommand(c,1);
 }
 
+static void zrangebyscoreCommand(redisClient *c) {
+    robj *o;
+    double min = strtod(c->argv[2]->ptr,NULL);
+    double max = strtod(c->argv[3]->ptr,NULL);
+
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
+        addReply(c,shared.nullmultibulk);
+    } else {
+        if (o->type != REDIS_ZSET) {
+            addReply(c,shared.wrongtypeerr);
+        } else {
+            zset *zsetobj = o->ptr;
+            zskiplist *zsl = zsetobj->zsl;
+            zskiplistNode *ln;
+            robj *ele, *lenobj;
+            unsigned int rangelen = 0;
+
+            /* Get the first node with the score >= min */
+            ln = zslFirstWithScore(zsl,min);
+            if (ln == NULL) {
+                /* No element matching the speciifed interval */
+                addReply(c,shared.emptymultibulk);
+                return;
+            }
+
+            /* We don't know in advance how many matching elements there
+             * are in the list, so we push this object that will represent
+             * the multi-bulk length in the output buffer, and will "fix"
+             * it later */
+            lenobj = createObject(REDIS_STRING,NULL);
+            addReply(c,lenobj);
+
+            while(ln->score <= max) {
+                ele = ln->obj;
+                addReplyBulkLen(c,ele);
+                addReply(c,ele);
+                addReply(c,shared.crlf);
+                ln = ln->forward[0];
+                rangelen++;
+            }
+            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
+        }
+    }
+}
+
 static void zlenCommand(redisClient *c) {
     robj *o;
     zset *zs;