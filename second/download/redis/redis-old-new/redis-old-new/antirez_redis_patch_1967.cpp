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
 
@@ -839,8 +839,7 @@ void genericZrangebyscoreCommand(redisClient *c, int justcount) {
     if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
         badsyntax = 1;
     if (badsyntax) {
-        addReplySds(c,
-            sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
+        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
         return;
     }
 