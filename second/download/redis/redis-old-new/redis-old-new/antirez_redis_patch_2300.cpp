@@ -311,12 +311,13 @@ typedef struct _redisSortOperation {
 
 typedef struct zskiplistNode {
     struct zskiplistNode **forward;
+    struct zskiplistNode *backward;
     double score;
     robj *obj;
 } zskiplistNode;
 
 typedef struct zskiplist {
-    struct zskiplistNode *header;
+    struct zskiplistNode *header, *tail;
     long length;
     int level;
 } zskiplist;
@@ -435,6 +436,7 @@ static void msetCommand(redisClient *c);
 static void msetnxCommand(redisClient *c);
 static void zaddCommand(redisClient *c);
 static void zrangeCommand(redisClient *c);
+static void zrevrangeCommand(redisClient *c);
 static void zlenCommand(redisClient *c);
 static void zremCommand(redisClient *c);
 
@@ -478,6 +480,7 @@ static struct redisCommand cmdTable[] = {
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
+    {"zrevrange",zrevrangeCommand,4,REDIS_CMD_INLINE},
     {"zlen",zlenCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
@@ -3721,6 +3724,8 @@ static zskiplist *zslCreate(void) {
     zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
     for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++)
         zsl->header->forward[j] = NULL;
+    zsl->header->backward = NULL;
+    zsl->tail = NULL;
     return zsl;
 }
 
@@ -3771,6 +3776,11 @@ static void zslInsert(zskiplist *zsl, double score, robj *obj) {
         x->forward[i] = update[i]->forward[i];
         update[i]->forward[i] = x;
     }
+    x->backward = (update[0] == zsl->header) ? NULL : update[i];
+    if (x->forward[0])
+        x->forward[0]->backward = x;
+    else
+        zsl->tail = x;
     zsl->length++;
 }
 
@@ -3793,6 +3803,12 @@ static int zslDelete(zskiplist *zsl, double score, robj *obj) {
                 if (update[i]->forward[i] != x) break;
                 update[i]->forward[i] = x->forward[i];
             }
+            if (x->forward[0]) {
+                x->forward[0]->backward = (x->backward == zsl->header) ?
+                                            NULL : x->backward;
+            } else {
+                zsl->tail = x->backward;
+            }
             zslFreeNode(x);
             while(zsl->level > 1 && zsl->header->forward[zsl->level-1] == NULL)
                 zsl->level--;
@@ -3890,7 +3906,7 @@ static void zremCommand(redisClient *c) {
     }
 }
 
-static void zrangeCommand(redisClient *c) {
+static void zrangeGenericCommand(redisClient *c, int reverse) {
     robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
@@ -3926,22 +3942,36 @@ static void zrangeCommand(redisClient *c) {
             rangelen = (end-start)+1;
 
             /* Return the result in form of a multi-bulk reply */
-            ln = zsl->header->forward[0];
-            while (start--)
-                ln = ln->forward[0];
+            if (reverse) {
+                ln = zsl->tail;
+                while (start--)
+                    ln = ln->backward;
+            } else {
+                ln = zsl->header->forward[0];
+                while (start--)
+                    ln = ln->forward[0];
+            }
 
             addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
             for (j = 0; j < rangelen; j++) {
                 ele = ln->obj;
                 addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
-                ln = ln->forward[0];
+                ln = reverse ? ln->backward : ln->forward[0];
             }
         }
     }
 }
 
+static void zrangeCommand(redisClient *c) {
+    zrangeGenericCommand(c,0);
+}
+
+static void zrevrangeCommand(redisClient *c) {
+    zrangeGenericCommand(c,1);
+}
+
 static void zlenCommand(redisClient *c) {
     robj *o;
     zset *zs;
@@ -5016,7 +5046,9 @@ static struct redisFunctionSym symsTable[] = {
 {"zslDelete",(unsigned long)zslDelete},
 {"createZsetObject",(unsigned long)createZsetObject},
 {"zaddCommand",(unsigned long)zaddCommand},
+{"zrangeGenericCommand",(unsigned long)zrangeGenericCommand},
 {"zrangeCommand",(unsigned long)zrangeCommand},
+{"zrevrangeCommand",(unsigned long)zrevrangeCommand},
 {"zremCommand",(unsigned long)zremCommand},
 {NULL,0}
 };