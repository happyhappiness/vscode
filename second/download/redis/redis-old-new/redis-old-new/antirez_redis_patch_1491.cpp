@@ -1018,7 +1018,7 @@ void zremrangebyscoreCommand(redisClient *c) {
 
     /* Parse the range arguments. */
     if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
-        addReplyError(c,"min or max is not a double");
+        addReplyError(c,"min or max is not a float");
         return;
     }
 
@@ -1493,7 +1493,7 @@ void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
                 j++; remaining--;
                 for (i = 0; i < setnum; i++, j++, remaining--) {
                     if (getDoubleFromObjectOrReply(c,c->argv[j],&src[i].weight,
-                            "weight value is not a double") != REDIS_OK)
+                            "weight value is not a float") != REDIS_OK)
                     {
                         zfree(src);
                         return;
@@ -1777,7 +1777,7 @@ void genericZrangebyscoreCommand(redisClient *c, int reverse) {
     }
 
     if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
-        addReplyError(c,"min or max is not a double");
+        addReplyError(c,"min or max is not a float");
         return;
     }
 
@@ -1959,7 +1959,7 @@ void zcountCommand(redisClient *c) {
 
     /* Parse the range arguments */
     if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
-        addReplyError(c,"min or max is not a double");
+        addReplyError(c,"min or max is not a float");
         return;
     }
 