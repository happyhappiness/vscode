@@ -379,30 +379,6 @@ void typeCommand(redisClient *c) {
     addReplyStatus(c,type);
 }
 
-void saveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1) {
-        addReplyError(c,"Background save already in progress");
-        return;
-    }
-    if (rdbSave(server.dbfilename) == REDIS_OK) {
-        addReply(c,shared.ok);
-    } else {
-        addReply(c,shared.err);
-    }
-}
-
-void bgsaveCommand(redisClient *c) {
-    if (server.bgsavechildpid != -1) {
-        addReplyError(c,"Background save already in progress");
-        return;
-    }
-    if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
-        addReplyStatus(c,"Background saving started");
-    } else {
-        addReply(c,shared.err);
-    }
-}
-
 void shutdownCommand(redisClient *c) {
     if (prepareForShutdown() == REDIS_OK)
         exit(0);