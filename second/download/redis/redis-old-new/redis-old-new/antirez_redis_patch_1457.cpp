@@ -216,12 +216,12 @@ void debugCommand(redisClient *c) {
         if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
         redisAssertWithInfo(c,c->argv[0],1 == 2);
     } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
-        if (rdbSave(server.dbfilename) != REDIS_OK) {
+        if (rdbSave(server.rdb_filename) != REDIS_OK) {
             addReply(c,shared.err);
             return;
         }
         emptyDb();
-        if (rdbLoad(server.dbfilename) != REDIS_OK) {
+        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
             addReplyError(c,"Error trying to load the RDB dump");
             return;
         }