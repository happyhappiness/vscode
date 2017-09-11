@@ -1085,7 +1085,7 @@ void saveCommand(redisClient *c) {
 void bgsaveCommand(redisClient *c) {
     if (server.bgsavechildpid != -1) {
         addReplyError(c,"Background save already in progress");
-    } else if (server.bgrewritechildpid != -1) {
+    } else if (server.aof_child_pid != -1) {
         addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
     } else if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
         addReplyStatus(c,"Background saving started");