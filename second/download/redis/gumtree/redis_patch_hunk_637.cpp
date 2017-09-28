     }
 
 cleanup:
     zfree(scores);
     if (added || updated) {
         signalModifiedKey(c->db,key);
-        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
+        notifyKeyspaceEvent(NOTIFY_ZSET,
             incr ? "zincr" : "zadd", key, c->db->id);
     }
 }
 
-void zaddCommand(redisClient *c) {
+void zaddCommand(client *c) {
     zaddGenericCommand(c,ZADD_NONE);
 }
 
-void zincrbyCommand(redisClient *c) {
+void zincrbyCommand(client *c) {
     zaddGenericCommand(c,ZADD_INCR);
 }
 
-void zremCommand(redisClient *c) {
+void zremCommand(client *c) {
     robj *key = c->argv[1];
     robj *zobj;
     int deleted = 0, keyremoved = 0, j;
 
     if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET)) return;
+        checkType(c,zobj,OBJ_ZSET)) return;
 
-    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *eptr;
 
         for (j = 2; j < c->argc; j++) {
             if ((eptr = zzlFind(zobj->ptr,c->argv[j],NULL)) != NULL) {
                 deleted++;
                 zobj->ptr = zzlDelete(zobj->ptr,eptr);
