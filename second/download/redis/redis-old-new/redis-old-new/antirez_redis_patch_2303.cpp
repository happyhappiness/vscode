@@ -434,6 +434,7 @@ static void debugCommand(redisClient *c);
 static void msetCommand(redisClient *c);
 static void msetnxCommand(redisClient *c);
 static void zaddCommand(redisClient *c);
+static void zrangeCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -473,6 +474,7 @@ static struct redisCommand cmdTable[] = {
     {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
+    {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"getset",getsetCommand,3,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
@@ -3710,6 +3712,7 @@ static zskiplist *zslCreate(void) {
     
     zsl = zmalloc(sizeof(*zsl));
     zsl->level = 1;
+    zsl->length = 0;
     zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
     for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++)
         zsl->header->forward[j] = NULL;
@@ -3764,6 +3767,7 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
         x->forward[i] = update[i]->forward[i];
         update[i]->forward[i] = x;
     }
+    zsl->length++;
 }
 
 static int zslDelete(zskiplist *zsl, double score, robj *obj) {
@@ -3819,6 +3823,58 @@ static void zaddCommand(redisClient *c) {
     }
 }
 
+static void zrangeCommand(redisClient *c) {
+    robj *o;
+    int start = atoi(c->argv[2]->ptr);
+    int end = atoi(c->argv[3]->ptr);
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
+
+            int llen = zsl->length;
+            int rangelen, j;
+            robj *ele;
+
+            /* convert negative indexes */
+            if (start < 0) start = llen+start;
+            if (end < 0) end = llen+end;
+            if (start < 0) start = 0;
+            if (end < 0) end = 0;
+
+            /* indexes sanity checks */
+            if (start > end || start >= llen) {
+                /* Out of range start or start > end result in empty list */
+                addReply(c,shared.emptymultibulk);
+                return;
+            }
+            if (end >= llen) end = llen-1;
+            rangelen = (end-start)+1;
+
+            /* Return the result in form of a multi-bulk reply */
+            ln = zsl->header->forward[0];
+            while (start--)
+                ln = ln->forward[0];
+
+            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+            for (j = 0; j < rangelen; j++) {
+                ele = ln->forward[0]->obj;
+                addReplyBulkLen(c,ele);
+                addReply(c,ele);
+                addReply(c,shared.crlf);
+                ln = ln->forward[0];
+            }
+        }
+    }
+}
+
 /* ========================= Non type-specific commands  ==================== */
 
 static void flushdbCommand(redisClient *c) {
@@ -4875,6 +4931,7 @@ static struct redisFunctionSym symsTable[] = {
 {"zslDelete",(unsigned long)zslDelete},
 {"createZsetObject",(unsigned long)createZsetObject},
 {"zaddCommand",(unsigned long)zaddCommand},
+{"zrangeCommand",(unsigned long)zrangeCommand},
 {NULL,0}
 };
 