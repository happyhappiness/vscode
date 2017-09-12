@@ -632,12 +632,11 @@ int rewriteAppendOnlyFileBackground(void) {
 
 void bgrewriteaofCommand(redisClient *c) {
     if (server.bgrewritechildpid != -1) {
-        addReplySds(c,sdsnew("-ERR background append only file rewriting already in progress\r\n"));
+        addReplyError(c,"Background append only file rewriting already in progress");
         return;
     }
     if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
-        char *status = "+Background append only file rewriting started\r\n";
-        addReplySds(c,sdsnew(status));
+        addReplyStatus(c,"Background append only file rewriting started");
     } else {
         addReply(c,shared.err);
     }