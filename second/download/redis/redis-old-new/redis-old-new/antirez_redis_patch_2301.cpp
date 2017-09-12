@@ -435,6 +435,7 @@ static void msetCommand(redisClient *c);
 static void msetnxCommand(redisClient *c);
 static void zaddCommand(redisClient *c);
 static void zrangeCommand(redisClient *c);
+static void zlenCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -475,6 +476,7 @@ static struct redisCommand cmdTable[] = {
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
+    {"zlen",zlenCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
@@ -2052,6 +2054,7 @@ static robj *getDecodedObject(const robj *o) {
 static int compareStringObjects(robj *a, robj *b) {
     assert(a->type == REDIS_STRING && b->type == REDIS_STRING);
 
+    if (a == b) return 0;
     if (a->encoding == REDIS_ENCODING_INT && b->encoding == REDIS_ENCODING_INT){
         return (long)a->ptr - (long)b->ptr;
     } else {
@@ -3751,7 +3754,6 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
             x = x->forward[i];
         update[i] = x;
     }
-    x = x->forward[1];
     /* we assume the key is not already inside, since we allow duplicated
      * scores, and the re-insertion of score and redis object should never
      * happpen since the caller of zslInsert() should test in the hash table
@@ -3771,7 +3773,34 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
 }
 
 static int zslDelete(zskiplist *zsl, double score, robj *obj) {
-    return 1;
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    int i;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i] && x->forward[i]->score < score)
+            x = x->forward[i];
+        update[i] = x;
+    }
+    /* We may have multiple elements with the same score, what we need
+     * is to find the element with both the right score and object. */
+    x = x->forward[0];
+    while(x->score == score) {
+        if (compareStringObjects(x->obj,obj) == 0) {
+            for (i = 0; i < zsl->level; i++) {
+                if (update[i]->forward[i] != x) break;
+                update[i]->forward[i] = x->forward[i];
+            }
+            zslFreeNode(x);
+            while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
+                zsl->level--;
+            return 1;
+        } else {
+            x = x->forward[0];
+            if (!x) return 0; /* end of the list reached, not found */
+        }
+    }
+    return 0; /* not found */
 }
 
 /* The actual Z-commands implementations */
@@ -3813,7 +3842,7 @@ static void zaddCommand(redisClient *c) {
         if (*score != *oldscore) {
             int deleted;
 
-            deleted = zslDelete(zs->zsl,*score,c->argv[3]);
+            deleted = zslDelete(zs->zsl,*oldscore,c->argv[3]);
             assert(deleted != 0);
             zslInsert(zs->zsl,*score,c->argv[3]);
             incrRefCount(c->argv[3]);
@@ -3875,6 +3904,24 @@ static void zrangeCommand(redisClient *c) {
     }
 }
 
+static void zlenCommand(redisClient *c) {
+    robj *o;
+    zset *zs;
+    
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
+        addReply(c,shared.czero);
+        return;
+    } else {
+        if (o->type != REDIS_ZSET) {
+            addReply(c,shared.wrongtypeerr);
+        } else {
+            zs = o->ptr;
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",zs->zsl->length));
+        }
+    }
+}
+
 /* ========================= Non type-specific commands  ==================== */
 
 static void flushdbCommand(redisClient *c) {