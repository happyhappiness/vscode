@@ -1438,7 +1438,8 @@ inline static void zunionInterAggregate(double *target, double val, int aggregat
 }
 
 void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
-    int i, j, setnum;
+    int i, j;
+    long setnum;
     int aggregate = REDIS_AGGR_SUM;
     zsetopsrc *src;
     zsetopval zval;
@@ -1450,7 +1451,9 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
     int touched = 0;
 
     /* expect setnum input keys to be given */
-    setnum = atoi(c->argv[2]->ptr);
+    if ((getLongFromObjectOrReply(c, c->argv[2], &setnum, NULL) != REDIS_OK))
+        return;
+
     if (setnum < 1) {
         addReplyError(c,
             "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
@@ -1762,7 +1765,7 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse) {
     zrangespec range;
     robj *key = c->argv[1];
     robj *zobj;
-    int offset = 0, limit = -1;
+    long offset = 0, limit = -1;
     int withscores = 0;
     unsigned long rangelen = 0;
     void *replylen = NULL;
@@ -1793,8 +1796,8 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse) {
                 pos++; remaining--;
                 withscores = 1;
             } else if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
-                offset = atoi(c->argv[pos+1]->ptr);
-                limit = atoi(c->argv[pos+2]->ptr);
+                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != REDIS_OK) ||
+                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
                 pos += 3; remaining -= 3;
             } else {
                 addReply(c,shared.syntaxerr);