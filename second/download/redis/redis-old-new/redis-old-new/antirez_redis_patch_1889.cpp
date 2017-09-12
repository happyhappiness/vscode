@@ -475,10 +475,11 @@ void configCommand(redisClient *c) {
         configGetCommand(c);
     } else if (!strcasecmp(c->argv[1]->ptr,"resetstat")) {
         if (c->argc != 2) goto badarity;
+        server.stat_keyspace_hits = 0;
+        server.stat_keyspace_misses = 0;
         server.stat_numcommands = 0;
         server.stat_numconnections = 0;
         server.stat_expiredkeys = 0;
-        server.stat_starttime = time(NULL);
         addReply(c,shared.ok);
     } else {
         addReplyError(c,