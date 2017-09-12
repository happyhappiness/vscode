@@ -355,8 +355,7 @@ void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, i
             *score = scoreval;
         }
         if (isnan(*score)) {
-            addReplySds(c,
-                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
+            addReplyError(c,"resulting score is not a number (NaN)");
             zfree(score);
             /* Note that we don't need to check if the zset may be empty and
              * should be removed here, as we can only obtain Nan as score if
@@ -561,7 +560,8 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     /* expect setnum input keys to be given */
     setnum = atoi(c->argv[2]->ptr);
     if (setnum < 1) {
-        addReplySds(c,sdsnew("-ERR at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE\r\n"));
+        addReplyError(c,
+            "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
         return;
     }
 
@@ -782,8 +782,7 @@ void zrangeGenericCommand(redisClient *c, int reverse) {
     }
 
     /* Return the result in form of a multi-bulk reply */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
-        withscores ? (rangelen*2) : rangelen));
+    addReplyMultiBulkLen(c,withscores ? (rangelen*2) : rangelen);
     for (j = 0; j < rangelen; j++) {
         ele = ln->obj;
         addReplyBulk(c,ele);
@@ -840,8 +839,7 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
     if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
         badsyntax = 1;
     if (badsyntax) {
-        addReplySds(c,
-            sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
+        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
         return;
     }
 
@@ -866,7 +864,8 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
             zset *zsetobj = o->ptr;
             zskiplist *zsl = zsetobj->zsl;
             zskiplistNode *ln;
-            robj *ele, *lenobj = NULL;
+            robj *ele;
+            void *replylen = NULL;
             unsigned long rangelen = 0;
 
             /* Get the first node with the score >= min, or with
@@ -884,11 +883,8 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
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
@@ -910,7 +906,7 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
             if (justcount) {
                 addReplyLongLong(c,(long)rangelen);
             } else {
-                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
+                setDeferredMultiBulkLength(c,replylen,
                      withscores ? (rangelen*2) : rangelen);
             }
         }
@@ -933,7 +929,7 @@ void zcardCommand(redisClient *c) {
         checkType(c,o,REDIS_ZSET)) return;
 
     zs = o->ptr;
-    addReplyUlong(c,zs->zsl->length);
+    addReplyLongLong(c,zs->zsl->length);
 }
 
 void zscoreCommand(redisClient *c) {