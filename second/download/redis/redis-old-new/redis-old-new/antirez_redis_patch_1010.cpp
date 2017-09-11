@@ -2959,7 +2959,7 @@ void dumpCommand(redisClient *c) {
 
 /* RESTORE key ttl serialized-value [REPLACE] */
 void restoreCommand(redisClient *c) {
-    long ttl;
+    long long ttl;
     rio payload;
     int j, type, replace = 0;
     robj *obj;
@@ -2981,15 +2981,16 @@ void restoreCommand(redisClient *c) {
     }
 
     /* Check if the TTL value makes sense */
-    if (getLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != REDIS_OK) {
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != REDIS_OK) {
         return;
     } else if (ttl < 0) {
         addReplyError(c,"Invalid TTL value, must be >= 0");
         return;
     }
 
     /* Verify RDB version and data checksum. */
-    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == REDIS_ERR) {
+    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == REDIS_ERR)
+    {
         addReplyError(c,"DUMP payload version or checksum are wrong");
         return;
     }