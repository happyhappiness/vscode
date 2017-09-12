@@ -249,7 +249,7 @@ void hmsetCommand(redisClient *c) {
     robj *o;
 
     if ((c->argc % 2) == 1) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
+        addReplyError(c,"wrong number of arguments for HMSET");
         return;
     }
 