@@ -12,7 +12,7 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
         if (getLongFromObjectOrReply(c, expire, &seconds, NULL) != REDIS_OK)
             return;
         if (seconds <= 0) {
-            addReplySds(c,sdsnew("-ERR invalid expire time in SETEX\r\n"));
+            addReplyError(c,"invalid expire time in SETEX");
             return;
         }
     }
@@ -98,7 +98,7 @@ void msetGenericCommand(redisClient *c, int nx) {
     int j, busykeys = 0;
 
     if ((c->argc % 2) == 0) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments for MSET\r\n"));
+        addReplyError(c,"wrong number of arguments for MSET");
         return;
     }
     /* Handle the NX flag. The MSETNX semantic is to return zero and don't