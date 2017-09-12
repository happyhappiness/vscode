@@ -555,6 +555,7 @@ void configCommand(redisClient *c) {
         server.stat_numcommands = 0;
         server.stat_numconnections = 0;
         server.stat_expiredkeys = 0;
+        resetCommandTableStats();
         addReply(c,shared.ok);
     } else {
         addReplyError(c,