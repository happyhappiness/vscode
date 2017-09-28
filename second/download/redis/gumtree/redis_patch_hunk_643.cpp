                 ln = ln->backward;
             } else {
                 ln = ln->level[0].forward;
             }
         }
     } else {
-        redisPanic("Unknown sorted set encoding");
+        serverPanic("Unknown sorted set encoding");
     }
 
     if (withscores) {
         rangelen *= 2;
     }
 
     setDeferredMultiBulkLength(c, replylen, rangelen);
 }
 
-void zrangebyscoreCommand(redisClient *c) {
+void zrangebyscoreCommand(client *c) {
     genericZrangebyscoreCommand(c,0);
 }
 
-void zrevrangebyscoreCommand(redisClient *c) {
+void zrevrangebyscoreCommand(client *c) {
     genericZrangebyscoreCommand(c,1);
 }
 
-void zcountCommand(redisClient *c) {
+void zcountCommand(client *c) {
     robj *key = c->argv[1];
     robj *zobj;
     zrangespec range;
     int count = 0;
 
     /* Parse the range arguments */
-    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
+    if (zslParseRange(c->argv[2],c->argv[3],&range) != C_OK) {
         addReplyError(c,"min or max is not a float");
         return;
     }
 
     /* Lookup the sorted set */
     if ((zobj = lookupKeyReadOrReply(c, key, shared.czero)) == NULL ||
-        checkType(c, zobj, REDIS_ZSET)) return;
+        checkType(c, zobj, OBJ_ZSET)) return;
 
-    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *zl = zobj->ptr;
         unsigned char *eptr, *sptr;
         double score;
 
         /* Use the first element in range as the starting point */
         eptr = zzlFirstInRange(zl,&range);
