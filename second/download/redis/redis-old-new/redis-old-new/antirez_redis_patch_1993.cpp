@@ -866,7 +866,8 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
             zset *zsetobj = o->ptr;
             zskiplist *zsl = zsetobj->zsl;
             zskiplistNode *ln;
-            robj *ele, *lenobj = NULL;
+            robj *ele;
+            void *replylen = NULL;
             unsigned long rangelen = 0;
 
             /* Get the first node with the score >= min, or with
@@ -884,11 +885,8 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
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
@@ -910,7 +908,7 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
             if (justcount) {
                 addReplyLongLong(c,(long)rangelen);
             } else {
-                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
+                setDeferredMultiBulkLength(c,replylen,
                      withscores ? (rangelen*2) : rangelen);
             }
         }