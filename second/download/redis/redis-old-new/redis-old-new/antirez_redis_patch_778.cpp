@@ -69,7 +69,7 @@ void setGenericCommand(redisClient *c, int flags, robj *key, robj *val, robj *ex
         if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
             return;
         if (milliseconds <= 0) {
-            addReplyError(c,"invalid expire time in SETEX");
+            addReplyErrorFormat(c,"invalid expire time in %s",c->cmd->name);
             return;
         }
         if (unit == UNIT_SECONDS) milliseconds *= 1000;
@@ -255,7 +255,7 @@ void getrangeCommand(redisClient *c) {
     if (end < 0) end = strlen+end;
     if (start < 0) start = 0;
     if (end < 0) end = 0;
-    if ((unsigned)end >= strlen) end = strlen-1;
+    if ((size_t)end >= strlen) end = strlen-1;
 
     /* Precondition: end >= 0 && end < strlen, so the only condition where
      * nothing can be returned is: start > end. */