@@ -977,9 +977,9 @@ void scriptCommand(redisClient *c) {
         sdsfree(sha);
     } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
         if (server.lua_caller == NULL) {
-            addReplyError(c,"No scripts in execution right now.");
+            addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));
         } else if (server.lua_write_dirty) {
-            addReplyError(c, "Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in an hard way using the SHUTDOWN NOSAVE command.");
+            addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in an hard way using the SHUTDOWN NOSAVE command.\r\n"));
         } else {
             server.lua_kill = 1;
             addReply(c,shared.ok);