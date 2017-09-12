@@ -466,6 +466,7 @@ static void debugCommand(redisClient *c);
 static void msetCommand(redisClient *c);
 static void msetnxCommand(redisClient *c);
 static void zaddCommand(redisClient *c);
+static void zincrscorebyCommand(redisClient *c);
 static void zrangeCommand(redisClient *c);
 static void zrangebyscoreCommand(redisClient *c);
 static void zrevrangeCommand(redisClient *c);
@@ -513,6 +514,7 @@ static struct redisCommand cmdTable[] = {
     {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM},
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"zadd",zaddCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
+    {"zincrscoreby",zincrscorebyCommand,4,REDIS_CMD_BULK|REDIS_CMD_DENYOOM},
     {"zrem",zremCommand,3,REDIS_CMD_BULK},
     {"zremrangebyscore",zremrangebyscoreCommand,4,REDIS_CMD_INLINE},
     {"zrange",zrangeCommand,4,REDIS_CMD_INLINE},
@@ -1383,7 +1385,6 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
-
     /* Use writev() if we have enough buffers to send */
     if (!server.glueoutputbuf &&
         listLength(c->reply) > REDIS_WRITEV_THRESHOLD && 
@@ -1939,6 +1940,14 @@ static void addReplySds(redisClient *c, sds s) {
     decrRefCount(o);
 }
 
+static void addReplyDouble(redisClient *c, double d) {
+    char buf[128];
+
+    snprintf(buf,sizeof(buf),"%.17g",d);
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
+        strlen(buf),buf));
+}
+
 static void addReplyBulkLen(redisClient *c, robj *obj) {
     size_t len;
 
@@ -4220,56 +4229,101 @@ static zskiplistNode *zslFirstWithScore(zskiplist *zsl, double score) {
 
 /* The actual Z-commands implementations */
 
-static void zaddCommand(redisClient *c) {
+/* This generic command implements both ZADD and ZINCRSCOREBY.
+ * scoreval is the score if the operation is a ZADD (doincrement == 0) or
+ * the increment if the operation is a ZINCRSCOREBY (doincrement == 1). */
+static void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, int doincrement) {
     robj *zsetobj;
     zset *zs;
     double *score;
 
-    zsetobj = lookupKeyWrite(c->db,c->argv[1]);
+    zsetobj = lookupKeyWrite(c->db,key);
     if (zsetobj == NULL) {
         zsetobj = createZsetObject();
-        dictAdd(c->db->dict,c->argv[1],zsetobj);
-        incrRefCount(c->argv[1]);
+        dictAdd(c->db->dict,key,zsetobj);
+        incrRefCount(key);
     } else {
         if (zsetobj->type != REDIS_ZSET) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
     }
-    score = zmalloc(sizeof(double));
-    *score = strtod(c->argv[2]->ptr,NULL);
     zs = zsetobj->ptr;
-    if (dictAdd(zs->dict,c->argv[3],score) == DICT_OK) {
+
+    /* Ok now since we implement both ZADD and ZINCRSCOREBY here the code
+     * needs to handle the two different conditions. It's all about setting
+     * '*score', that is, the new score to set, to the right value. */
+    score = zmalloc(sizeof(double));
+    if (doincrement) {
+        dictEntry *de;
+
+        /* Read the old score. If the element was not present starts from 0 */
+        de = dictFind(zs->dict,ele);
+        if (de) {
+            double *oldscore = dictGetEntryVal(de);
+            *score = *oldscore + scoreval;
+        } else {
+            *score = scoreval;
+        }
+    } else {
+        *score = scoreval;
+    }
+
+    /* What follows is a simple remove and re-insert operation that is common
+     * to both ZADD and ZINCRSCOREBY... */
+    if (dictAdd(zs->dict,ele,score) == DICT_OK) {
         /* case 1: New element */
-        incrRefCount(c->argv[3]); /* added to hash */
-        zslInsert(zs->zsl,*score,c->argv[3]);
-        incrRefCount(c->argv[3]); /* added to skiplist */
+        incrRefCount(ele); /* added to hash */
+        zslInsert(zs->zsl,*score,ele);
+        incrRefCount(ele); /* added to skiplist */
         server.dirty++;
-        addReply(c,shared.cone);
+        if (doincrement)
+            addReply(c,shared.cone);
+        else
+            addReplyDouble(c,*score);
     } else {
         dictEntry *de;
         double *oldscore;
         
         /* case 2: Score update operation */
-        de = dictFind(zs->dict,c->argv[3]);
+        de = dictFind(zs->dict,ele);
         assert(de != NULL);
         oldscore = dictGetEntryVal(de);
         if (*score != *oldscore) {
             int deleted;
 
-            deleted = zslDelete(zs->zsl,*oldscore,c->argv[3]);
+            /* Remove and insert the element in the skip list with new score */
+            deleted = zslDelete(zs->zsl,*oldscore,ele);
             assert(deleted != 0);
-            zslInsert(zs->zsl,*score,c->argv[3]);
-            incrRefCount(c->argv[3]);
-            dictReplace(zs->dict,c->argv[3],score);
+            zslInsert(zs->zsl,*score,ele);
+            incrRefCount(ele);
+            /* Update the score in the hash table */
+            dictReplace(zs->dict,ele,score);
             server.dirty++;
         } else {
             zfree(score);
         }
-        addReply(c,shared.czero);
+        if (doincrement)
+            addReplyDouble(c,*score);
+        else
+            addReply(c,shared.czero);
     }
 }
 
+static void zaddCommand(redisClient *c) {
+    double scoreval;
+
+    scoreval = strtod(c->argv[2]->ptr,NULL);
+    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,0);
+}
+
+static void zincrscorebyCommand(redisClient *c) {
+    double scoreval;
+
+    scoreval = strtod(c->argv[2]->ptr,NULL);
+    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
+}
+
 static void zremCommand(redisClient *c) {
     robj *zsetobj;
     zset *zs;
@@ -4478,12 +4532,9 @@ static void zscoreCommand(redisClient *c) {
             if (!de) {
                 addReply(c,shared.nullbulk);
             } else {
-                char buf[128];
                 double *score = dictGetEntryVal(de);
 
-                snprintf(buf,sizeof(buf),"%.17g",*score);
-                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
-                    strlen(buf),buf));
+                addReplyDouble(c,*score);
             }
         }
     }